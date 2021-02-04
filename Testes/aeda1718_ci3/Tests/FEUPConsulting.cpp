/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    Expertize exp(expertizeAvailable, cost);
    BSTItrIn<Expertize> it(expertizes);
    while (!it.isAtEnd()) {
        Expertize aux = it.retrieve();
        if (aux == exp) {
            aux.addConsultant(student);
            expertizes.remove(aux);
            expertizes.insert(aux);
            return;
        }
        it.advance();
    }
    exp.addConsultant(student);
    expertizes.insert(exp);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
    Expertize itemNotFound("", 0);
	vector<Student*> temp;
	Expertize exp(project->getExpertize(), project->getCost());
	Expertize aux = expertizes.find(exp);
	if (!(aux == itemNotFound)) {
        for (Student *st : aux.getConsultants()) {
            if (st->getCurrentProject() == "") {
                temp.push_back(st);
            }
        }
	}
	return temp;
}

bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    if (project->getConsultant() != NULL || student->getCurrentProject() != "") return false;

    Expertize itemNotFound("", 0);
    Expertize aux = expertizes.find(Expertize(project->getExpertize(), project->getCost()));
    if (aux == itemNotFound) return false;
    for (Student *st : aux.getConsultants()) {
        if (st->getName() == student->getName() && st->getEMail() == student->getEMail()) {
            project->setConsultant(student);
            st->addProject(project->getTitle());
            expertizes.remove(aux);
            expertizes.insert(aux);
            return true;
        }
    }
    return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	StudentPtr aux(student);
	students.insert(aux);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	auto it = students.find(StudentPtr(student));
	StudentPtr aux = *it;
	aux.setEMail(newEMail);
	students.erase(it);
	students.insert(aux);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
    for (Student st : candidates) {
        if (st.getPastProjects().size() >= min) {
            activeStudents.push(st);
        }
    }
}

int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    if (activeStudents.empty()) return 0;
    priority_queue<Student> copy = activeStudents;
    Student aux1 = copy.top();
    copy.pop();
    if (!copy.empty() && copy.top().getPastProjects().size() == aux1.getPastProjects().size()) {
        return 0;
    }
    studentMaximus = activeStudents.top();
    return activeStudents.size();
}





















