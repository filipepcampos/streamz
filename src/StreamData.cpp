#include "StreamData.h"
#include <iostream>

using namespace std;

StreamData::StreamData(const unsigned &id, const string &title, const string &streamer,const Date &start_date, const Date &end_date,  const string &language, const unsigned &viewers, const bool &isPublic): id(id), title(title), streamer(streamer), start_date(start_date), end_date(end_date), language(language), viewers(viewers), isPublic(isPublic) {}

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

ostream& StreamData::operator<<(ostream& os) const{
    os << "stream data: " << getIsPublic() << " " << getId() << " " << getTitle() << " " << getStreamer() << " " << getStartDate().toString() << " " << getEndDate().toString() << " " << getLanguage() << " " << getViewers() << endl;
    return os;
}

