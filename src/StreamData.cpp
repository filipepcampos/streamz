#include "StreamData.h"
#include <iostream>
#include <iomanip>
#include "Input.h"

StreamData::StreamData(unsigned id, const string &title, const string &streamer,const Date &start_date,
                       const Date &end_date,  const string &language, unsigned viewers, bool isPublic,
                       unsigned min_age, unsigned likes, unsigned dislikes) :
                            id(id), title(title), streamer(streamer), start_date(start_date), end_date(end_date),
                            language(language), viewers(viewers), min_age(min_age),
                            isPublic(isPublic), likes(likes), dislikes(dislikes) {}

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
    os << std::endl << "    minimum_age: " << getMinAge() << std::endl;
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
    std::cout << std::left << std::setw(MAX_NICKNAME_LENGHT+2) << getStreamer()
        << std::setw(10) << (getIsPublic() ? "public" : "private")
        << std::setw(8) << getId()       << std::setw(MAX_TITLE_LENGHT+2) << getTitle()
        << std::setw(5) << getLanguage() << std::setw(8) << getMinAge()
        << std::setw(8) << getViewers()  << std::setw(8) << getLikes()
        << std::setw(8) << getDislikes() << " "
        << getStartDate().toString() << "  " << (over ? getEndDate().toString() : "")
        << std::endl;
}

unsigned int StreamData::getMinAge() const {
    return min_age;
}
bool StreamData::isOver() const{
    return over;
}

void showStreamsHeader(){
    std::cout << std::left << std::setw(MAX_NICKNAME_LENGHT+2) << "streamer "
              << std::setw(10) << "type "
              << std::setw(8) << "id "
              << std::setw(MAX_TITLE_LENGHT+2) << "title "
              << std::setw(5) << "lang "
              << std::setw(8) << "min_age "
              << std::setw(8) << "views "
              << std::setw(8) << "likes " << std::setw(8) << "dislikes "
              << "start             " << "end " << std::endl;
}