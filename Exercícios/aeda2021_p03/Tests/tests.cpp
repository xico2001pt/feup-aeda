#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "graph.h"

using testing::Eq;

TEST(test, a_Constructor){
    Graph<string,int> g;
    EXPECT_EQ(0, g.numNodes());
    EXPECT_EQ(0, g.numEdges());
}

TEST(test, b_AddNode){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    EXPECT_EQ(3, f.numNodes());

    EXPECT_THROW(f.addNode("B"), NodeAlreadyExists<string>);
    try {
        f.addNode("B");
    }
    catch (NodeAlreadyExists<string> &e) {
        ostringstream ostr;
        ostr << e;
        string str = "Node already exists: B";
        EXPECT_EQ(str, ostr.str());
    }
    f.addNode("D");
    f.addNode("E");
    EXPECT_EQ(5, f.numNodes());
}

TEST(test, c_InserirAresta){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    f.addNode("D");
    f.addNode("E");
    f.addEdge("A", "B", 5);
    f.addEdge("A", "C", 8);
    f.addEdge("B", "D", 9);
    f.addEdge("C", "D", 3);
    f.addEdge("C", "E", 4);
    f.addEdge("D", "E", 2);
    f.addEdge("D", "B", 11);
    EXPECT_EQ(7, f.numEdges());
    EXPECT_THROW(f.addEdge("D", "B", 12), EdgeAlreadyExists<string>);
    try {
        f.addEdge("D", "B", 12);
    }
    catch (EdgeAlreadyExists<string> &e) {
        ostringstream ostr;
        ostr << e;
        string str = "Edge already exists: D , B";
        EXPECT_EQ(str, ostr.str());
    }

    EXPECT_THROW(f.addEdge("F", "B", 11), NodeDoesNotExist<string>);
    try {
        f.addEdge("F", "B", 11);
    }
    catch (NodeDoesNotExist<string> &e) {
        ostringstream ostr1;
        ostr1 << e;
        string str1 = "Node does not exist: F";
        EXPECT_EQ(str1, ostr1.str());
    }

    EXPECT_EQ(7, f.numEdges());
}

TEST(test, d_ValorAresta){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    f.addNode("D");
    f.addNode("E");
    f.addEdge("A", "B", 5);
    f.addEdge("A", "C", 8);
    f.addEdge("B", "D", 9);
    f.addEdge("C", "D", 3);
    f.addEdge("C", "E", 4);
    f.addEdge("D", "E", 2);
    f.addEdge("D", "B", 11);
    f.edgeValue("A", "B") = 15;
    EXPECT_EQ(15, f.edgeValue("A", "B"));
    EXPECT_THROW(f.edgeValue("A", "A"), EdgeDoesNotExist<string>);
    try {
        f.edgeValue("A", "A");
    }
    catch (EdgeDoesNotExist<string> &e) {
        ostringstream ostr;
        ostr << e;
        string str = "Edge does not exist: A , A";
        EXPECT_EQ(str, ostr.str());
    }

    EXPECT_THROW(f.edgeValue("F", "B"), NodeDoesNotExist<string>);
    try {
        f.edgeValue("F", "B");
    }
    catch (NodeDoesNotExist<string> &e) {
        ostringstream ostr1;
        ostr1 << e;
        string str1 = "Node does not exist: F";
        EXPECT_EQ(str1, ostr1.str());
    }
}

TEST(test, e_EliminarAresta){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    f.addNode("D");
    f.addNode("E");
    f.addEdge("A", "B", 5);
    f.addEdge("A", "C", 8);
    f.addEdge("B", "D", 9);
    f.addEdge("C", "D", 3);
    f.addEdge("C", "E", 4);
    f.addEdge("D", "E", 2);
    f.addEdge("D", "B", 11);
    EXPECT_EQ(7, f.numEdges());
    f.removeEdge("D", "E");
    EXPECT_EQ(6, f.numEdges());
    EXPECT_THROW(f.removeEdge("D", "A"), EdgeDoesNotExist<string>);
    try {
        f.removeEdge("A", "A");
    }
    catch (EdgeDoesNotExist<string> &e) {
        ostringstream ostr;
        ostr << e;
        string str = "Edge does not exist: A , A";
        EXPECT_EQ(str, ostr.str());
    }

    EXPECT_THROW(f.removeEdge("F", "B"), NodeDoesNotExist<string>);
    try {
        f.removeEdge("F", "B");
    }
    catch (NodeDoesNotExist<string> &e) {
        //cout << "Apanhou excecao " << e << endl;
        ostringstream ostr1;
        ostr1 << e;
        string str1 = "Node does not exist: F";
        EXPECT_EQ(str1, ostr1.str());
    }

    EXPECT_EQ(6, f.numEdges());
}

TEST(test, f_ImprimirGraph){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    f.addNode("D");
    f.addNode("E");
    f.addEdge("A", "B", 5);
    f.addEdge("A", "C", 8);
    f.addEdge("B", "D", 9);
    f.addEdge("C", "D", 3);
    f.addEdge("C", "E", 4);
    f.addEdge("D", "E", 2);
    f.addEdge("D", "B", 11);
    EXPECT_EQ(7, f.numEdges());
    ostringstream ostr;
    f.print(ostr);
    string str = "( A [B 5] [C 8] ) ( B [D 9] ) ( C [D 3] [E 4] ) ( D [E 2] [B 11] ) ( E ) ";
    cout << str.c_str()<<endl;
    EXPECT_EQ(str, ostr.str());
}


TEST(test, g_OperadorSaida){
    Graph<string,int> f;
    f.addNode("A");
    f.addNode("B");
    f.addNode("C");
    f.addNode("D");
    f.addNode("E");
    f.addEdge("A", "B", 5);
    f.addEdge("A", "C", 8);
    f.addEdge("B", "D", 9);
    f.addEdge("C", "D", 3);
    f.addEdge("C", "E", 4);
    f.addEdge("D", "E", 2);
    f.addEdge("D", "B", 11);
    EXPECT_EQ(7, f.numEdges());
    ostringstream ostr;
    ostr << f;
    string str = "( A [B 5] [C 8] ) ( B [D 9] ) ( C [D 3] [E 4] ) ( D [E 2] [B 11] ) ( E ) ";
    EXPECT_EQ(str, ostr.str());
}
