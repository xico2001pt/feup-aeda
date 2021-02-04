#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gallery.h"
#include <vector>

using namespace std;
using testing::Eq;


TEST(test, test_getPaintsBy) {
    vector<Paint*> paints;
    paints.push_back(new Paint("a1", "t11", 1888, 10.00));
    paints.push_back(new Paint("a1", "t12", 2010, 10.00));
    paints.push_back(new Paint("a1", "t13", 1888, 10.00));
    paints.push_back(new Paint("a2", "t21", 1885, 90.00));
    paints.push_back(new Paint("a2", "t22", 1937, 90.00));
    paints.push_back(new Paint("a3", "t31", 1903, 90.00));
    paints.push_back(new Paint("a3", "t32", 1905, 90.00));
    paints.push_back(new Paint("a4", "t41", 1903, 90.00));

    Gallery gal= Gallery(paints);
    gal.generateCatalog();

    BST<PaintCatalogItem> paintsBST = gal.getCatalog();
    PaintCatalogItem paintI = paintsBST.findMin();
    EXPECT_EQ(paintI.getAuthor(), "a1");
    EXPECT_EQ(paintI.getTitle(), "t12");
    EXPECT_EQ(paintI.getYear(), 2010);

    vector<Paint*> pa = gal.getPaintsBy("a4");
    EXPECT_EQ(pa.size(),1);
    if (pa.size() ==1 ) {
        EXPECT_EQ(pa.at(0)->getTitle(),"t41");
    }

    pa.clear();
    pa = gal.getPaintsBy("a1");
    EXPECT_EQ(pa.size(),3);
    if (pa.size() ==3 ) {
        EXPECT_EQ(pa.at(0)->getTitle(),"t12");
        EXPECT_EQ(pa.at(1)->getTitle(),"t11");
        EXPECT_EQ(pa.at(2)->getTitle(),"t13");
    }

    pa.clear();
    pa = gal.getPaintsBy("ax");
    EXPECT_EQ(pa.size(),0);
}

TEST(test, test_getPaintsBetween) {
    vector<Paint*> paints;
    paints.push_back(new Paint("a1", "t11", 1888, 10.00));
    paints.push_back(new Paint("a1", "t12", 2010, 10.00));
    paints.push_back(new Paint("a1", "t13", 1888, 10.00));
    paints.push_back(new Paint("a2", "t21", 1885, 90.00));
    paints.push_back(new Paint("a2", "t22", 1937, 90.00));
    paints.push_back(new Paint("a3", "t31", 1903, 90.00));
    paints.push_back(new Paint("a3", "t32", 1905, 90.00));
    paints.push_back(new Paint("a4", "t41", 1903, 90.00));

    Gallery gal= Gallery(paints);
    gal.generateCatalog();

    vector<Paint*> py = gal.getPaintsBetween(1904,2018);
    EXPECT_EQ(py.size(),3);
    if (py.size() ==3 ) {
        EXPECT_EQ(py.at(0)->getTitle(),"t12");
        EXPECT_EQ(py.at(1)->getTitle(),"t22");
        EXPECT_EQ(py.at(2)->getTitle(),"t32");
    }

    py.clear();
    py = gal.getPaintsBetween(1800,1904);
    EXPECT_EQ(py.size(),5);
    if (py.size() ==5 ) {
        EXPECT_EQ(py.at(0)->getTitle(),"t31");
        EXPECT_EQ(py.at(2)->getTitle(),"t11");
        EXPECT_EQ(py.at(4)->getTitle(),"t21");
    }

    py.clear();
    py = gal.getPaintsBetween(2011,2018);
    EXPECT_EQ(py.size(),0);
}

TEST(test, test_updateTitle) {
    vector<Paint*> paints;
    paints.push_back(new Paint("a1", "t11", 1888, 10.00));
    paints.push_back(new Paint("a1", "t12", 2010, 10.00));
    paints.push_back(new Paint("a1", "t13", 1888, 10.00));
    paints.push_back(new Paint("a2", "t21", 1885, 90.00));
    paints.push_back(new Paint("a2", "t22", 1937, 90.00));
    paints.push_back(new Paint("a3", "t31", 1903, 90.00));
    paints.push_back(new Paint("a3", "t32", 1905, 90.00));
    paints.push_back(new Paint("a4", "t41", 1903, 90.00));

    Gallery gal= Gallery(paints);
    gal.generateCatalog();
    Paint *p = new Paint("a2","t22",1937,90);

    bool upd = gal.updateTitle(p, "t2x");
    EXPECT_EQ(upd,true);
    BST<PaintCatalogItem> catalog = gal.getCatalog();
    PaintCatalogItem pi("a2","t2x",1937,90);
    PaintCatalogItem pf = catalog.find(pi);
    EXPECT_EQ(pf.getTitle(),"t2x");
    PaintCatalogItem piant("a2","t22",1937,90);
    pf = catalog.find(piant);
    EXPECT_EQ(pf.getTitle(),"");

    gal.generateCatalog();
    p = new Paint("a1","t13",1888,10);
    upd = gal.updateTitle(p, "t1y");
    EXPECT_EQ(upd,true);
    catalog = gal.getCatalog();
    PaintCatalogItem pi2ant("a1","t13",1888,10);
    pf = catalog.find(pi2ant);
    EXPECT_EQ(pf.getTitle(),"");
    PaintCatalogItem pi2("a1","t1y",1888,10);
    pf = catalog.find(pi2);
    EXPECT_EQ(pf.getTitle(),"t1y");
    pf = catalog.findMax();
    EXPECT_EQ(pf.getTitle(), "t21");
    catalog.remove(pf);
    pf = catalog.findMax();
    EXPECT_EQ(pf.getTitle(), "t1y");

    gal.generateCatalog();
    p = new Paint("a5","t13",1888,10);
    upd = gal.updateTitle(p, "tyy");
    EXPECT_EQ(upd,false);
}

