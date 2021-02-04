#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()) {
        if (it.retrieve().getAuthor() == a)
            tmp.push_back(it.retrieve().getPaint());
        it.advance();
    }
    return tmp;
}

vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()) {
        PaintCatalogItem aux = it.retrieve();
        if (aux.getYear() >= y1 && aux.getYear() <= y2)
            tmp.push_back(aux.getPaint());
        it.advance();
    }
    return tmp;
}

bool Gallery::updateTitle(Paint* p, string tnew) {
    PaintCatalogItem pci(p);
    if (!catalog.remove(p)) return false;
    *p = Paint(p->getAuthor(),tnew,p->getYear(),p->getPrice());
    catalog.insert(PaintCatalogItem(p));
    return true;
}

int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for (const Paint *p : collection) {
        AuthorRecord aux(p->getAuthor());
        if(!authorRecords.insert(aux).second) { // if exists
            auto a = authorRecords.find(aux);
            AuthorRecord b(a->getAuthor(), a->getAvailablePaints() + 1, a->getTotalSells() + p->getPrice());
            authorRecords.erase(a);
            authorRecords.insert(b);
        }
    }
    return authorRecords.size();
}

double Gallery::totalSells() const {
    double result = 0;
    for (const AuthorRecord &a : authorRecords) {
        result += a.getTotalSells();
    }
    return result;
}

double Gallery::sellPaint(string a, string t) {
    vector<Paint*>::iterator it = collection.begin();
    while (it != collection.end()) {
        if ((*it)->getAuthor() == a && (*it)->getTitle() == t) {
            double val = (*it)->getPrice();
            AuthorRecord au(a, 1, val);
            auto c = authorRecords.find(au);
            au = AuthorRecord(a, c->getAvailablePaints() - 1, c->getTotalSells() + val);
            authorRecords.erase(c);
            authorRecords.insert(au);
            collection.erase(it);
            return val;
        }
        ++it;
    }
}

vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    priority_queue<ExhibitionItem> copy = paintsToShow;
    int counter = 0, last_year = copy.top().getYear();
    while (!copy.empty() && tmp.size() < n) {
        ExhibitionItem i = copy.top();
        copy.pop();
        if (last_year == i.getYear()) {
            if (counter < maxPerYear) {
                tmp.push_back(i.getPaint());
            }
            ++counter;
        }
        else {
            counter = 0;
            last_year = i.getYear();
            if (counter < maxPerYear) {
                tmp.push_back(i.getPaint());
            }
            ++counter;
        }
    }
    priority_queue<ExhibitionItem> copy2;
    bool found;
    while (!paintsToShow.empty()) {
        found = false;
        ExhibitionItem i = paintsToShow.top();
        paintsToShow.pop();
        for (const Paint* p : tmp) {
            if (p->getAuthor() == i.getAuthor() && p->getTitle() == i.getTitle()) {
                found = true;
                break;
            }
        }
        if (!found) {
            copy2.push(i);
        }
    }
    paintsToShow = copy2;
    return tmp;
}

int Gallery::itemExibitionOrder(string a, string t) {
    priority_queue<ExhibitionItem> copy = paintsToShow;
    int counter = 0;
    while (!copy.empty()) {
        ++counter;
        ExhibitionItem i = copy.top();
        copy.pop();
        if (i.getAuthor() == a && i.getTitle() == t) {
            return counter;
        }
    }
    return 0;
}

