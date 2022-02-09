//
// Created by chenhonxinh on 2021/12/9.
//

#ifndef PRE_EPIDEMIC_DOCTOR_H
#define PRE_EPIDEMIC_DOCTOR_H


#include "User.h"

class Doctor: public User{
public:
    Doctor(User* user);
    QStringList getALLBackLog();
    bool vaccinate(BackLog backLog);
    bool doNAD(BackLog backLog);

};


#endif //PRE_EPIDEMIC_DOCTOR_H
