#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>

#include "packagingMachine.h"

using testing::Eq;

TEST(test, a_loadObjects){
    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 11));
    objects.push_back(Object(3, 17)); objects.push_back(Object(4, 3));
    objects.push_back(Object(5, 9)); objects.push_back(Object(6, 4));
    objects.push_back(Object(7, 2)); objects.push_back(Object(8, 12));
    objects.push_back(Object(9, 7)); objects.push_back(Object(10, 1));

    for(unsigned i = 0; i < objects.size(); i++) 
        cout << objects[i] << endl;

    PackagingMachine machine;
    int objsLoaded = machine.loadObjects(objects);
    int objsNotLoaded  = objects.size();
    EXPECT_EQ(7, objsLoaded);
    EXPECT_EQ(3, objsNotLoaded);
    HeapObj objectsH= machine.getObjects();
    bool isEmp = objectsH.empty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false)
        EXPECT_EQ(5,objectsH.top().getID());
}

TEST(test, b_searchBox){
    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 5));
    objects.push_back(Object(3, 8)); objects.push_back(Object(4, 1));
    objects.push_back(Object(5, 4)); objects.push_back(Object(6, 6));
    objects.push_back(Object(7, 1)); objects.push_back(Object(8, 4));

    Box::resetID();

    Box b1(10); //7
    b1.addObject( objects[0] );
    b1.addObject( objects[1] );
    Box b2(10); //8
    b2.addObject( objects[2] );

    PackagingMachine machine;
    machine.addBox( b1 );
    machine.addBox( b2 );

    cout << "Free in Box " << b1.getID() << ": " << b1.getFree() << endl; //3
    cout << "Free in Box " << b2.getID() << ": " << b2.getFree() << endl; //2

    EXPECT_EQ(2, machine.numberOfBoxes()); // 8 7
    HeapBox boxesH= machine.getBoxes();
    bool isEmp = boxesH.empty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false)
        EXPECT_EQ(2,boxesH.top().getFree());

    Box bx = machine.searchBox( objects[3] );
    bx.addObject( objects[3] );
    machine.addBox( bx );
    //cout << "Carga livre em C" << bx.getID() << ": " << bx.getFree() << endl;
    EXPECT_EQ(2, machine.numberOfBoxes()); // 9 7
    boxesH= machine.getBoxes();
    isEmp = boxesH.empty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false)
        EXPECT_EQ(1,boxesH.top().getFree());

    bx = machine.searchBox( objects[4] );
    bx.addObject( objects[4] );
    machine.addBox( bx );
    cout << "Free in Box " << bx.getID() << ": " << bx.getFree() << endl;
    EXPECT_EQ(3, machine.numberOfBoxes()); // 9 7 4
    boxesH= machine.getBoxes();
    isEmp = boxesH.empty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false)
        EXPECT_EQ(1,boxesH.top().getFree());

    bx = machine.searchBox( objects[5] );
    bx.addObject( objects[5] );
    machine.addBox( bx );
    cout << "Free in Box " << bx.getID() << ": " << bx.getFree() << endl;
    EXPECT_EQ(3, machine.numberOfBoxes()); // 10 9 7
    boxesH= machine.getBoxes();
    isEmp = boxesH.empty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false)
        EXPECT_EQ(0,boxesH.top().getFree());

    bx = machine.searchBox( objects[6] );
    bx.addObject( objects[6] );
    machine.addBox( bx );
    cout << "Free in Box " << bx.getID() << ": " << bx.getFree() << endl;
    EXPECT_EQ(3, machine.numberOfBoxes()); // 10 10 7
    boxesH = machine.getBoxes();
    EXPECT_EQ(3,boxesH.size());
    if (boxesH.size()==3) {
        boxesH.pop();
        EXPECT_EQ(0, boxesH.top().getFree());
    }

    bx = machine.searchBox( objects[7] );
    bx.addObject( objects[7] );
    machine.addBox( bx );
    cout << "Free in Box " << bx.getID() << ": " << bx.getFree() << endl;
    EXPECT_EQ(4, machine.numberOfBoxes()); // 10 10 7 6
    boxesH = machine.getBoxes();
    EXPECT_EQ(4,boxesH.size());
    if (boxesH.size()==4) {
        boxesH.pop();
        boxesH.pop();
        EXPECT_EQ(3, boxesH.top().getFree());
    }
}

