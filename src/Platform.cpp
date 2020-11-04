#include "Platform.h"
#include "Streamer.h"
#include "Viewer.h"
#include "StreamData.h"
#include "Stream.h"
#include "PrivateStream.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>

Platform::Platform() : archive(files.archived_stream_file) {
    std::string line;
    std::ifstream users_file(files.user_file);
    if(users_file.is_open()){
        /*
        std::getline(users_file, line);
        while(std::getline(users_file, line)){
            std::string nickname, name;
            std::istringstream ss{line};
            ss >> nickname;
            std::getline(ss, name);
            // TODO: Change to correct class
            users.push_back(new Viewer(nickname, name, Date(), this));
        }*/
        users_file.close();
    }
    // TODO: Read streams
}

Platform::~Platform() {
    if(!test){
        save();
    }
    for(auto ptr : users){
        delete ptr;
    }
}

void Platform::save(){
    std::cout << "saving" << std::endl;
    std::ofstream users_file(files.user_file, std::ofstream::trunc);
    if(users_file.is_open()){
        for(const auto &user : users){
            users_file << *user;
            users_file << std::endl;
        }
        users_file.close();
    }
    std::ofstream streams_file(files.active_stream_file, std::ofstream::trunc);
    if(streams_file.is_open()){
        streams_file << stream_id_count << endl;
        for(const auto &stream : active_streams){
            streams_file << *stream;
            streams_file << std::endl;
        }
        streams_file.close();
    }
}

template <typename F>
void Platform::sortActiveStreams(F pred) {
    std::sort(active_streams.begin(), active_streams.end(), pred);
}

void Platform::sort(sortingMode mode, sortingOrder order) {
    switch(mode){
        case views:
            sortActiveStreams([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return ptr1->getViewers() < ptr2->getViewers();
            }); break;
        case likes:/* TODO: Uncomment
            sortActiveStreams([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return ptr1->getLikes() < ptr2->getLikes();
            });*/ break;
        case id:
            sortActiveStreams([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return ptr1->getId() < ptr2->getId();
            }); break;
        case minimum_age:
            sortActiveStreams([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return ptr1->getMinimumAge() < ptr2->getMinimumAge();
            }); break;
        default:
            return;
    }
    if(order == descending){
        std::reverse(active_streams.begin(), active_streams.end());
    }
}

bool Platform::userExists(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User *user){
        return user->getNickname() == nickname;
    });
    return (it != users.end());
}

bool Platform::registerStreamer(const std::string &nickname, const std::string &name, const Date &birth_date) {
    if(userExists(nickname)){
        throw UserAlreadyExists(nickname);
    }
    users.push_back(new Streamer(nickname, name, birth_date, this));
    return true;
}

bool Platform::registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date) {
    if(userExists(nickname)){
        throw UserAlreadyExists(nickname);
    }
    users.push_back(new Viewer(nickname, name, birth_date, this));
    return true;
}

unsigned int Platform::getUserCount() const{
    return users.size();
}
unsigned int Platform::getActiveStreamCount() const{
    return active_streams.size();
}
unsigned int Platform::getArchivedStreamCount() const {
    return archive.getStreamCount();
}

unsigned int Platform::getTotalStreamCount() const{
    return getActiveStreamCount() + getArchivedStreamCount();
}


void Platform::showStreams(const std::string &language_filter, unsigned minimum_age) {
    for(int i = 0; i < active_streams.size(); ++i){
        //TODO Check minimum age
        if((language_filter.empty() || active_streams[i]->getLanguage() == language_filter) && active_streams[i]->getMinimumAge() <= minimum_age){
            std::cout << i+1 << ": " << active_streams[i]->getTitle() << ' ' << active_streams[i]->getId() << ' '
                      << active_streams[i]->getViewers() << std::endl;
        }
        /*
        if(active_streams[i]->getMinimumAge() < minimum_age && (!language_filter || active_streams[i]->getLanguage() == language_filter){
            // TODO Change to .show()
            std::cout << i+1 << ": " << active_streams[i]->getTitle() << ' ' << active_streams[i]->getId() << ' '
                      << active_streams[i]->getViewers() << std::endl;
        }*/
    }
}

void Platform::showUsers() {
    for(int i = 0; i < users.size(); ++i){
        std::cout << i+1 << ": ";
        users[i]->show();
    }
}

void Platform::showStreamHistory(const std::vector<unsigned int> &ids) {
    std::vector<StreamData *> history = archive.getStreamsById(ids);
    for(const auto &data : history){
        // TODO: Uncomment
        //data->show();
    }
}

User *Platform::getUser(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User * user){
        return user->getNickname() == nickname;
    });
    if(it == users.end()){
        throw UserDoesNotExist(nickname);
    }
    return (*it);
}

