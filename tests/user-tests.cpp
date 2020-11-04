#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Streamer.h"
#include "Viewer.h"
#include <string>
#include <vector>
using testing::Eq;

TEST(user, getMethods) {
    Platform platform;
    platform.testMode();
    Streamer st("streamer","st name", Date("22/06/2001 00:00"), &platform);
    EXPECT_EQ("streamer", st.getNickname());
    EXPECT_EQ("st name", st.getName());

    Viewer vw("viewer","vw name", Date("22/06/2001 00:00"), &platform);
    EXPECT_EQ("viewer", vw.getNickname());
    EXPECT_EQ("vw name", vw.getName());
}

TEST(user, userEquality) {
    Platform platform;
    platform.testMode();
    Streamer st1("MikeG", "Miguel", Date("22/06/2001 00:00"), &platform);
    Streamer st2("Streamer1", "Streamer Name", Date("22/06/2001 00:00"), &platform);
    Viewer vw1("Viewer1", "Viewer Name", Date("22/06/2001 00:00"), &platform);
    std::vector<User *> users;
    users.push_back(&st1);
    users.push_back(&st2);
    users.push_back(&vw1);
    EXPECT_EQ(true, *(users[0]) == *(users[0]));
    EXPECT_EQ(false, *(users[0]) == *(users[1]));
    EXPECT_EQ(false, *(users[1]) == *(users[2]));
}

TEST(user, streamInteraction) {
    Platform platform;
    platform.testMode();
    platform.registerStreamer("Streamer1", "Streamer Name", Date("22/06/2001 00:00"));
    platform.registerViewer("Viewer1", "Viewer Name", Date("01/01/2000 00:00"));
    platform.registerViewer("Viewer2", "Viewer Name", Date("01/01/2000 00:00"));

    Streamer * st = dynamic_cast<Streamer*>(platform.getUser("Streamer1"));
    st->startPublicStream("Test", "PT", 10);
    Viewer * vw1 = dynamic_cast<Viewer*>(platform.getUser("Viewer1"));
    vw1->joinStream(1);
    Viewer * vw2 = dynamic_cast<Viewer*>(platform.getUser("Viewer2"));
    vw2->joinStream(1);

    EXPECT_EQ(2, vw1->getCurrentStream().lock()->getViewers());

    vw2->leaveStream();
    EXPECT_EQ(1, vw1->getCurrentStream().lock()->getViewers());
}

TEST(user, streamsHistory) {
    Platform platform;
    platform.testMode();
    platform.registerStreamer("Streamer1", "Streamer Name", Date("01/01/2000 00:00"));
    platform.registerViewer("Viewer1", "Viewer Name", Date("01/01/2000 00:00"));
    platform.registerViewer("Viewer2", "Viewer Name", Date("01/01/2000 00:00"));

    Streamer * st = dynamic_cast<Streamer*>(platform.getUser("Streamer1"));
    st->startPublicStream("Test", "PT", 10);
    Viewer * vw1 = dynamic_cast<Viewer*>(platform.getUser("Viewer1"));
    vw1->joinStream(1);
    st->endStream();
    EXPECT_EQ(1, st->getStreamsHistory().size());
}

TEST(user, showUser) {
    Platform platform;
    platform.testMode();
    platform.registerStreamer("Streamer1", "Streamer Name", Date("22/06/2001 00:00"));
    platform.registerViewer("Viewer1", "Viewer Name", Date("22/06/2001 00:00"));

    Streamer * st = dynamic_cast<Streamer*>(platform.getUser("Streamer1"));
    cout << *st;
    Viewer * vw1 = dynamic_cast<Viewer*>(platform.getUser("Viewer1"));
    cout << *vw1;
    cout << endl << vw1->getAge() << endl;
}
