#include "Stream.h"
#include <iostream>

using namespace std;


Stream::Stream(const string &title, const string &streamer, const string &language, unsigned int id,const unsigned int minimum_age): StreamData(id,title,streamer,start_date,end_date,language,0,true,0,0){
    this->minimum_age = minimum_age;
}

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

void Stream::giveDislike() {
    dislikes++;
}

void Stream::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    cout << "IMPLEMENTAR MAIS TARDE" << endl;
}

ostream& operator<<(ostream& os, const Stream& stream){
    stream.print(os);
    return os;
}

ostream& Stream::print(ostream & os) const{
    os << "stream: " << getIsPublic() << " " << getId() << " " << getTitle() << " " << getStreamer() << " " << getStartDate().toString() << " " << getEndDate().toString() << " " << getLanguage() << " " << getViewers() << " " << getLikes() << " " << getDislikes() << " " << minimum_age << endl;
    return os;
}

void Stream::endStream(){
    end_date = Date();
}

unsigned Stream::getMinimumAge() const {
    return minimum_age;
}

