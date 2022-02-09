//
// Created by chenhonxinh on 2021/12/10.
//

#ifndef PRE_EPIDEMIC_USERDATA_H
#define PRE_EPIDEMIC_USERDATA_H
#include <string>
#include "Header/Data/Pre_user.h"
using namespace std;
class UserData{
private:
    QString id;
    QString username;
    QString password;
    QString job;
    bool isDoctor= false;

    QString name_ZH;
    bool sex= false;
    int age;
    QString idNumber;
    Pre_user* preEpidemicData= nullptr;
public:
    UserData(const QString &id, const QString &username);

    UserData();


public:
    Pre_user *getPreEpidemicData() const;

    void setPreEpidemicData(Pre_user *preEpidemicData);
    /**coutMsg**/
    void countUserMSg();

public:
    const QString &getId() const;

    void setId(const QString &id);

    const QString &getUsername() const;

    void setUsername(const QString &username);

    const QString &getPassword() const;

    void setPassword(const QString &password);

    const QString &getJob() const;

    void setJob(const QString &job);

    bool isDoctor1() const;

    void setIsDoctor(bool isDoctor);

    const QString &getNameZh() const;

    void setNameZh(const QString &nameZh);

    bool isSex() const;

    void setSex(bool sex);

    int getAge() const;

    void setAge(int age);

    const QString &getIdNumber() const;

    void setIdNumber(const QString &idNumber);

};

#endif //PRE_EPIDEMIC_USERDATA_H
