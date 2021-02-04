#ifndef AEDA1920_CP03_SOL_GALLERY_H
#define AEDA1920_CP03_SOL_GALLERY_H

#include "bst.h"
#include <vector>
#include <unordered_set>
#include <queue>
#include "Paint.h"

// ----------------------------------------------------------

struct AuthorRecordHash {
    int operator()(const AuthorRecord& ar) const {
        int v = 0;
        for (const char &c : ar.getAuthor()) {
            v = 37 * v + c;
        }
        return v;
    }

    bool operator()(const AuthorRecord& ar1, const AuthorRecord& ar2) const {
        return ar1.getAuthor() == ar2.getAuthor();
    }
};


typedef unordered_set<AuthorRecord, AuthorRecordHash, AuthorRecordHash> HashTableAuthorRecord;

class Gallery {
    vector<Paint*> collection;
    BST<PaintCatalogItem> catalog;
    HashTableAuthorRecord authorRecords;
    priority_queue<ExhibitionItem> paintsToShow;
public:
    Gallery(vector<Paint*> c);
    vector<Paint*> getCollection() const;
    void setCollection(vector<Paint*> c);
    priority_queue<ExhibitionItem> getPaintsToShow() const;
    HashTableAuthorRecord getAuthorRecords () const;
    void addAuthorRecord(AuthorRecord ar);

    //Part I - BST
    void generateCatalog();
    BST<PaintCatalogItem> getCatalog() const;
    vector<Paint*> getPaintsBy(string autor) const; //getPaintsBy -- o vetor deve estar ordenado, pelo criterio do <
    vector<Paint*> getPaintsBetween(int y1, int y2) const; //inclusive
    bool updateTitle(Paint* p, string tnew);

    //Part II - Hash - borrowedPaints
    int recordAvailablePainters(); //carrega a tabela de dispersao com AuthorRecords; retorna o numero de autores
    double totalSells() const;
    double sellPaint(string a, string t); //realiza uma veda do quadro do autor a, com título t, se existir na colecao retorna; retorna o total vendido para o autor; e atualiza hash

    //Part III - Priority Queue
    void prepareExhibition();
    vector<Paint*> nBestExibition(int n, int maxPerYear); //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposicao (maximo de NPerYear pinturas de um mesmo ano)
    int itemExibitionOrder(string a, string t); // verifica qual a ordem de exibicao de uma pintura, mantentdo a ordem origial dos elementos; retorna 0, se nao estiver na fila
};


#endif //AEDA1920_CP03_SOL_GALLERY_H
