//
// Created by chenhonxinh on 2021/12/7.
//

#ifndef BIGPROJECT_USER_H
#define BIGPROJECT_USER_H
#include <string>
#include "Header/Data/UserData.h"
#include <QString>
#include "Header/Data/UserData.h"
#include "Header/Data/Materials.h"
#include "Header/Data/BackLog.h"
#include <QPixmap>
using namespace std;
class User: public UserData{

public:
    User(UserData & );
    virtual   ~User();

     bool isAdmin1() const;

    void setIsAdmin(bool isAdmin);

    QStringList getSupply_Information(QString sql="all");
    bool apply_for_supply(QString name,int much);

    void  apply_for_dealWith(BackLog);
    void queryPreEpidemicMsg();

    /**医生权限处理**/
    bool apply_becomeToDoctor(QString,QByteArray);
    QStringList getListWantBeDoctor();
    QPixmap getDoctorMaterialPIC(QString );
    bool dealFinishedDoctorApply(QString ,int flag=0);
private:
    bool isAdmin= false;
};


#endif //BIGPROJECT_USER_H
