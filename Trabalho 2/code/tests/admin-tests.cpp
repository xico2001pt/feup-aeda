#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Admin.h"
#include "Streamer.h"
#include <string>
using testing::Eq;

TEST(admin, adminTests) {
    Platform pl;
    pl.testMode();
    Admin ad(pl);
    Date d1;
    pl.registerStreamer("st1", "st1", Date("22/06/2001 00:00"));
    pl.registerStreamer("st2", "st2", Date("22/06/2001 00:00"));
    pl.registerViewer("vw1", "vw1", Date("22/06/2001 00:00"));
    pl.registerViewer("vw2", "vw2", Date("22/06/2001 00:00"));
    pl.registerViewer("vw3", "vw3", Date("22/06/2001 00:00"));
    EXPECT_EQ(0, ad.averageViews());

    Streamer * st1 = dynamic_cast<Streamer *>(pl.getUser("st1"));
    Streamer * st2 = dynamic_cast<Streamer *>(pl.getUser("st2"));
    Viewer * vw1 = dynamic_cast<Viewer *>(pl.getUser("vw1"));
    Viewer * vw2 = dynamic_cast<Viewer *>(pl.getUser("vw2"));
    Viewer * vw3 = dynamic_cast<Viewer *>(pl.getUser("vw3"));

    st1->startPrivateStream("str1", "PT", 0, 10, {"vw1","vw2"});
    vw1->joinStream(1);vw2->joinStream(1);
    st1->endStream();
    vw1->leaveStream();vw2->leaveStream();

    st1->startPublicStream("str2", "EN", 0);
    vw1->joinStream(2);vw2->joinStream(2);vw3->joinStream(2);

    st1->endStream();
    vw1->leaveStream();vw2->leaveStream();vw3->leaveStream();

    st2->startPublicStream("str3", "PT", 0);
    vw1->joinStream(3);

    EXPECT_EQ(2, ad.averageViews());
    EXPECT_EQ(2, ad.streamsCounter(true, d1, Date()));
    EXPECT_EQ("PT", ad.topLanguage());
    EXPECT_EQ("public", ad.topTypeStream());
    EXPECT_EQ("st1", ad.topStreamer());
}