#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(), obj.end(), sortFunc);
    for (Object &ob : obj) {
        objects.push(ob);
    }
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(double maxSize){
    Object res;
    queue<Object> aux;
    bool found = false;
    while (!objects.empty()) {
        if (objects.front().getSize() <= maxSize) {
            found = true;
            res = objects.front();
            objects.pop();
            break;
        }
        else {
            aux.push(objects.front());
            objects.pop();
        }
    }
    if (found) {
        while (!objects.empty()) {
            aux.push(objects.front());
            objects.pop();
        }
    }
    else {
        res = Object("dummy", maxSize);
    }
    objects = aux;
    return res;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for (const ThinTallBox &thinTallBox : boV) {
        boxes.push(thinTallBox);
    }
    return boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    unsigned int counter = boxes.size();
    while (counter > 0) {
        ThinTallBox aux = boxes.front();
        if (aux.getContentSize() == aux.getCapacity()) { // Caixa está cheia
            res.push_back(aux);
        }
        else if (aux.getDays() == 0) { // Caixa expirou
            Object ob = RemoveObjectQueue(aux.getCapacity() - aux.getContentSize());
            if (ob.getName() == "dummy") ob = Object("dummy", 0); // trocar tamanho para 0
            boxes.front().insert(ob);
            res.push_back(boxes.front());
        }
        else {
            Object ob = RemoveObjectQueue(aux.getCapacity() - aux.getContentSize());
            if (ob.getName() == "dummy") ob = Object("dummy", 0); // trocar tamanho para 0
            boxes.front().insert(ob);
            boxes.front().setDaysToSend(aux.getDays() - 1);
            boxes.push(boxes.front());
        }
        boxes.pop();
        counter--;
    }
    return res;
}

