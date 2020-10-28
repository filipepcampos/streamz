#include "Platform.h"
#include <iostream>
#include <algorithm>

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
    return archived_streams.size();
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
    auto it = std::find_if(active_streams.begin(), active_streams.end(), [id](std::shared_ptr<Stream> ptr){
        return ptr->getId() == id;
    });
    if(it == active_streams.end()){
        throw id <= stream_id_count ? StreamNoLongerActive(id) : StreamDoesNotExist(id);
    }
    StreamData data = *(*it);
    */
}

void Platform::reset() {
    users.clear();
    active_streams.clear();
    archived_streams.clear();
}