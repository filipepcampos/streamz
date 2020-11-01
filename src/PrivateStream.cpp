#include "PrivateStream.h"
#include <iostream>
#include <algorithm>

using namespace std;

PrivateStream::PrivateStream(const string &title, const string &streamer, const string &language, unsigned int id, const unsigned int minimum_age, const unsigned int max_capacity, const vector<string> allowed_viewers) : Stream(title, streamer, language, id, minimum_age), max_capacity(max_capacity), allowed_viewers(allowed_viewers) {
    isPublic = false;
}

bool PrivateStream::canJoin(Viewer &viewer){
    string nickname = viewer.getNickname();
    if (viewers < max_capacity)
        if (Stream::canJoin(viewer))
            if (find(allowed_viewers.begin(),allowed_viewers.end(),nickname) != allowed_viewers.end())
                return true;
    return false;
}

void PrivateStream::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    cout << "IMPLEMENTAR MAIS TARDE" << endl;
}
