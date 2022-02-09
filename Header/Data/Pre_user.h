//
// Created by chenhonxinh on 2021/12/26.
//

#ifndef PRE_EPIDEMIC_PRE_USER_H
#define PRE_EPIDEMIC_PRE_USER_H
#include <QString>

class Pre_user {
private:
    int inoculateCount=-1;
    int NADCount=-1;
    QString InoculateTime_last;
    QString inoculateName;
    QString NADLastTime;
public:
    int getInoculateCount() const {
        return inoculateCount;
    }

    void setInoculateCount(int inoculateCount) {
        Pre_user::inoculateCount = inoculateCount;
    }

    int getNadCount() const {
        return NADCount;
    }

    void setNadCount(int nadCount) {
        NADCount = nadCount;
    }

    const QString &getInoculateTimeLast() const {
        return InoculateTime_last;
    }

    void setInoculateTimeLast(const QString &inoculateTimeLast) {
        InoculateTime_last = inoculateTimeLast;
    }

    const QString &getInoculateName() const {
        return inoculateName;
    }

    void setInoculateName(const QString &inoculateName) {
        Pre_user::inoculateName = inoculateName;
    }

    const QString &getNadLastTime() const {
        return NADLastTime;
    }

    void setNadLastTime(const QString &nadLastTime) {
        NADLastTime = nadLastTime;
    }

};


#endif //PRE_EPIDEMIC_PRE_USER_H
