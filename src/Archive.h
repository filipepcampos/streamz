#ifndef STREAMZ_ARCHIVE_H
#define STREAMZ_ARCHIVE_H
#include "StreamData.h"
#include <vector>
#include <list>


class Archive {
private:
    friend class Admin;
    bool test = false;
    std::string filename;
    std::vector<StreamData> streams;
    std::list<StreamData> top_views;
    std::list<StreamData> top_likes;

    int binarySearch(unsigned int id) const;
public:
    explicit Archive(const string &filename = "archive.txt");
    ~Archive();
    void archiveStream(const StreamData &data);
    void updateTop(const StreamData &data);
    unsigned int getStreamCount() const;
    void show() const;
    void showTop() const;
    void showStream(unsigned int id) const;
    std::vector<const StreamData *> getStreamsById(const std::vector<unsigned int> &ids) const;
    void testMode();
};


#endif //STREAMZ_ARCHIVE_H
