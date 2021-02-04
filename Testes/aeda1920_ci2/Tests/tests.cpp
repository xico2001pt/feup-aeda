#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "Box.h"
#include "WideFlatBox.h"
#include "ThinTallBox.h"
#include "Warehouse.h"

using testing::Eq;
using namespace std;


// void WideFlatBox::remove(Object object)
TEST(test_1, test_a){
	srand(1);
	Box* b1 = new WideFlatBox(10);
	Object o1("qwe",4);
	Object o2("asd",3);
	Object o3("zxc",5);
	b1->insert(o1);
	b1->insert(o2);
	EXPECT_THROW(b1->remove(o3), InaccessibleObjectException);
	try {
		b1->remove(o3);
	} catch(InaccessibleObjectException &o) {
		EXPECT_EQ(o.getObject(), o3);
	}
	EXPECT_EQ(7, b1->getContentSize());

	b1->remove(o1);
	EXPECT_EQ(3, b1->getContentSize());
	EXPECT_EQ(b1->empty(),false);
	if (!b1->empty())
  	    EXPECT_EQ(b1->next(), o2);
}


// void ThinTallBox::insert(Object object)
TEST(test_2, test_b){
    Box* b1 = new ThinTallBox(10);
    Object o1("qwe",4);
    Object o2("asd",3);
    Object o3("zxc",5);

    b1->insert(o1);
    EXPECT_EQ(4, b1->getContentSize());
    EXPECT_EQ(b1->empty(),false);
    if (!b1->empty())
        EXPECT_EQ(b1->next(), o1);

    b1->insert(o2);
    EXPECT_EQ(7, b1->getContentSize());
    EXPECT_EQ(b1->empty(),false);
    if (!b1->empty())
        EXPECT_EQ(b1->next(), o2);

    EXPECT_THROW(b1->insert(o3), ObjectDoesNotFitException);
    EXPECT_EQ(7, b1->getContentSize());
}


// Object Box::removeNext()
TEST(test_3, test_c){
	stack<Object> objects;
	Object o1("qwe",4);
	Object o2("asd",3);
	objects.push(o1);
	objects.push(o2);
	Box* b1 = new ThinTallBox(10, objects, 7);

    EXPECT_EQ(b1->removeNext(), o2);
    EXPECT_EQ(b1->removeNext(), o1);
	EXPECT_THROW(b1->removeNext(), InaccessibleObjectException);
}


// void ThinTallBox::sortObjects()
TEST(test_4, test_d){
	stack<Object> objects;
	Object o1("qwe",4);
	Object o2("asd",5);
	Object o3("zxc",2);
	Object o4("rty",6);
	Object o5("fgh",3);
	objects.push(o1);
	objects.push(o2);
	objects.push(o3);
	objects.push(o4);
	objects.push(o5);
	ThinTallBox* b1 = new ThinTallBox(20, objects, 20);
	b1->sortObjects();
	stack<Object> objsSort= b1->getObjects();
	EXPECT_EQ(objsSort.size(),5);
	EXPECT_EQ(objsSort.top(),o3); objsSort.pop();
    EXPECT_EQ(objsSort.top(), o5); objsSort.pop();
	EXPECT_EQ(objsSort.top(), o1); objsSort.pop();
	EXPECT_EQ(objsSort.top(), o2); objsSort.pop();
	EXPECT_EQ(objsSort.top(), o4);
}


TEST(test_5, test_e) {
    Warehouse *w1 = new Warehouse();
    vector<Object> objv;
    Object o1("qwe", 4);
    Object o2("asd", 5);
    Object o3("zxc", 2);
    Object o4("rty", 6);
    Object o5("fgh", 3);
    Object o6("obj6", 1);
    objv.push_back(o1);
    objv.push_back(o2);
    objv.push_back(o3);
    objv.push_back(o4);
    objv.push_back(o5);
    objv.push_back(o6);
    unsigned num = w1->InsertObjectsInQueue(objv);

    EXPECT_EQ(num, 6);
    queue<Object> q1 = w1->getObjects();
    if (!q1.empty()) {
        EXPECT_EQ(q1.front(), o4);
        q1.pop();
    }
    if (!q1.empty()) {
        EXPECT_EQ(q1.front(), o2);
        q1.pop();
    }
    if (!q1.empty()) {
        EXPECT_EQ(q1.front(), o1);
        q1.pop();
    }
    if (!q1.empty()) {
        EXPECT_EQ(q1.front(), o5);
        q1.pop();
    }
    if (!q1.empty()) {
        EXPECT_EQ(q1.front(), o3);
        q1.pop();
    }
    if (!q1.empty())
        EXPECT_EQ(q1.front(), o6);
}


