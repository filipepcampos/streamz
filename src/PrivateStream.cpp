#include "PrivateStream.h"
#include <iostream>
#include <algorithm>

using namespace std;

PrivateStream::PrivateStream(const string &title, const string &streamer, const string &language, const unsigned int id, const unsigned int minimum_age, const unsigned int max_capacity, const vector<string> &allowed_viewers) : Stream(title, streamer, language, id, minimum_age), max_capacity(max_capacity), allowed_viewers(allowed_viewers) {
    isPublic = false;
}

PrivateStream::PrivateStream(const string &title, const string &streamer, const string &language, unsigned int id,
                             const unsigned int minimum_age, const unsigned int max_capacity, const vector<string> &allowed_viewers,
                             unsigned int likes, unsigned int dislikes,
                             const std::string &start_date, const std::vector<Comment> &comments) :
                                 Stream(title, streamer, language, id, minimum_age, likes, dislikes, start_date),
                                 max_capacity(max_capacity), allowed_viewers(allowed_viewers), comments(comments) {
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

ostream& PrivateStream::print(ostream & os) const{
    Stream::print(os);
    os << "    " << "maximum_capacity: " << max_capacity << " allowed_users: ";
    for (int i = 0; i < allowed_viewers.size(); i++)
        os << allowed_viewers.at(i) << " ";
    os << std::endl;
    for (int n = 0; n < comments.size(); n++)
        os << "      " << comments.at(n).date.toString() << " " << comments.at(n).nickname << " \"" << comments.at(n).comment << "\"" << std::endl;
    return os;
}

void PrivateStream::addComment(Viewer &viewer, const string &comment){
    Comment comentario;
    comentario.date = Date();
    comentario.nickname = viewer.getNickname();
    comentario.comment = comment;
    comments.push_back(comentario);
}

void PrivateStream::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    cout << "IMPLEMENTAR MAIS TARDE" << endl;
}

