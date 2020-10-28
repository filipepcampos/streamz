#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Platform.h"
using testing::Eq;

TEST(platform, reset){
    Platform platform;
    platform.reset();
    EXPECT_EQ(platform.getUserCount(), 0);
    EXPECT_EQ(platform.getActiveStreamCount(), 0);
    EXPECT_EQ(platform.getTotalStreamCount(), 0);
}

TEST(platform, registerUniqueUsers) {
    Platform platform;
    platform.reset();
    EXPECT_EQ(platform.getUserCount(), 0);
    for(int i = 0; i < 30; i+=2) {
        EXPECT_EQ(platform.registerViewer("user" + std::to_string(i), "abc", Date()), true);
        EXPECT_EQ(platform.registerStreamer("user" + std::to_string(i+1), "abc", Date()), true);
        EXPECT_EQ(platform.getUserCount(), i + 2);
    }
}

TEST(platform, registerNonUniqueUsers){
    Platform platform;
    platform.reset();
    std::string name = "name"; Date date;

    EXPECT_EQ(platform.registerViewer("user1", name, date), true);
    EXPECT_THROW(platform.registerViewer("user1", name, date), UserAlreadyExists);

    EXPECT_EQ(platform.registerStreamer("user2", name, date), true);
    EXPECT_THROW(platform.registerStreamer("user2", name, date), UserAlreadyExists);

    EXPECT_EQ(platform.registerViewer("user3", name, date), true);
    EXPECT_THROW(platform.registerStreamer("user3", name, date), UserAlreadyExists);

    EXPECT_EQ(platform.registerStreamer("user4", name, date), true);
    EXPECT_THROW(platform.registerViewer("user4", name, date), UserAlreadyExists);

    EXPECT_EQ(platform.registerViewer("user5", name, date), true);
    for(int i = 0; i < 10; ++i){
        EXPECT_THROW(platform.registerViewer("user5", name, date), UserAlreadyExists);
    }
}

TEST(platform, getUsers){
    Platform platform;
    platform.reset();
    std::string name = "name"; Date date;
    for(int i = 0; i < 30; i+=2) {
        EXPECT_EQ(platform.registerViewer("user" + std::to_string(i), name, date), true);
        EXPECT_EQ(platform.registerStreamer("user" + std::to_string(i+1), name, date), true);
        EXPECT_EQ(platform.getUserCount(), i + 2);
    }
    for(int i = 0; i < 30; i++){
        User * user = platform.getUser("user" + std::to_string(i));
        EXPECT_EQ(user->getNickname(), "user" + std::to_string(i));
    }
    EXPECT_THROW(platform.getUser("user50"), UserDoesNotExist);
}

TEST(platform, showUsers){
    Platform platform;
    std::string name = "Name"; Date date;
    platform.reset();
    std::cout << " --- Please verify the following information --- " << std::endl;
    for(int i = 0; i < 10; ++i) {
        platform.registerViewer("viewer" + std::to_string(i), name, date);
    }
    for(int i = 10; i < 15; ++i){
        platform.registerStreamer("streamer" + std::to_string(i), name, date);
    }
    platform.showUsers();
}

TEST(platform, showStreams){
    Platform platform;
    platform.reset();
    GTEST_SKIP();
    std::cout << " --- Please verify the following information --- " << std::endl;
    for(int i = 0; i < 10; ++i){

    }
}