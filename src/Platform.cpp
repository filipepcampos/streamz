#include "Platform.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>

Platform::Platform() {
    std::string line;
    std::ifstream users_file(files.user_file);
    if(users_file.is_open()){
        std::getline(users_file, line);
        while(std::getline(users_file, line)){
            std::string nickname, name;
            std::istringstream ss{line};
            ss >> nickname;
            std::getline(ss, name);
            // TODO: Change to correct class
            users.push_back(new Viewer(nickname, name, Date()));
        }
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
        users_file << "=====================" << std::endl;
        for(auto user : users){
            users_file << user->getNickname() << " " << user->getName() << std::endl;
        }
        users_file.close();
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
    users.push_back(new Streamer(nickname, name, birth_date));
    return true;
}

bool Platform::registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date) {
    if(userExists(nickname)){
        throw UserAlreadyExists(nickname);
    }
    users.push_back(new Viewer(nickname, name, birth_date));
    return true;
}

unsigned int Platform::getUserCount() const{
    return users.size();
}
unsigned int Platform::getActiveStreamCount() const{
    return active_streams.size();
}
unsigned int Platform::getTotalStreamCount() const{
    return active_streams.size() + archived_streams.size();
}


void Platform::showStreams() {
    std::cout << "NOT IMPLEMENTED" << std::endl;
    for(int i = 0; i < active_streams.size(); ++i){
        std::cout << i+1 << ": " << std::endl;
    }
}

void Platform::showUsers() {
    for(int i = 0; i < users.size(); ++i){
        std::cout << i+1 << ": ";
        users[i]->show();
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

std::weak_ptr<Stream> Platform::joinStream(int p, Viewer &viewer) {
    p--;
    if(p < 0 || p >= active_streams.size()){
        throw std::out_of_range("Invalid index for active_streams");
    }
    std::weak_ptr<Stream> ptr = active_streams[p];

    try{
        std::cout << "NOT IMPLEMENTED" << std::endl;
        /*
        ptr->join(viewer);
        return ptr; */
    }
    catch(const InsufficientAge &e){
        throw;
    }
    return std::weak_ptr<Stream>();
}

std::weak_ptr<Stream> Platform::startStream(Streamer &streamer){
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return std::weak_ptr<Stream>();
}

void Platform::endStream(unsigned int id){
    std::cout << "NOT IMPLEMENTED" << std::endl;
    /*
    auto stream_it = std::find_if(active_streams.begin(), active_streams.end(), [id](std::shared_ptr<Stream> ptr){
        return ptr->getId() == id;
    });
    if(stream_it == active_streams.end()){
        throw id <= stream_id_count ? StreamNoLongerActive(id) : StreamDoesNotExist(id);
    }
    StreamData data = (*stream_it).get();
    updateArchivedTop(data);*/
}

void Platform::updateArchivedTop(StreamData &data) {
    /*
    auto views_it = std::lower_bound(archived_top10_views.begin(), archived_top10_views.end(), [data](StreamData &d){
        return d.getViews() < data;
    });
    if(views_it != archived_top10_views.begin()){
        archived_top10_views.insert(views_it, data);
        archived_top10_views.pop_back();
    }
    auto likes_it = std::lower_bound(archived_top10_likes.begin(), archived_top10_likes.end(), [data](StreamData &d){
        return d.getLikes() < data;
    });
    if(likes_it != archived_top10_likes.begin()){
        archived_top10_likes.insert(likes_it, data);
        archived_top10_likes.pop_back();
    }*/
}

template <typename F>
std::vector<std::weak_ptr<Stream>> Platform::getTop(F function){
    // TODO: Test this function;
    std::vector<std::weak_ptr<Stream>> top10;
    if(getActiveStreamCount() > 10){
        top10.reserve(10);
        std::stack<decltype(active_streams.begin())> s;
        // Custom insertion sort, where 10 greatest elements are inserted into the first 10 index
        for(auto it = active_streams.begin(); it != active_streams.begin() + 10; ++it){
            auto max_it = std::max_element(it, active_streams.end(), function);
            s.emplace(max_it);
            std::iter_swap(it, max_it);
        }
        for(int i = 0; i < 10; ++i){
            top10.emplace_back(active_streams[i]);
        }
        // Unwind the changes made, restoring original vector state
        auto it = active_streams.begin() + 10;
        for(int i = 0; i < 10; ++i, --it){
            std::iter_swap(s.top(), it);
            s.pop();
        }
    }
    else{
        top10.reserve(active_streams.size());
        for(auto &ptr : active_streams){
            top10.emplace_back(ptr);
        }
    }
    return top10;
}

void Platform::topActiveStreams() {
    std::cout << "NOT IMPLEMENTED" << std::endl;
    /*
    std::vector<std::weak_ptr<Stream>> likes = getTop([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
        return ptr1->getLikes() < ptr2->getLikes();
    });
    std::vector<std::weak_ptr<Stream>> views = getTop([](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
        return ptr1->getViews() < ptr2->getViews();
    });
     */
}

void Platform::topArchivedStreams() {
    std::cout << "NOT IMPLEMENTED" << std::endl;
}

bool Platform::deleteUser(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User *ptr){
        return ptr->getNickname() == nickname;
    });
    if(it == users.end()){
        return false;
    }
    users.erase(it);
    return true;
}

void Platform::test_mode() {
    test = true;
    users.clear();
    active_streams.clear();
    archived_streams.clear();
    archived_top10_likes.clear();
    archived_top10_views.clear();
}