std::weak_ptr<Stream> Platform::joinStreamByPos(int p, Viewer &viewer) {
    p--;
    if(p < 0 || p >= active_streams.size()){
        throw std::out_of_range("Invalid index for active_streams");
    }

    if(active_streams[p]->canJoin(viewer)){
        active_streams[p]->joinStream();
        std::weak_ptr<Stream> ptr = active_streams[p];
        return ptr;
    }
    return std::weak_ptr<Stream>();
}

std::weak_ptr<Stream> Platform::joinStreamById(unsigned int id, Viewer &viewer) {
    auto it = std::find_if(active_streams.begin(), active_streams.end(), [id](std::shared_ptr<Stream> ptr){
        return ptr->getId() == id;
    });
    if(it == active_streams.end()){
        if(id >= stream_id_count || id < 1){
            throw StreamDoesNotExist(id);
        }
        else{
            throw StreamNoLongerActive(id);
        }
    }
    if((*it)->canJoin(viewer)){
        (*it)->joinStream();
        std::weak_ptr<Stream> ptr = (*it);
        return ptr;
    }
    return std::weak_ptr<Stream>();
}

std::weak_ptr<Stream> Platform::startPublicStream(const string &title, const string &streamer, const string &language,
                                                  const unsigned int minimum_age) {
    std::shared_ptr<Stream> ptr(new Stream(title, streamer, language, stream_id_count++, minimum_age));
    active_streams.emplace_back(ptr);
    std::weak_ptr<Stream> weak_ptr = ptr;
    return weak_ptr;
}

std::weak_ptr<Stream> Platform::startPrivateStream(const string &title, const string &streamer, const string &language,
                                                   const unsigned minimum_age, const unsigned max_capacity,
                                                   const vector<string> &allowed_viewers){
    std::shared_ptr<Stream> ptr(new PrivateStream(title, streamer, language, stream_id_count++, minimum_age, max_capacity, allowed_viewers));
    active_streams.emplace_back(ptr);
    std::weak_ptr<Stream> weak_ptr = ptr;
    return weak_ptr;
}

void Platform::endStream(unsigned int id){
    auto stream_it = std::find_if(active_streams.begin(), active_streams.end(), [id](std::shared_ptr<Stream> ptr){
        return ptr->getId() == id;
    });
    if(stream_it == active_streams.end()){
        if(id >= stream_id_count || id < 1)
            throw StreamDoesNotExist(id);
        else
            throw StreamNoLongerActive(id);
    }
    StreamData data = *(*stream_it);
    archive.archiveStream(data);
    active_streams.erase(stream_it);
}

template <typename F>
std::vector<std::weak_ptr<Stream>> Platform::getTopActiveStreams(F pred){
    std::vector<std::weak_ptr<Stream>> top10;
    int n_elements = active_streams.size() > 10 ? 10 : active_streams.size();
    top10.reserve(n_elements);
    std::stack<decltype(active_streams.begin())> s;

    // Custom insertion sort, where 10 greatest elements are inserted into the first 10 index
    for(auto it = active_streams.begin(); it != active_streams.begin() + n_elements; ++it){
        auto max_it = std::max_element(it, active_streams.end(), pred);
        s.emplace(max_it);
        std::iter_swap(it, max_it);
    }
    for(int i = 0; i < n_elements; ++i){
        top10.emplace_back(active_streams[i]);
    }
    // Unwind the changes made, restoring original vector state
    auto it = active_streams.begin() + n_elements - 1;
    for(int i = 0; i < n_elements; ++i, --it){
        std::iter_swap(s.top(), it);
        s.pop();
    }
    return top10;
}

void Platform::topActiveStreams() {
    // TODO: Uncomment likes
    /*
    std::vector<std::weak_ptr<Stream>> likes = getTop([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
        return ptr1->getLikes() < ptr2->getLikes();
    });*/

    std::vector<std::weak_ptr<Stream>> views = getTopActiveStreams([](const std::shared_ptr<Stream> &ptr1,const std::shared_ptr<Stream> &ptr2){
        return ptr1->getViewers() < ptr2->getViewers();
    });
    std::cout << "Top by Views" << std::endl;
    for(int i = 0; i < views.size(); ++i){
        if(auto ptr = views[i].lock()){
            // TODO: Change to .show()
            std::cout << i+1 << ": " << ptr->getTitle() << ' ' << ptr->getId() << ' '
                      << ptr->getViewers();
            //ptr->show();
            std::cout << std::endl;
        }
    }
}

void Platform::topArchivedStreams() {
    archive.showTop();
}

bool Platform::deleteUser(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User *ptr){
        return ptr->getNickname() == nickname;
    });
    if(it == users.end()){
        return false;
    }
    delete (*it);
    users.erase(it);
    return true;
}

void Platform::testMode() {
    test = true;
    stream_id_count = 1;
    for(auto u : users){
        delete u;
    }
    users.clear();
    active_streams.clear();
    archive.testMode();
}

std::vector<std::shared_ptr<Stream>> Platform::testGetStreams() {
    return active_streams;
}
