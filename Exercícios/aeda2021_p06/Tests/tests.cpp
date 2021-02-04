#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "stackExt.h"
#include "counter.h"
#include "exceptions.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "performance.h"

using testing::Eq;


TEST(test_1, StackExt_FindMin){
    StackExt<int> s1;
    // Testing empty()
    EXPECT_EQ(true, s1.empty());
    // Testing push() e top()
    s1.push(6);
    s1.push(4);
    s1.push(7);
    s1.push(2);
    s1.push(5);
    EXPECT_EQ(5, s1.top());
    // Testing pop() e top()
    s1.pop();
    s1.pop();
    EXPECT_EQ(7, s1.top());

    // Testing findMin()
    EXPECT_EQ(4, s1.findMin());
    s1.push(3);
    s1.push(2);
    EXPECT_EQ(2, s1.findMin());

    // Now testing findMin() to verify constant time
    // clearing Stack
    s1.pop();
    s1.pop();
    s1.pop();
    s1.pop();
    s1.pop();
    EXPECT_EQ(true, s1.empty());

    // preparing data to test execution test
    int size = 9;
    unsigned int elapsedTime[size];
    int x_el[] = {5000000,6000000,7000000,8000000,9000000,10000000,11000000,12000000,13000000};
    int random_int;
    ticks tstart;
    ticks tend;

    for (int i = 0; i < size; i++) {
        // fill stack with number of elements specified in x_el
        for (int z = 1; z <= x_el[i]; z++) {
            random_int = rand() % 1000 + 1;
            s1.push(random_int);
        }
        // counting time
        tstart = getticks(); // initiate ticks counting
        s1.findMin(); // this is constant
        tend = getticks(); // end ticks counting
        elapsedTime[i] = getElapsed(tend,tstart);
        // clearing stack
        for (int z = 1; z <= x_el[i]; z++) {
            s1.pop();
        }
    }
    // Verify if constant time
    // NOTE: parameter 10 means that values in the range [-10, 10] are considered constant
    EXPECT_EQ(true, isConstant(elapsedTime, size, 10));
}

TEST(test_2, a_ClientConstructor){
    srand(time(NULL));
    Client cl;
    EXPECT_TRUE((cl.getNumGifts()>0 && cl.getNumGifts()<=5));
}

TEST(test_2, b_CounterConstructor){
    srand(time(NULL));
    Counter c;
    EXPECT_EQ(0, c.getNumAttendedClients());
    EXPECT_EQ(2, c.getWrappingTime());
    EXPECT_EQ(0, c.getActualTime());
    EXPECT_TRUE((c.getNextEnter()>0 && c.getNextEnter() <= 20));
    EXPECT_EQ(0, c.getNextLeave());
    EXPECT_THROW(c.getNextClient(), EmptyQueue);
    try {
        c.getNextClient();
    }
    catch (EmptyQueue &e) {
        cout << "Exception caught, empty queue: " << e.getMsg() << endl;
        EXPECT_EQ("Empty Queue", e.getMsg());
    }
}

TEST(test_2, c_EnterCounter){
    Counter c;
    cout << "This test does not fail. Check if the following information appears (x varies between 1 and 5): time = 0\n"
            "new customer arrived with x gifts" << endl;

    c.enter();
    EXPECT_EQ(0, c.getActualTime());
    EXPECT_TRUE((c.getNextClient().getNumGifts()>0 && c.getNextClient().getNumGifts()<=5));
    EXPECT_TRUE((c.getNextEnter()>0 && c.getNextEnter() <= 20));
    EXPECT_TRUE((c.getNextLeave()>=2 && c.getNextLeave() <= 10)); // between [0+1*2, 0+5*2]
}

TEST(test_2, d_LeaveCounter){
    Counter c;
    // Simulates the arrival of clients
    c.enter();
    c.enter();

    // simulates the leaving
    c.leave();

    EXPECT_EQ(0, c.getActualTime());
    EXPECT_TRUE((c.getNextLeave()>=2 && c.getNextLeave() <= 10)); // between [0+1*2, 0+5*2]
    c.leave();
    try {
        c.getNextClient();
    }
    catch (EmptyQueue &e) {
        cout << "Exception caught, empty queue: " << e.getMsg() << endl;
        EXPECT_EQ("Empty Queue", e.getMsg());
    }
}

TEST(test_2, e_NextEvent){
    cout << "This test does not fail. Check the information on the monitor." << endl;
    EXPECT_TRUE(true);
    Counter c;
    c.nextEvent();
    cout << "01: " << "Number of attended clients: " << c.getNumAttendedClients() << " Actual time: " << c.getActualTime() << " Next enter: " << c.getNextEnter() << " Next leave: " << c.getNextLeave() << endl;
    c.nextEvent();
    cout << "02: " << "Number of attended clients: " << c.getNumAttendedClients() << " Actual time: " << c.getActualTime() << " Next enter: " << c.getNextEnter() << " Next leave: " << c.getNextLeave() << endl;
    c.nextEvent();
    cout << "03: " << "Number of attended clients: " << c.getNumAttendedClients() << " Actual time: " << c.getActualTime() << " Next enter: " << c.getNextEnter() << " Next leave: " << c.getNextLeave() << endl;
    c.nextEvent();
    cout << "04: " << "Number of attended clients: " << c.getNumAttendedClients() << " Actual time: " << c.getActualTime() << " Next enter: " << c.getNextEnter() << " Next leave: " << c.getNextLeave() << endl;
}

TEST(test_2, f_Operador){
    cout << "This test does not fail. Check the information on the monitor." << endl;
    EXPECT_TRUE(true);
    Counter c;
    c.nextEvent();
    c.nextEvent();
    c.nextEvent();
    c.nextEvent();
    cout << c << endl;
}