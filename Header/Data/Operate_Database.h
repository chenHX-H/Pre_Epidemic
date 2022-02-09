//
// Created by chenhonxinh on 2021/12/17.
//

#ifndef PRE_EPIDEMIC_OPERATE_DATABASE_H
#define PRE_EPIDEMIC_OPERATE_DATABASE_H

#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Header/Data/Materials.h"
#include "Header/Data/UserData.h"
#include <QVariant>
#include "Header/Data/BackLog.h"
using namespace std;
class Operate_Database {

public:
     Operate_Database();
/****数据库连接记得释放 2021年12月17日 01:06:10****/
     ~Operate_Database();
     QSqlQuery* getSqlQuery();
     void ReConnect();
     /***公告查询****/
     QStringList getAnnouncement();
     bool insertNotice(QString title,QString content,QString time);
    /***对用户表的操作**/
     void addNewUser(UserData);
     Pre_user* getPreUser(QString sql);
     bool check_user_isExist(const char*);
     UserData * loginQuery(const char*,const char*);
     void showAllUser();

   /**对物资表的操作**/
    QStringList getMaterial(QString sql);
    bool addNewMaterials(const Materials &);
    bool addMaterials(QString sql);
    /******待处理列表*******/
    QStringList getBackLog(QString sql);
    bool addBackLogItem(QString sql);
    bool deleteBackLogItem(QString id,QString operation);
    void dealWithEpidemic(QString sql);

    /***医生权限申请***/
    void addApply_UserToDoctor(QString ,QString name,QString,QByteArray);
    QByteArray getUser_to_Doctor_PICTURE(QString);
    QStringList getListDoctorApply();
    bool dealFinishedDoctorApply(QString,int);
private:
     QSqlDatabase db;
     QSqlQuery* sqlQuery;
};





#endif //PRE_EPIDEMIC_OPERATE_DATABASE_H
