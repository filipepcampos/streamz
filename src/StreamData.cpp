#include "StreamData.h"
#include <iostream>

using namespace std;

StreamData::StreamData(const unsigned &id, const string &title, const string &streamer,const Date &start_date, const Date &end_date,  const string &language, const unsigned &viewers, const bool &isPublic, const unsigned &likes, const unsigned &dislikes): id(id), title(title), streamer(streamer), start_date(start_date), end_date(end_date), language(language), viewers(viewers), isPublic(isPublic), likes(likes), dislikes(dislikes) {}

unsigned StreamData::getId() const{
    return id;
}

string StreamData::getTitle() const{
    return title;
}

string StreamData::getStreamer() const{
    return streamer;
}

Date StreamData::getStartDate() const{
    return start_date;
}

Date StreamData::getEndDate() const{
    return end_date;
}

string StreamData::getLanguage() const{
    return language;
}

unsigned StreamData::getViewers() const{
    return viewers;
}

bool StreamData::getIsPublic() const {
    return isPublic;
}

unsigned StreamData::getLikes() const {
    return likes;
}

unsigned StreamData::getDislikes() const {
    return dislikes;
}

ostream& operator<<(ostream& os, const StreamData &d) {
    os << "(" << d.getId() << ") " << d.getTitle() << endl
        << "    by " << d.getStreamer() << endl
        << "    " << (d.getIsPublic() ? "public" : "private") << " " << d.getLanguage() << " " << d.getViewers() << endl
        //<< "    " << d.getLikes() << " " << d.getDislikes() << endl
        << "    " << d.getStartDate().toString() << " - " << d.getEndDate().toString() << endl;
    return os;
}

void StreamData::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    cout << "IMPLEMENTAR MAIS TARDE" << endl;
}

