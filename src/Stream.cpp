#include "Stream.h"
#include <iostream>

using namespace std;


Stream::Stream(const string &title, const string &streamer, const string &language, unsigned int id,const unsigned int minimum_age): StreamData(id,title,streamer,start_date,end_date,language,0,true){
    this->minimum_age = minimum_age;
}

bool Stream::canJoin(Viewer &viewer){
    return (viewer.getAge() >= minimum_age);
}

void Stream::joinStream(){
    viewers++;
}

void Stream::leaveStream(){
    viewers--;
}

void Stream::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    cout << "IMPLEMENTAR MAIS TARDE" << endl;
}

void Stream::endStream(){
    Date date;
    end_date = date;
}
