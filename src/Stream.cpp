#include "Stream.h"
#include <iostream>
#include <iomanip>

using namespace std;


Stream::Stream(const string &title, const string &streamer, const string &language, unsigned int id,
               const unsigned int minimum_age) :
                        StreamData(id,title,streamer,Date(),end_date,language,0,true),
                        minimum_age(minimum_age) {}

Stream::Stream(const string &title, const string &streamer, const string &language, unsigned int id,
               const unsigned int minimum_age, unsigned int likes, unsigned int dislikes,
               const std::string &start_date) :
                        StreamData(id,title,streamer,Date(start_date),end_date,language,0,true,
                                   likes, dislikes),
                        minimum_age(minimum_age) {}

bool Stream::canJoin(const Viewer &viewer){
    return (viewer.getAge() >= minimum_age);
}

void Stream::joinStream(){
    viewers++;
}

void Stream::leaveStream(){
    viewers--;
}

void Stream::giveLike() {
    likes++;
}

void Stream::removeLike() {
    likes--;
}

void Stream::giveDislike() {
    dislikes++;
}

void Stream::removeDislike() {
    dislikes--;
}

void Stream::show() const {
    std::cout << std::setw(10) << getStreamer() << std::setw(9) << getIsPublic() << std::setw(7) << getId() << std::setw(20) << getTitle() << std::setw(4) << getLanguage() << std::setw(7) << getViewers() << std::endl;
}

ostream& operator<<(ostream& os, const Stream& stream){
    return stream.print(os);
}

ostream& Stream::print(ostream & os) const{
    StreamData::print(os);
    os << std::endl << "    minimum_age: " << getMinimumAge() << std::endl;
    return os;
}

void Stream::endStream(){
    end_date = Date();
    over = true;
}

unsigned Stream::getMinimumAge() const {
    return minimum_age;
}

