
#include "Header/Data/Materials.h"

string Materials::getName() const {
    return name;
}

void Materials::setName(const string &name) {
    this->name=name;
}

const string &Materials::getKind() const {
    return kind;
}

void Materials::setKind(const string &kind) {
this->kind=kind;
}

int Materials::getCount() const {
    return count;
}

void Materials::setCount(int count) {
this->count=count;
}

bool Materials::isRegulate() const {
    return is_regulate;
}

void Materials::setIsRegulate(bool isRegulate) {
    this->is_regulate=isRegulate;
}

Materials::Materials( string &name,  string &kind, int count, bool isRegulate) : name(name), kind(kind),
                                                                                           count(count),
                                                                                           is_regulate(isRegulate) {}

Materials::Materials(string name, int count):name(name),count(count) {}
