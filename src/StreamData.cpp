#include "StreamData.h"
#include <iostream>
#include <iomanip>
#include "Input.h"

StreamData::StreamData(unsigned id, const string &title, const string &streamer,const Date &start_date,
                       const Date &end_date,  const string &language, unsigned viewers,
                       bool isPublic, unsigned likes, unsigned dislikes) :
                            id(id), title(title), streamer(streamer), start_date(start_date), end_date(end_date),
                            language(language), viewers(viewers), isPublic(isPublic), likes(likes), dislikes(dislikes) {}

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

std::ostream &StreamData::print(ostream &os) const {
    os << "(" << getId() << ") " << getTitle() << endl
       << "    by " << getStreamer() << endl
       << "    " << (getIsPublic() ? "public" : "private") << " " << getLanguage() << " " << getViewers() << " viewers "
       << getLikes() << " likes " << " " << getDislikes() << " dislikes" << std::endl
       << "    " << getStartDate().toString();
    if(isOver()){
        os << " - " << getEndDate().toString() << endl;
    }
    return os;
}

unsigned StreamData::getLikes() const {
    return likes;
}

unsigned StreamData::getDislikes() const {
    return dislikes;
}

ostream& operator<<(ostream& os, const StreamData &d) {
    return d.print(os);
}

void StreamData::show() const {
    std::cout << std::setw(MAX_NICKNAME_LENGHT) << getStreamer() << " " << std::setw(9) << (getIsPublic() ? "public" : "private") << " " << std::setw(7) << getId() << " " << std::setw(MAX_TITLE_LENGHT) << getTitle() << " " << std::setw(4) << getLanguage() << " " << std::setw(7) << getViewers() << " " << std::setw(7) << getLikes() << " " << std::setw(7) << getDislikes() << " " <<  getStartDate().toString() << " " << getEndDate().toString() << std::endl;
}

bool StreamData::isOver() const{
    return over;
}
