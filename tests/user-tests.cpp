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
    platform.testMode();
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
    platform.testMode();
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

TEST(user, streamInteraction) {
    Platform platform;
    platform.testMode();
    platform.registerStreamer("Streamer1", "Streamer Name", Date());
    platform.registerViewer("Viewer1", "Viewer Name", Date("01/01/2000 00:00"));
    platform.registerViewer("Viewer2", "Viewer Name", Date("01/01/2000 00:00"));

    Streamer * st = dynamic_cast<Streamer*>(platform.getUser("Streamer1"));
    st->startPublicStream("Test", "PT", 10);
    Viewer * vw1 = dynamic_cast<Viewer*>(platform.getUser("Viewer1"));
    vw1->joinStream(0);
    Viewer * vw2 = dynamic_cast<Viewer*>(platform.getUser("Viewer2"));
    vw2->joinStream(0);

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
    vw1->joinStream(0);
    st->endStream();
    EXPECT_EQ(1, st->getStreamsHistory().size());
}

TEST(user, showUser) {
    Platform platform;
    platform.testMode();
    platform.registerStreamer("Streamer1", "Streamer Name", Date());
    platform.registerViewer("Viewer1", "Viewer Name", Date("22/06/2001 00:00"));

    Streamer * st = dynamic_cast<Streamer*>(platform.getUser("Streamer1"));
    cout << *st;
    Viewer * vw1 = dynamic_cast<Viewer*>(platform.getUser("Viewer1"));
    cout << *vw1;
    cout << endl << vw1->getAge() << endl;
}
