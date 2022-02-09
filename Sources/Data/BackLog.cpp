//
// Created by chenhonxinh on 2021/12/25.
//

#include "Header/Data/BackLog.h"

const QString &BackLog::getName() const {
    return name;
}

void BackLog::setName(const QString &name) {
    BackLog::name = name;
}

int BackLog::getAge() const {
    return age;
}

void BackLog::setAge(int age) {
    BackLog::age = age;
}

const QString &BackLog::getId() const {
    return id;
}

void BackLog::setId(const QString &id) {
    BackLog::id = id;
}

const QString &BackLog::getOperation() const {
    return operation;
}

void BackLog::setOperation(const QString &operation) {
    BackLog::operation = operation;
}

const QString &BackLog::getMsg() const {
    return msg;
}

void BackLog::setMsg(const QString &msg) {
    BackLog::msg = msg;
}

bool BackLog::isSex() const {
    return sex;
}

void BackLog::setSex(bool sex) {
    BackLog::sex = sex;
}

int BackLog::getInoculateCount() const {
    return inoculateCount;
}

void BackLog::setInoculateCount(int inoculateCount) {
    BackLog::inoculateCount = inoculateCount;
}

int BackLog::getNadCount() const {
    return NADCount;
}

void BackLog::setNadCount(int nadCount) {
    NADCount = nadCount;
}

const QString &BackLog::getInoculateTimeLast() const {
    return InoculateTime_last;
}

void BackLog::setInoculateTimeLast(const QString &inoculateTimeLast) {
    InoculateTime_last = inoculateTimeLast;
}

const QString &BackLog::getInoculateName() const {
    return inoculateName;
}

void BackLog::setInoculateName(const QString &inoculateName) {
    BackLog::inoculateName = inoculateName;
}

const QString &BackLog::getNadLastTime() const {
    return NADLastTime;
}

void BackLog::setNadLastTime(const QString &nadLastTime) {
    NADLastTime = nadLastTime;
}

const QString &BackLog::getIdNumber() const {
    return idNumber;
}

void BackLog::setIdNumber(const QString &idNumber) {
    BackLog::idNumber = idNumber;
}
