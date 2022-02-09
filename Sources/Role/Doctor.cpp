//
// Created by chenhonxinh on 2021/12/9.
//

#include "Header/Role/Doctor.h"
#include "Header/Application.h"
Doctor::Doctor(User* user): User(*user) {
    this->setIsDoctor(true);
}

QStringList Doctor::getALLBackLog() {
    Operate_Database *db = Application::getDatabase_Connection();
    QString sql="select * from backlog;";
    return db->getBackLog(sql);
}

bool Doctor::vaccinate(BackLog backLog) {
    Operate_Database *db = Application::getDatabase_Connection();

    db->deleteBackLogItem(backLog.getIdNumber(),backLog.getOperation());
    db->dealWithEpidemic(QString("update pre_user set inoculateCount=inoculateCount+1 ,inoculateTime_last='%1' where id='%2'").arg(backLog.getInoculateTimeLast()).arg(backLog.getId()));

    return false;
}

bool Doctor::doNAD(BackLog backLog) {
    Operate_Database *db = Application::getDatabase_Connection();

    db->deleteBackLogItem(backLog.getIdNumber(),backLog.getOperation());
    db->dealWithEpidemic(QString("update pre_user set NADCount=NADCount+1 ,NADLastTime='%1' where id='%2'").arg(backLog.getNadLastTime()).arg(backLog.getId()));

    return false;
}
