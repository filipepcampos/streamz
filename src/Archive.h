#ifndef STREAMZ_ARCHIVE_H
#define STREAMZ_ARCHIVE_H
#include "StreamData.h"
#include <vector>
#include <list>


class Archive {
private:
    bool test = false;
    std::string filename;
    std::vector<StreamData> streams;
    std::list<StreamData> top_views;
    std::list<StreamData> top_likes;
public:
    Archive(const string &filename = "archive.txt");
    ~Archive();
    void archiveStream(const StreamData &data);
    void updateTop(const StreamData &data);
    unsigned int getStreamCount() const;
    void show();
    void showTop();
    void testMode();
};


#endif //STREAMZ_ARCHIVE_H
