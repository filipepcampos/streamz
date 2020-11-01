#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Archive.h"
#include "Platform.h"
using testing::Eq;

TEST(archive, test_mode) {
    Archive archive;
    archive.testMode();
    EXPECT_EQ(archive.getStreamCount(), 0);
}

TEST(archive, addStream){
    ;
}