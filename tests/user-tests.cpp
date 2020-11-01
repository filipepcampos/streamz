#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Streamer.h"
#include "Viewer.h"
#include <string>
#include <vector>
using testing::Eq;

TEST(user, getMethods) {
    Date date;
    Platform platform;
    Streamer st("streamer","st name", date, &platform);
    EXPECT_EQ("streamer", st.getNickname());
    EXPECT_EQ("st name", st.getName());
    //EXPECT_EQ(date, st.getBirthDate());

    Viewer vw("viewer","vw name", date, &platform);
    EXPECT_EQ("viewer", vw.getNickname());
    EXPECT_EQ("vw name", vw.getName());
    //EXPECT_EQ(date, vw.getBirthDate());
}

TEST(user, userEquality) {
    Platform platform;
    Streamer st1("MikeG", "Miguel", Date(), &platform);
    Streamer st2("Streamer1", "Streamer Name", Date(), &platform);
    Viewer vw1("Viewer1", "Viewer Name", Date(), &platform);
    std::vector<User *> users;
    users.push_back(&st1);
    users.push_back(&st2);
    users.push_back(&vw1);
    EXPECT_EQ(true, *(users[0]) == *(users[0]));
    EXPECT_EQ(false, *(users[0]) == *(users[1]));
    EXPECT_EQ(false, *(users[1]) == *(users[2]));
}
/*
TEST(user, streamInteraction) {
    std::shared_ptr<Stream> stream1(nullptr);
    stream1 = std::make_shared<Stream>(arguments);
    Viewer vw1("Viewer1", "Viewer Name", Date());

    vw1.joinStream(stream1);
    EXPECT_EQ(id, vw1.getCurrentStream().lock().get().getId());

    vw1.leaveStream();
    EXPECT_EQ(true, vw1.getCurrentStream().expired());
}
*/
TEST(user, streamsHistory) {
    Platform platform;
    Streamer st("Streamer", "Streamer Name", Date(), &platform);
    st.addStream(1);
    st.addStream(3);
    st.addStream(10);
    std::vector<unsigned int> v{1,3,10};
    EXPECT_EQ(v, st.getStreamsHistory());

    st.removeStream(10);
    v.erase(v.begin()+2);
    EXPECT_EQ(v, st.getStreamsHistory());
}