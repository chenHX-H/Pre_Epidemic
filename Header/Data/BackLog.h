//
// Created by chenhonxinh on 2021/12/25.
//

#ifndef PRE_EPIDEMIC_BACKLOG_H
#define PRE_EPIDEMIC_BACKLOG_H
#include "QString"
class BackLog {
private:
    QString name;
    int age;
    QString id;
    QString operation;
    QString msg;
    bool sex= false;
    QString idNumber;
public:
    const QString &getIdNumber() const;

    void setIdNumber(const QString &idNumber);

private:

    int inoculateCount=-1;
    int NADCount=-1;
    QString InoculateTime_last;
    QString inoculateName;
    QString NADLastTime;
public:
    int getInoculateCount() const;

    void setInoculateCount(int inoculateCount);

    int getNadCount() const;

    void setNadCount(int nadCount);

    const QString &getInoculateTimeLast() const;

    void setInoculateTimeLast(const QString &inoculateTimeLast);

    const QString &getInoculateName() const;

    void setInoculateName(const QString &inoculateName);

    const QString &getNadLastTime() const;

    void setNadLastTime(const QString &nadLastTime);

public:
    bool isSex() const;

    void setSex(bool sex);

public:
    const QString &getName() const;

    void setName(const QString &name);

    int getAge() const;

    void setAge(int age);

    const QString &getId() const;

    void setId(const QString &id);

    const QString &getOperation() const;

    void setOperation(const QString &operation);

    const QString &getMsg() const;

    void setMsg(const QString &msg);

};


#endif //PRE_EPIDEMIC_BACKLOG_H
