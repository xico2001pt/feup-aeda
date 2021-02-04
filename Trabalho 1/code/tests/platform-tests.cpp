#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Platform.h"
#include "Streamer.h"
using testing::Eq;

TEST(platform, test_mode){
    Platform platform;
    platform.registerViewer("viewer", "Name", Date("01/01/1984 00:00"));
    platform.registerStreamer("streamer", "Name", Date("01/01/1984 00:00"));
    platform.testMode();
    EXPECT_EQ(platform.getUserCount(), 0);
    EXPECT_EQ(platform.getActiveStreamCount(), 0);
    EXPECT_EQ(platform.getTotalStreamCount(), 0);
}

TEST(platform, registerUniqueUsers) {
    Platform platform;
    platform.testMode();
    EXPECT_EQ(platform.getUserCount(), 0);
    for(int i = 0; i < 30; i+=2) {
        EXPECT_EQ(platform.registerViewer("user" + std::to_string(i), "abc", Date("01/01/1984 00:00")), true);
        EXPECT_EQ(platform.registerStreamer("user" + std::to_string(i+1), "abc", Date("01/01/1984 00:00")), true);
        EXPECT_EQ(platform.getUserCount(), i + 2);
    }
}

TEST(platform, registerNonUniqueUsers){
    Platform platform;
    platform.testMode();
    std::string name = "name"; Date date("01/01/1984 00:00");

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
    platform.testMode();
    std::string name = "name"; Date date("01/01/1984 00:00");
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

TEST(platform, deleteUsers){
    Platform platform;
    platform.testMode();
    std::string name = "Name"; Date date("01/01/1984 00:00");

    EXPECT_EQ(platform.registerStreamer("streamer1", name, date), true);
    EXPECT_EQ((platform.getUser("streamer1")->getNickname()), "streamer1");
    EXPECT_EQ(platform.deleteUser("streamer1"), true);
    EXPECT_THROW(platform.getUser("streamer1"), UserDoesNotExist);

    EXPECT_EQ(platform.deleteUser("user"), false);
}

TEST(platform, showUsers){
    Platform platform;
    platform.testMode();
    std::string name = "Name"; Date date("01/01/1984 00:00");

    std::cout << " --- Please verify the following information --- " << std::endl;
    for(int i = 0; i < 10; ++i) {
        platform.registerViewer("viewer" + std::to_string(i), name, date);
    }
    for(int i = 10; i < 15; ++i){
        platform.registerStreamer("streamer" + std::to_string(i), name, date);
    }
    platform.showUsers();
}

TEST(platform, startStream){
    Platform platform;
    platform.testMode();
    EXPECT_EQ(platform.registerStreamer("streamer1", "Name", Date("01/01/1984 00:00")), true);
    Streamer * streamer = dynamic_cast<Streamer *>(platform.getUser("streamer1"));
    platform.startPublicStream("title", streamer->getName(), "PT", 15);
    std::vector<std::string> allowed;
    platform.startPrivateStream("title", streamer->getName(), "PT", 15, 5, allowed);
}

TEST(platform, joinStream){
    Platform platform;
    platform.testMode();
    platform.registerViewer("viewer", "Name", Date("01/01/1984 00:00"));
    Viewer * viewer = dynamic_cast<Viewer *>(platform.getUser("viewer"));
    EXPECT_THROW(platform.joinStream("abc", *viewer), StreamerNotStreaming);
    EXPECT_THROW(platform.joinStream(9999, *viewer), StreamDoesNotExist);
    EXPECT_THROW(platform.joinStream(0, *viewer), StreamDoesNotExist);
    platform.startPublicStream("title", "nickname", "PT", 5);
    EXPECT_NO_THROW(platform.joinStream("nickname",*viewer));
    viewer->leaveStream();
    EXPECT_NO_THROW(platform.joinStream(1, *viewer));
    viewer->leaveStream();
    platform.endStream(1);
    EXPECT_THROW(platform.joinStream(1, *viewer), StreamNoLongerActive);
    EXPECT_THROW(platform.joinStream("nickname", *viewer), StreamerNotStreaming);
}

TEST(platform, endStream){
    Platform platform;
    platform.testMode();
    EXPECT_THROW(platform.endStream(0), StreamDoesNotExist);
    EXPECT_THROW(platform.endStream(1), StreamDoesNotExist);
    platform.startPublicStream("title", "nickname", "PT", 5);
    EXPECT_EQ(platform.getArchivedStreamCount(), 0);
    EXPECT_EQ(platform.getActiveStreamCount(), 1);
    platform.endStream(1);
    EXPECT_EQ(platform.getActiveStreamCount(), 0);
    EXPECT_EQ(platform.getArchivedStreamCount(), 1);
    EXPECT_THROW(platform.endStream(0), StreamDoesNotExist);
    EXPECT_THROW(platform.endStream(1), StreamNoLongerActive);
}

TEST(platform, top10){
    srand(time(nullptr));
    Platform platform;
    platform.testMode();
    std::cout << "Should be empty:" << std::endl;
    platform.topActiveStreams();
    platform.registerStreamer("streamer", "Name", Date("01/01/1984 00:00"));
    Streamer * streamer = dynamic_cast<Streamer *>(platform.getUser("streamer"));

    for(int i = 0; i < 30; ++i){
        platform.startPublicStream("title" + std::to_string(i), streamer->getName(), "pt", 10);
    }

    std::vector<std::shared_ptr<Stream>> vec = platform.testGetStreams();

    Viewer viewer("abc","name",Date("01/01/1984 00:00"), platform);
    for(int i = 0; i < 1500; ++i){
        platform.joinStream(1 + rand() % platform.getActiveStreamCount(), viewer);
    }
    platform.topActiveStreams();

    std::vector<std::shared_ptr<Stream>> new_vec = platform.testGetStreams();
    if(new_vec.size() != vec.size()){
        GTEST_FAIL();
    }
    for(int i = 0; i < vec.size(); ++i){
        if(new_vec[i]->getId() != vec[i]->getId()){
            GTEST_FAIL();
        }
    }
}

TEST(platform, sorting){
    srand(time(0));
    Platform platform;
    platform.testMode();
    const int N_STREAMS = 500;
    const int N_VIEWERS = 1500;
    for(int i = 0; i < N_STREAMS; ++i){
        platform.startPublicStream("title" + std::to_string(i), "streamer" + std::to_string(i), "PT", i);
    }
    for(int i = 0; i < N_VIEWERS; ++i){
        platform.registerViewer("viewer" + std::to_string(i), "Name", Date("01/01/1984 00:00"));
        Viewer * viewer = dynamic_cast<Viewer *>(platform.getUser("viewer" + std::to_string(i)));
        viewer->joinStream(1 + rand() % (N_STREAMS-1));
    }

    platform.sort(likes, ascending);
    std::vector<std::shared_ptr<Stream>> vec = platform.testGetStreams();
    unsigned old_val = 0;
    for(const auto &ptr : vec){
        if(ptr->getLikes() < old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getLikes();
    }
    platform.sort(likes, descending);
    vec = platform.testGetStreams();
    old_val = 999999999;
    for(const auto &ptr : vec) {
        if (ptr->getLikes() > old_val) {
            GTEST_FAIL();
        }
        old_val = ptr->getLikes();
    }

    platform.sort(views, ascending);
    vec = platform.testGetStreams();
    old_val = 0;
    for(const auto &ptr : vec){
        if(ptr->getViewers() < old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getViewers();
    }
    platform.sort(views, descending);
    vec = platform.testGetStreams();
    old_val = 999999999;
    for(const auto &ptr : vec){
        if(ptr->getViewers() > old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getViewers();
    }
    platform.sort(id, ascending);
    vec = platform.testGetStreams();
    old_val = 0;
    for(const auto &ptr : vec){
        if(ptr->getId() < old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getId();
    }
    platform.sort(id, descending);
    vec = platform.testGetStreams();
    old_val = 999999999;
    for(const auto &ptr : vec){
        if(ptr->getId() > old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getId();
    }
    platform.sort(minimum_age, ascending);
    vec = platform.testGetStreams();
    old_val = 0;
    for(const auto &ptr : vec){
        if(ptr->getMinAge() < old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getMinAge();
    }
    platform.sort(minimum_age, descending);
    vec = platform.testGetStreams();
    old_val = 999999999;
    for(const auto &ptr : vec){
        if(ptr->getMinAge() > old_val){
            GTEST_FAIL();
        }
        old_val = ptr->getMinAge();
    }
}

TEST(platform, showStreams){
    Platform platform;
    platform.testMode();
    for(int i = 0; i < 100; ++i){
        platform.startPublicStream("title" + std::to_string(i), "nick" + std::to_string(i), "PT", i);
    }
    platform.startPublicStream("title", "nick", "EN", 95);
    platform.startPublicStream("title", "nick", "EN", 15);
    std::cout << " --- Please verify the following information --- " << std::endl;
    platform.showStreams();
    std::cout << " --- Filter: min_age <= 16 ---" << std::endl;
    platform.showStreams("", 16);
    std::cout << " --- Filter: language = 'EN' ---" << std::endl;
    platform.showStreams("EN");
    std::cout << " --- Filter: language = 'EN' and min_age <= 16 --- " << std::endl;
    platform.showStreams("EN", 20);
}

TEST(platform, archiveTop){
    Platform platform;
    platform.testMode();
    std::vector<std::pair<unsigned int,char>> ids;
    const unsigned int N_STREAMS = 50;
    for(int i = 0; i < N_STREAMS; ++i){
        if(rand() % 3 == 0){
            ids.emplace_back(i,'-');
        }
        platform.startPublicStream("title"+std::to_string(i), "streamer", "PT", 19);
        platform.endStream(i+1);
    }
    std::cout << " --- Verify the following information ---\n";
    std::cout << "Should include following ids:";
    for(auto i : ids){
        std::cout << i.first << ",";
    }
    std::cout << std::endl;
    platform.showStreamHistory(ids);

    std::cout << " --- Verify the following information ---\n";
    platform.topArchivedStreams();
}