TEST(test, test_recordAvailablePaiters) {
    vector<Paint*> p1;
    p1.push_back(new Paint("a1", "t11", 1937, 200.00));
    p1.push_back(new Paint("a2", "t21", 1937, 90.00));
    p1.push_back(new Paint("a2", "t22", 1937, 90.00));
    p1.push_back(new Paint("a3", "t31", 1903, 50.00));
    p1.push_back(new Paint("a3", "t32", 1905, 50.00));

    Gallery g(p1);
    EXPECT_EQ(g.getCollection().size(),5);
    EXPECT_EQ(g.recordAvailablePainters(),3);

    HashTableAuthorRecord htar = g.getAuthorRecords();
    AuthorRecord ar("a1");
    HashTableAuthorRecord::iterator it = htar.find(ar);
    EXPECT_NE(it,htar.end());
    if(it != htar.end())
        EXPECT_EQ(it->getAvailablePaints(), 1);

    vector<Paint*> p2;
    p2.push_back(new Paint("a3", "t31", 1937, 200.00));
    p2.push_back(new Paint("a3", "t32", 1937, 90.00));
    p2.push_back(new Paint("a3", "t33", 1937, 90.00));
    p2.push_back(new Paint("a3", "t34", 1903, 50.00));
    p2.push_back(new Paint("a3", "t35", 1905, 50.00));

    Gallery gg(p2);
    EXPECT_EQ(gg.getCollection().size(),5);
    EXPECT_EQ(gg.recordAvailablePainters(),1);
    htar = gg.getAuthorRecords();
    AuthorRecord arx("a3");
    it = htar.find(arx);
    EXPECT_NE(it,htar.end());
    if(it != htar.end())
        EXPECT_EQ(it->getAvailablePaints(), 5);
}

TEST(test, test_sellPaint) {
    vector<Paint*> p1;
    p1.push_back(new Paint("a1", "t11", 1937, 200.00));
    p1.push_back(new Paint("a2", "t21", 1937, 90.00));
    p1.push_back(new Paint("a2", "t22", 1937, 90.00));
    p1.push_back(new Paint("a3", "t31", 1903, 50.00));
    p1.push_back(new Paint("a3", "t32", 1905, 50.00));

    Gallery g(p1);

    AuthorRecord ar1("a1", 1, 0);
    g.addAuthorRecord(ar1);
    AuthorRecord ar2("a2", 2, 0);
    g.addAuthorRecord(ar2);
    AuthorRecord ar3("a3", 2, 0);
    g.addAuthorRecord(ar3);

    EXPECT_EQ(g.getCollection().size(),5);

    EXPECT_NEAR(g.sellPaint("a3", "t31"), 50.00, 0.001);
    EXPECT_EQ(g.getCollection().size(),4);

    HashTableAuthorRecord htar = g.getAuthorRecords();
    AuthorRecord ar("a3");
    HashTableAuthorRecord::iterator it = htar.find(ar);
    EXPECT_NE(it,htar.end());
    if(it != htar.end())
        EXPECT_NEAR(it->getTotalSells(), 50.00, 0.001);

    EXPECT_EQ(g.sellPaint("a3", "t31"), 0.00);
    EXPECT_EQ(g.getCollection().size(),4);

    EXPECT_EQ(g.sellPaint("a1", "t11"), 200.00);
    EXPECT_EQ(g.getCollection().size(),3);

    htar = g.getAuthorRecords();
    AuthorRecord arF("a1");
    it = htar.find(arF);
    EXPECT_NE(it,htar.end());
    if(it != htar.end())
        EXPECT_NEAR(it->getTotalSells(), 200.00, 0.001);


    EXPECT_EQ(g.sellPaint("aaaaa", "tttt"), 0.00);
    EXPECT_EQ(g.getCollection().size(),3);
}

