#ifndef AEDA1920_CP03_SOL_PAINT_H
#define AEDA1920_CP03_SOL_PAINT_H

#include <string>
#include <ostream>

using namespace std;

class Paint {
    string author;
    string title;
    int year;
    double price;
public:
    Paint(string a, string t, int y, double p);
    string getAuthor() const;
    string getTitle() const;
    int getYear() const;
    double getPrice() const;

    friend ostream& operator<<(ostream& os, const Paint& p);
    friend class PaintCatalogItem;
};

class PaintCatalogItem {
    Paint* paintItem;
public:
    PaintCatalogItem(Paint* paintItem);
    PaintCatalogItem(string a, string t, int y, double p);
    Paint* getPaint() const;
    string getAuthor() const;
    string getTitle() const;
    int getYear() const;
    double getPrice() const;

    bool operator<(const PaintCatalogItem& pci) const;
    bool operator==(const PaintCatalogItem& pci) const;
    friend ostream& operator<<(ostream& os, const PaintCatalogItem& p);
};

class AuthorRecord {
    string author;
    int availablePaints;
    double totalSells;
public:
    AuthorRecord(string a); //cria um novo authorRecord
    AuthorRecord(string a, int ap, double ts);
    string getAuthor() const;
    int getAvailablePaints() const;
    double getTotalSells() const;
    int addAvaliablePaint(); //adiciona um, a availablePaints do autor; retorna o total availablePaints
    int subAvailablePaint(); //subtrai um, a availablePaints
    void setTotalSells(double s);

    int recordAvailablePainters(); //conta availablePaints da collection; adiciona mais um
    double recordSell(double p); //a cada nova venda, deduz availablePaints e totaliza totalSells
};

class ExhibitionItem {
    Paint* toShow;
public:
    ExhibitionItem(Paint* paint);
    ExhibitionItem(string a, string t, int y, double p);
    Paint* getPaint() const;
    string getAuthor() const;
    string getTitle() const;
    int getYear() const;
    double getPrice() const;

    bool operator<(const ExhibitionItem& pci) const;
    bool operator==(const ExhibitionItem& pci) const;
    friend ostream& operator<<(ostream& os, const ExhibitionItem& p);
};
#endif //AEDA1920_CP03_SOL_PAINT_H
