#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Archive.h"
using testing::Eq;

TEST(archive, test_mode) {
    Archive archive;
    archive.testMode();
    EXPECT_EQ(archive.getStreamCount(), 0);
}

TEST(archive, addStream){
    Archive archive;
    archive.testMode();
    const unsigned N_STREAMS = 50;
    srand(time(0));
    for(int i = 0; i < N_STREAMS; ++i){
        unsigned int viewers = rand() % 5000;
        bool is_public = rand() % 2;
        archive.archiveStream(StreamData(i,"title"+std::to_string(i), "streamer", Date(), Date(), "PT", viewers, is_public));
    }
    archive.showStream(5);
    EXPECT_EQ(archive.getStreamCount(), N_STREAMS);
}

TEST(archive, show){
    Archive archive;
    archive.testMode();
    const unsigned N_STREAMS = 50;
    srand(time(0));
    for(int i = 0; i < N_STREAMS; ++i){
        unsigned int viewers = rand() % 5000;
        bool is_public = rand() % 2;
        archive.archiveStream(StreamData(i,"title"+std::to_string(i), "streamer", Date(), Date(), "PT", viewers, is_public));
    }
    EXPECT_EQ(archive.getStreamCount(), N_STREAMS);
    std::cout << "  ---  Verify the following information  ---\n";
    archive.show();
    std::cout << "  --- Top --- \n";
    archive.showTop();
}

TEST(archive, streamsById){
    Archive archive;
    archive.testMode();
    const unsigned N_STREAMS = 50;
    srand(time(0));

    std::vector<unsigned int> ids;

    for(int i = 0; i < N_STREAMS; ++i){
        unsigned int viewers = rand() % 5000;
        bool is_public = rand() % 2;
        if(rand() % 3 == 0){
            ids.push_back(i);
        }
        archive.archiveStream(StreamData(i,"title"+std::to_string(i), "streamer", Date(), Date(), "PT", viewers, is_public));
    }

    std::vector<const StreamData *> vec = archive.getStreamsById(ids);
    EXPECT_EQ(ids.size(), vec.size());
    for(int i = 0; i < ids.size(); ++i){
        if(vec[i]->getId() != ids[i]){
            GTEST_FAIL();
        }
    }

    std::vector<unsigned int> empty_ids;
    EXPECT_EQ(archive.getStreamsById(empty_ids).size(), 0);

    std::vector<unsigned int> out_of_range_ids = {99921, 7213, 721349};
    EXPECT_EQ(archive.getStreamsById(out_of_range_ids).size(), 0);
}