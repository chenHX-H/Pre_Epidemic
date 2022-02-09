//
// Created by chenhonxinh on 2021/12/7.
//

#ifndef BIGPROJECT_ADMIN_H
#define BIGPROJECT_ADMIN_H
#include "Header/Role/Doctor.h"
#include <QStringList>
class Admin: public Doctor{
public:
    Admin(User*);
    bool addUser();
    bool ratify();//批准用户注册,针对医护人员
    bool deleteUser();
    bool setLimitedSupply();    //设置物资上限
    bool stopSupply(); //停止补给
    bool announce(QStringList);
    bool addMaterial(Materials);  //添加物资
    bool addNewMaterial(Materials);

};


#endif //BIGPROJECT_ADMIN_H
