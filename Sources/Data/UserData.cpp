//
// Created by chenhonxinh on 2021/12/14.
//
#include "Header/Data/UserData.h"
#include <iostream>

using namespace std;

UserData::UserData(const QString &id, const QString &username) {
    this->id=id;
    this->username=username;
}

UserData::UserData() {

}

Pre_user *UserData::getPreEpidemicData() const {
    return preEpidemicData;
}

void UserData::setPreEpidemicData(Pre_user *preEpidemicData) {
    this->preEpidemicData=preEpidemicData;
}

void UserData::countUserMSg() {

}

const QString &UserData::getId() const {
    return id;
}

void UserData::setId(const QString &id) {
    this->id=id;
}

const QString &UserData::getUsername() const {
    return username;
}

void UserData::setUsername(const QString &username) {
    this->username=username;
}



const QString &UserData::getJob() const {
    return job;
}

void UserData::setJob(const QString &job) {
    this->job=job;
}

bool UserData::isDoctor1() const {
    return isDoctor;
}

void UserData::setIsDoctor(bool isDoctor) {
    this->isDoctor=isDoctor;
}

const QString &UserData::getNameZh() const {
    return name_ZH;
}

void UserData::setNameZh(const QString &nameZh) {
    this->name_ZH=nameZh;
}

bool UserData::isSex() const {
    return sex;
}

void UserData::setSex(bool sex) {
    this->sex=sex;
}

int UserData::getAge() const {
    return this->age;
}

void UserData::setAge(int age) {
    this->age=age;
}

const QString &UserData::getIdNumber() const {
    return idNumber;
}

void UserData::setIdNumber(const QString &idNumber) {
    this->idNumber=idNumber;
}

const QString &UserData::getPassword() const {
    return password;
}

void UserData::setPassword(const QString &password) {
    this->password=password;
}
