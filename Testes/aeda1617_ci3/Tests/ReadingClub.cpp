/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    BookCatalogItem itemNotFound("", "", 0);
    for (Book * b : books) {
        BookCatalogItem aux(b->getTitle(), b->getAuthor(), b->getYear());
        BookCatalogItem book = catalogItems.find(aux);
        if (book == itemNotFound) {
            aux.addItems(b);
            catalogItems.insert(aux);
        }
        else {
            book.addItems(b);
            catalogItems.remove(book);
            catalogItems.insert(book);
        }
    }
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
    BookCatalogItem itemNotFound("", "", 0);
    BookCatalogItem aux(book->getTitle(), book->getAuthor(), book->getYear());
    BookCatalogItem b = catalogItems.find(aux);
    if (!(b == itemNotFound)) {
        for (Book *bo : b.getItems()) {
            if (bo->getReader() == NULL) {
                temp.push_back(bo);
            }
        }
    }
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
    BookCatalogItem itemNotFound("", "", 0);
    BookCatalogItem aux(book->getTitle(), book->getAuthor(), book->getYear());
    BookCatalogItem b = catalogItems.find(aux);
    if (!(b == itemNotFound)) {
        for (Book *bo : b.getItems()) {
            if (bo->getReader() == NULL) {
                bo->setReader(reader);
                reader->addReading(book->getTitle(), book->getAuthor());
                catalogItems.remove(b);
                catalogItems.insert(b);
                return true;
            }
        }
    }
    return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
    HashTabUserRecord::iterator it = userRecords.find(UserRecord(user));
    UserRecord aux = *it;
    aux.setEMail(newEMail);
    userRecords.erase(it);
    userRecords.insert(aux);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for (User u : candidates) {
	    if (u.numReadings() >= min)
	        readerCandidates.push(u);
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
    if (readerCandidates.empty()) return 0;
    if (readerCandidates.size() == 1) {
        champion = readerCandidates.top();
        return 1;
    }
    priority_queue<User> copy(readerCandidates);
    copy.pop();
    User aux = copy.top();
    if (readerCandidates.top().numReadings() == aux.numReadings()) return 0;
    champion = readerCandidates.top();
	return readerCandidates.size();
}
