TEST(test, c_packObjects){
    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 11));
    objects.push_back(Object(3, 17)); objects.push_back(Object(4, 3));
    objects.push_back(Object(5, 9)); objects.push_back(Object(6, 4));
    objects.push_back(Object(7, 2)); objects.push_back(Object(8, 12));
    objects.push_back(Object(9, 7)); objects.push_back(Object(10, 10));
    objects.push_back(Object(11, 10)); objects.push_back(Object(12, 1));

    Box::resetID();
    PackagingMachine machine;

    EXPECT_EQ(9, machine.loadObjects(objects));
    EXPECT_EQ(3, objects.size());
    EXPECT_EQ(5, machine.packObjects());

    HeapBox boxes = machine.getBoxes();
    EXPECT_EQ(5, boxes.size());
    if (boxes.size()==5) {
        EXPECT_EQ(0, boxes.top().getFree());
        boxes.pop();
        EXPECT_EQ(0, boxes.top().getFree());
        boxes.pop();
        EXPECT_EQ(0, boxes.top().getFree());
        boxes.pop();
        EXPECT_EQ(0, boxes.top().getFree());
        boxes.pop();
        EXPECT_EQ(2, boxes.top().getFree());
    }
}

TEST(test, d_ObjectsNotPacked){
    PackagingMachine machine;
    EXPECT_EQ("No objects!\n", machine.printObjectsNotPacked());

    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 12));
    objects.push_back(Object(3, 8)); objects.push_back(Object(4, 1));

    EXPECT_EQ(3, machine.loadObjects(objects));
    string objsNotP = machine.printObjectsNotPacked();
    cout << objsNotP;
    EXPECT_EQ("O3:8\nO1:2\nO4:1\n", machine.printObjectsNotPacked());

    EXPECT_EQ(2, machine.packObjects());
    EXPECT_EQ("No objects!\n", machine.printObjectsNotPacked());
}

TEST(test, e_ConteudoBox){
    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 5));
    Box::resetID();

    Box b1(10);
    EXPECT_EQ("Box 1 empty!\n", b1.printContent());

    b1.addObject( objects[0] );
    b1.addObject( objects[1] );

    EXPECT_EQ("Box 1 [ O2:5 O1:2 ]", b1.printContent());
}

TEST(test, f_BoxMoreObjects){
    vector<Object> objects;
    objects.push_back(Object(1, 2)); objects.push_back(Object(2, 11));
    objects.push_back(Object(3, 17)); objects.push_back(Object(4, 3));
    objects.push_back(Object(5, 9)); objects.push_back(Object(6, 4));
    objects.push_back(Object(7, 2)); objects.push_back(Object(8, 12));
    objects.push_back(Object(9, 7)); objects.push_back(Object(10, 10));
    objects.push_back(Object(11, 10)); objects.push_back(Object(12, 1));

    Box bx;
    Box::resetID();
    PackagingMachine machine;

    EXPECT_THROW(machine.boxWithMoreObjects(), PackagingMachine::MachineWithoutBoxes);
    try {
        bx = machine.boxWithMoreObjects();
    }
    catch(PackagingMachine::MachineWithoutBoxes &msc) {
        cout << "This test never fails! Verify information written in monitor" << endl;
        EXPECT_TRUE(true);

    }

    EXPECT_EQ(9, machine.loadObjects(objects));
    EXPECT_EQ(3, objects.size());
    EXPECT_EQ(5, machine.packObjects());

    bx = machine.boxWithMoreObjects();
    EXPECT_EQ(5, bx.getID());
    EXPECT_EQ("Box 5 [ O1:2 O7:2 O6:4 ]", bx.printContent());
}

