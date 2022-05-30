/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x=0, int y=0);
    string toString() const;
    int distanceTo(const Point & otherPoint) const;
};

Point::Point(int x, int y): x(x), y(y) {
    // do nothing
}
string Point::toString() const {
    string s = "<Point[";
    s.append(to_string(x));
    s.append(",");
    s.append(to_string(y));
    s.append("]>");
    return s;
}
int Point::distanceTo(const Point & otherPoint) const {
    double dis = sqrt((double)(pow(x - otherPoint.x, 2) + pow(y - otherPoint.y, 2)));
    return (int)std::ceil(dis);
}

class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point & point=Point(), Node * next=NULL);
    string toString() const;
};

Node::Node(const Point & point, Node * next): point(point), next(next) {
    // Do nothing
}

string Node::toString() const {
    string s = "<Node[";
    s.append(point.toString());
    s.append("]>");
    return s;
}

class Path {
private:
    Node * head;
    Node * tail;
    int count;
    int length;

public:
    Path();
    ~Path();

    void addPoint(int x, int y);
    string toString() const;
    Point getLastPoint() const;

    int gLength() {
        return length;
    }
};

Path::Path() {
    head = tail = NULL;
    length = -1;
    count = 0;
}

Path::~Path() {
    Node *tmp;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

void Path::addPoint(int x, int y) {
    count++;
    Point p(x, y);
    Node *n = new Node(p);
    if(tail == NULL) {
        tail = head = n;
        length = 0;
    }
    else {
        tail->next = n;
        length += p.distanceTo(tail->point);
        tail = n;
    }
}

Point Path::getLastPoint() const {
    return tail->point;
}

string Path::toString() const {
    string s = "<Path[count:";
    s.append(to_string(count));
    s.append(",length:");
    s.append(to_string(length));
    s.append(",[");
    Node *i = head;
    for(; i != tail; i = i->next) {
        s.append(i->toString());
        s.append(",");
    }
    if(tail != NULL) {
        s.append(tail->toString());
    }
    s.append("]]>");
    return s;
}

class Character {
private:
    string name;
    Path * path;

public:
    Character(const string & name="");
    ~Character();

    string getName() const;
    void setName(const string & name);

    void moveToPoint(int x, int y);
    string toString() const;

    int gPLength() const {
        int l = path->gLength();
        return l;
    }

    int distanceTo(Character c) const {
        Point otherPos = c.path->getLastPoint();
        Point myPos = path->getLastPoint();
        return myPos.distanceTo(otherPos);
    }
};

Character::Character(const string & name): name(name){
    path = new Path();
}

Character::~Character() {
    delete path;
}

string Character::getName() const {
    return name;
}
void Character::setName(const string & name) {
    this->name = name;
}
void Character::moveToPoint(int x, int y) {
    path->addPoint(x, y);
}
string Character::toString() const {
    string s = "<Character[name:";
    s.append(name);
    s.append(",path:");
    s.append(path->toString());
    s.append("]>");
    return s;
}

bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {

    if(chWatson.gPLength() - chMurderer.gPLength() > maxLength){
        outDistance = -1;
        return false;
    } else {
        outDistance = chWatson.distanceTo(chMurderer);
        if(outDistance > maxDistance)
            return false;
        else
            return true;
    }
    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */