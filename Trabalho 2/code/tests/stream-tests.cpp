#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StreamData.h"
#include "Stream.h"
#include "PrivateStream.h"
#include <string>
using testing::Eq;

TEST(stream, streamTests) {
    Platform platform;
    platform.testMode();
    Stream st("title", "loltyler1", "english", 10, 16);
    st.giveDislike();
    st.giveLike();
    EXPECT_EQ("loltyler1", st.getStreamer());
    EXPECT_EQ("english", st.getLanguage());
    EXPECT_EQ(16, st.getMinAge());
    EXPECT_EQ(1, st.getLikes());
    EXPECT_EQ(1, st.getDislikes());
}

TEST(private_stream, privateStreamTests){
    Platform platform;
    platform.testMode();
    PrivateStream pst("title", "loltyler1", "english", 10, 16, 300, {"aaaa", "babaab", "adadf"}, 0, 0, Date().toString(), {});
    Viewer viewer("aaaa", "Vasco", Date("29/02/2004 12:30"), platform);
    EXPECT_EQ(true, pst.canJoin(viewer));
    pst.addComment(viewer, "nao jogas nada");
    EXPECT_EQ("nao jogas nada", pst.getComments().at(0).comment);
    EXPECT_EQ("aaaa", pst.getComments().at(0).nickname);
}

