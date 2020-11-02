#include "Archive.h"
#include <algorithm>
#include <iostream>

Archive::Archive(const string &filename) {
    // TODO: Read data
}

Archive::~Archive(){
    // TODO: Store data
    if(!test){
        ;
    }
}

unsigned int Archive::getStreamCount() const {
    return streams.size();
}

void Archive::show() {
    for(const auto &data : streams){
        // TODO: Change to .show()
        std::cout << data.getId() << " " << data.getTitle() << " " << data.getViewers() << std::endl;
    }
}

void Archive::showTop() {
    std::cout << "Top by Views:" << std::endl;
    for(auto it = top_views.rbegin(); it!= top_views.rend(); ++it){
        // TODO: Change to .show()
        std::cout << it->getId() << " " << it->getTitle() << " " << it->getViewers() << std::endl;
    }
    // TODO add likes
}

void Archive::showStreamsById(const std::vector<unsigned int> &ids) {
    for(auto id : ids){
        for(StreamData &data : streams){
            if(data.getId() == id){
                // TODO: Uncomment
                //data.show();
            }
        }
    }
}

void Archive::archiveStream(const StreamData &data) {
    streams.push_back(data);
    updateTop(data);
}

void Archive::updateTop(const StreamData &data){
    auto views_it = std::lower_bound(top_views.begin(), top_views.end(), data.getViewers(), [](const StreamData &d, unsigned int viewers){
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