TEST(test_6, test_f) {
    Warehouse *w1= new Warehouse();
    Object o1("qwe",7);
    Object o2("asd",5);
    Object o3("zxc",4);
    Object o4("rty",8);
    Object o5("fgh",6);
    Object o6("obj6",3);
    w1->addObject(o1);
    w1->addObject(o2);
    w1->addObject(o3);
    w1->addObject(o4);
    w1->addObject(o5);
    w1->addObject(o6);

    Object ot1 = w1->RemoveObjectQueue(2);
    EXPECT_EQ(ot1.getName(), "dummy");
    queue<Object> q = w1->getObjects();
    EXPECT_EQ(q.size(),6);
    EXPECT_EQ(q.front(),o1); q.pop();
    EXPECT_EQ(q.front(),o2); q.pop();
    EXPECT_EQ(q.front(),o3);

    Object ot2 = w1->RemoveObjectQueue(4);
    EXPECT_EQ(ot2.getName(), "zxc");
    q = w1->getObjects();
    EXPECT_EQ(q.size(),5);
    EXPECT_EQ(q.front(),o1); q.pop();
    EXPECT_EQ(q.front(),o2); q.pop();
    EXPECT_EQ(q.front(),o4);

    Object ot3  = w1->RemoveObjectQueue(4);
    EXPECT_EQ(ot3.getName(), "obj6");
    q = w1->getObjects();
    EXPECT_EQ(q.size(),4);
    EXPECT_EQ(q.front(),o1); q.pop();
    EXPECT_EQ(q.front(),o2); q.pop();
    EXPECT_EQ(q.front(),o4); q.pop();
    EXPECT_EQ(q.front(),o5);
}


TEST(test_7, test_g) {
    Warehouse *w1 = new Warehouse();
    Object o1("o1", 4);
    Object o2("o2", 3);
    Object o3("o3", 5);
    Object o4("o4", 6);
    stack<Object> st1;
    st1.push(o1); st1.push(o2);
    ThinTallBox b1(10, st1, 7);
    stack<Object> st2;
    st2.push(o3); st2.push(o4);
    ThinTallBox b2(20, st2, 11);
    stack<Object> st3;
    st3.push(o1); st3.push(o3); st3.push(o4);
    ThinTallBox b3(20, st3, 15);

    vector<ThinTallBox> v;
    v.push_back(b1);
    EXPECT_EQ(w1->addPackOfBoxes(v),1);
    v.clear();
    v.push_back(b2); v.push_back(b3);
    EXPECT_EQ(w1->addPackOfBoxes(v),3);
}


TEST(test_8, test_h) {
    Warehouse *w1 = new Warehouse();
    Object o1("o1", 4);
    Object o2("o2", 3);
    Object o3("o3", 5);
    Object o4("o4", 6);
    stack<Object> st1;
    st1.push(o2);
    st1.push(o1);
    ThinTallBox b1(10, st1, 7);
    b1.setDaysToSend(2);
    stack<Object> st2;
    st2.push(o3);
    st2.push(o4);
    ThinTallBox b2(20, st2, 11);
    b2.setDaysToSend(0);
    stack<Object> st3;
    st3.push(o1);
    st3.push(o3);
    st3.push(o4);
    ThinTallBox b3(18, st3, 15);
    b3.setDaysToSend(2);
    stack<Object> st4;
    st4.push(o1);
    st4.push(o2);
    st4.push(o3);
    st4.push(o4);
    ThinTallBox b4(18, st4, 18);
    b4.setDaysToSend(2);
    queue<ThinTallBox> q;
    q.push(b1);
    q.push(b2);
    q.push(b3);
    q.push(b4);
    w1->setBoxes(q);

    Object ox("ox", 4);
    Object oy("oy", 5);
    Object oz("oz", 3);
    Object ow("ow", 6);
    Object ok("ok", 8);
    w1->addObject(ox);
    w1->addObject(oy);
    w1->addObject(oz);
    w1->addObject(ow);
    w1->addObject(ok);

    vector<ThinTallBox> v = w1->DailyProcessBoxes();
    EXPECT_EQ(v.size(), 2);
    if (v.size() == 2) {
        EXPECT_EQ(v[0].getObjects().size(), 3);
        EXPECT_EQ(v[0].getObjects().top().getName(), "ox");
        EXPECT_EQ(v[1].getObjects().size(), 4);
        EXPECT_EQ(v[1].getObjects().top().getName(), "o4");
    }

    queue<Object> qobjs = w1->getObjects();
    EXPECT_EQ(qobjs.size(),3);
    if (!qobjs.empty()) {
        EXPECT_EQ(qobjs.front().getName(), "oy");
        qobjs.pop();
    }
    if (!qobjs.empty()) {
        EXPECT_EQ(qobjs.front().getName(), "ow");
        qobjs.pop();
    }
    if (!qobjs.empty())
        EXPECT_EQ(qobjs.front().getName(),"ok");
}
