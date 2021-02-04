#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fleet.h"
#include <string>

using testing::Eq;

TEST(test_1, a_MakeVehicles) {
    Car a1("Fiat",5,2017,"gas",1200);
    Truck c1("Ford",3,2016,"gas",1400,1000);
    Car a2("Renault",9,2017,"diesel",1300);
    Bicycle b1("XX",4,2018,"ToutTerrain");
    EXPECT_EQ("gas", c1.getFuel());
    EXPECT_EQ("Fiat", a1.getBrand());
    EXPECT_EQ("Ford", c1.getBrand());
}

TEST(test_1, b_MakeFleet){
    Fleet f;
    EXPECT_EQ(0, f.numVehicles());
    EXPECT_EQ(0, f.lowestYear());
    Vehicle *v1 =new Car("Fiat",5,1997,"gasolina",1200);
    Vehicle *v2= new Truck("Ford",3,1999,"gasolina",1400,1000);
    Vehicle *v3=new Car("Renault",9,1997,"gasoleo",1300);
    Vehicle *v4=new Bicycle("XX",4,2002,"TodoTerreno");
    f.addVehicle(v1);
    f.addVehicle(v2);
    f.addVehicle(v3);
    f.addVehicle(v4);
    EXPECT_EQ(4, f.numVehicles());
    EXPECT_EQ(1997, f.lowestYear());
}

TEST(test_1, c_InfoVehicle){
    Car a1("Fiat",5,1997,"gas",1200);
    Truck c1("Ford",3,1999,"gas",1400,1000);
    Bicycle b1("XX",4,2002,"TouTerrain");
    EXPECT_EQ(5, a1.info());
    EXPECT_EQ(6,c1.info());
    EXPECT_EQ(4,b1.info());
}

TEST(test_1, d_InfoFleet){
    Vehicle *v1 =new Car("Fiat",5,2016,"gas",1200);
    Vehicle *v2= new Truck("Ford",3,2017,"gas",1400,1000);
    Vehicle *v3=new Bicycle("XX",4,2018,"ToutTerrain");
    Fleet f;
    f.addVehicle(v1);
    f.addVehicle(v2);
    f.addVehicle(v3);
    EXPECT_TRUE(true);
    cout << "This test never fails! VERIFY information written in monitorr" << endl;
    cout << f;
}

TEST(test_1, e_OperatorLessThan) {
    Car a1("Fiat",3,2017,"gas",1200);
    Truck c1("Ford",5,2017,"gas",1400,1000);
    Bicycle b1("XX",4,2018,"ToutTerrain");
    EXPECT_EQ(true, a1<c1);
    EXPECT_EQ(false,b1<c1);
    EXPECT_EQ(true,a1<b1);
}

TEST(test_1, f_OperatorFunction) {
    Fleet f;
    Vehicle *v1 =new Car("Fiat",5,2016,"gas",1200);
    Vehicle *v2= new Truck("Ford",3,2017,"gas",1400,1000);
    Vehicle *v3=new Car("Renault",9,2016,"diesel",1300);
    Vehicle *v4=new Car("Renault",9,2010,"diesel",1300);
    Vehicle *v5=new Bicycle("XX",4,2018,"ToutTerrain");
    f.addVehicle(v1);
    f.addVehicle(v2);
    f.addVehicle(v3);
    f.addVehicle(v4);
    f.addVehicle(v5);
    EXPECT_EQ(5, f.numVehicles());
    vector<Vehicle*> v;
    v = f(2016);
    EXPECT_EQ(2, v.size());
    v = f(2015);
    EXPECT_EQ(0, v.size());
    v = f(2010);
    EXPECT_EQ(1, v.size());
    EXPECT_EQ("Renault", v[0]->getBrand());
}

TEST(test_1, g_TaxVehicle) {
    Car a1("Fiat",5,1997,"gas",1200);
    Truck c1("Ford",3,1999,"gas",1400,1000);
    Bicycle b1("XX",4,2002,"ToutTerrain");
    EXPECT_NEAR(29.06, a1.calculateTax(),0.001);
    EXPECT_NEAR(45.15,c1.calculateTax(),0.001);
    EXPECT_NEAR(0,b1.calculateTax(),0.001);
}

TEST(test_1, h_TaxFleet) {
    Vehicle *v1 =new Car("Fiat",5,1997,"gas",1200);
    Vehicle *v2= new Truck("Ford",3,1999,"gas",1400,1000);
    Vehicle *v3=new Bicycle("XX",4,2002,"ToutTerrain");
    Fleet f;
    f.addVehicle(v1);
    f.addVehicle(v2);
    f.addVehicle(v3);
    EXPECT_NEAR(74.21, f.totalTax(),0.001);
}

TEST(test_1, i_removeVehicles) {
    Vehicle *v1 =new Car("Fiat",5,2018,"gas",1200);
    Vehicle *v2= new Truck("Ford",3,2015,"gas",1400,1000);
    Vehicle *v3= new Truck("Ford",4,2017,"gas",1400,1000);
    Vehicle *v4= new Truck("Ford",5,2019,"gas",1400,1000);
    Vehicle *v5= new Truck("Ford",3,2018,"gas",1400,1000);
    Vehicle *v6=new Bicycle("XX",4,2020,"ToutTerrain");
    Fleet f;
    f.addVehicle(v1); f.addVehicle(v2);
    f.addVehicle(v3); f.addVehicle(v4);
    f.addVehicle(v5); f.addVehicle(v6);
    EXPECT_EQ(2, f.removeOldVehicles(2017));
    EXPECT_EQ(4,f.getVehicles().size());
    EXPECT_EQ(3, f.removeOldVehicles(2019));
    EXPECT_EQ(1,f.getVehicles().size());
}