TEST(test, test_totalSells) {
    vector<Paint*> p1;
    p1.push_back(new Paint("a1", "t11", 1937, 200.00));
    p1.push_back(new Paint("a2", "t21", 1937, 90.00));
    p1.push_back(new Paint("a2", "t22", 1937, 90.00));
    p1.push_back(new Paint("a3", "t31", 1903, 50.00));
    p1.push_back(new Paint("a3", "t32", 1905, 50.00));

    Gallery g(p1);

    AuthorRecord a1("a1", 4, 200.0);
    AuthorRecord a2("a2", 4, 180.0);
    g.addAuthorRecord(a1);
    g.addAuthorRecord(a2);

    HashTableAuthorRecord htar = g.getAuthorRecords();
    EXPECT_NEAR(g.totalSells(), 380.00, 0.001);

    AuthorRecord a3("a3", 4, 100.0);
    g.addAuthorRecord(a3);

    htar = g.getAuthorRecords();
    EXPECT_NEAR(g.totalSells(), 480.00, 0.001);
}

TEST(test, test_itemExibitionOrder) {
    vector<Paint*> vp;
    vp.push_back(new Paint("a2", "t21", 1937, 90.00));
    vp.push_back(new Paint("a2", "t22", 1937, 80.00));
    vp.push_back(new Paint("a1", "t11", 1937, 200.00));
    vp.push_back(new Paint("a3", "t31", 1903, 50.00));
    vp.push_back(new Paint("a3", "t32", 1905, 50.00));
    vp.push_back(new Paint("a4", "t42", 1903, 20.00));
    vp.push_back(new Paint("a4", "t43", 1903, 10.00));
    vp.push_back(new Paint("a5", "t53", 1903, 10.00));
    vp.push_back(new Paint("a6", "t63", 1903, 10.00));
    vp.push_back(new Paint("a4", "t41", 1903, 30.00));

    Gallery gal(vp);
    gal.prepareExhibition();
    priority_queue<ExhibitionItem> paintsTS = gal.getPaintsToShow();
    EXPECT_EQ(paintsTS.size(),10);
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),50.00,0.01);
    }

    int p = gal.itemExibitionOrder("a4","t41");
    EXPECT_EQ(p,2);
    paintsTS = gal.getPaintsToShow();
    EXPECT_EQ(paintsTS.size(),10);
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),50.00,0.01);
    }

    p = gal.itemExibitionOrder("a2","t22");
    EXPECT_EQ(p,10);
    paintsTS = gal.getPaintsToShow();
    EXPECT_EQ(paintsTS.size(),10);
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),50.00,0.01);
    }

    p = gal.itemExibitionOrder("a2","t11");
    EXPECT_EQ(p,0);
    paintsTS = gal.getPaintsToShow();
    EXPECT_EQ(paintsTS.size(),10);
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),50.00,0.01);
    }

}

TEST(test, test_nBestExibition) {
    vector<Paint*> vp;
    vp.push_back(new Paint("a1", "t11", 1937, 200.00));
    vp.push_back(new Paint("a2", "t21", 1937, 90.00));
    vp.push_back(new Paint("a2", "t22", 1937, 90.00));
    vp.push_back(new Paint("a3", "t31", 1903, 50.00));
    vp.push_back(new Paint("a3", "t32", 1905, 50.00));
    vp.push_back(new Paint("a4", "t41", 1903, 30.00));
    vp.push_back(new Paint("a4", "t42", 1903, 20.00));
    vp.push_back(new Paint("a4", "t43", 1903, 10.00));
    vp.push_back(new Paint("a5", "t53", 1903, 10.00));
    vp.push_back(new Paint("a6", "t63", 1903, 10.00));

    Gallery gal(vp);
    gal.prepareExhibition();
    priority_queue<ExhibitionItem> paintsTS = gal.getPaintsToShow();
    EXPECT_EQ(paintsTS.size(),10);
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),50.00,0.01);
    }

    vector<Paint *> exib = gal.nBestExibition(7,4);
    EXPECT_EQ(exib.size(),7);
    EXPECT_EQ(gal.getPaintsToShow().size(),3);
    paintsTS = gal.getPaintsToShow();
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),10.00,0.01);
    }

    gal.prepareExhibition();
    exib = gal.nBestExibition(7,2);
    EXPECT_EQ(exib.size(),5);
    EXPECT_EQ(gal.getPaintsToShow().size(),5);
    paintsTS = gal.getPaintsToShow();
    if (!paintsTS.empty()) {
        EXPECT_EQ(paintsTS.top().getYear(),1903);
        EXPECT_NEAR(paintsTS.top().getPrice(),20.00,0.01);
    }
}
