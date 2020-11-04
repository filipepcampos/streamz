#include "Archive.h"
#include <algorithm>
#include <iostream>

Archive::Archive(const string &filename) {
    // TODO: Read data
}

Archive::~Archive(){
    // TODO: Store data
    if(!test){
        ;//
    }
}

unsigned int Archive::getStreamCount() const {
    return streams.size();
}

void Archive::show() {
    for(const auto &data : streams){
        data.show();
    }
}

void Archive::showTop() {
    std::cout << "Top by Views:" << std::endl;
    for(auto it = top_views.rbegin(); it!= top_views.rend(); ++it){
        (*it).show();
    }
    // TODO add likes
}

void Archive::showStream(unsigned int id) {
    int pos = binarySearch(id);
    if(pos != -1) {
        // TODO: Uncomment
        //streams[pos].show();
    }
}

std::vector<StreamData *> Archive::getStreamsById(const std::vector<unsigned int> &ids) {
    std::vector<StreamData *> vec;
    for(auto id : ids){
        int pos = binarySearch(id);
        if(pos != -1){
            vec.push_back(&streams[pos]);
        }
    }
    return vec;
}

int Archive::binarySearch(unsigned int id) {
    int left = 0, right = streams.size()-1;
    while (left <= right) {
        int m = left + (right - left) / 2;
        unsigned int current_id = streams[m].getId();
        if (current_id == id)
            return m;
        if (current_id < id)
            left = m + 1;
        else
            right = m - 1;
    }
    return -1;
}

void Archive::archiveStream(const StreamData &data) {
    auto it = std::lower_bound(streams.begin(), streams.end(), data.getId(),
                       [](const StreamData &d, unsigned int id){
                           return d.getId() < id;
                       });
    streams.insert(it, data);
    updateTop(data);
}

void Archive::updateTop(const StreamData &data){
    auto views_it = std::lower_bound(top_views.begin(), top_views.end(), data.getViewers(),  [](const StreamData &d, unsigned int viewers){
        return d.getViewers() < viewers;
    });
    if(views_it != top_views.begin()){
        top_views.insert(views_it, data);
        top_views.pop_back();
    }
    // TODO Implement likes
    /*
    auto likes_it = std::lower_bound(top_archived.likes.begin(), top_archived.likes.end(), [data](StreamData &d){
        return d.getLikes() < data;
    });
    if(likes_it != top_archived.likes.begin()){
        top_archived.likes.insert(likes_it, data);
        top_archived.likes.pop_back();*/
}

void Archive::testMode(){
    test = true;
    top_views.clear();
    top_likes.clear();
    streams.clear();
}