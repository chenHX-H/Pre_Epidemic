//
// Created by chenhonxinh on 2021/12/7.
//

#include "Header/Role/User.h"
#include "Header/Application.h"
User::User(UserData& data):UserData(data) {
     queryPreEpidemicMsg();
}

QStringList User::getSupply_Information(QString sql) {
    if(sql.compare("all")==0){
        return Application::getDatabase_Connection()->getMaterial(QString("select * from material;"));
    }
    return Application::getDatabase_Connection()->getMaterial(sql);
}

bool User::apply_for_supply(QString name,int much) {
    Application::getDatabase_Connection()
    ->getMaterial(QString("update material set count=count-%1 where name='%2';").arg(much).arg(name));
    return false;
}



bool User::isAdmin1() const {
    return isAdmin;
}

void User::setIsAdmin(bool isAdmin) {
    User::isAdmin = isAdmin;
}

void User::queryPreEpidemicMsg() {
    QString sql="select * from pre_user where id='%1'";
    cout<<"查询语句:"<<sql.arg(this->getId()).toStdString();
    Pre_user *pUser = Application::getDatabase_Connection()->getPreUser(sql.arg(this->getId()));
    this->setPreEpidemicData(pUser);
}

User::~User() {

}

void User::apply_for_dealWith(BackLog backLog) {
    cout<<"预处理:"<<endl;
    cout<<"backLog:"<<endl;
    cout<<"中文";
    QString sql=QString("insert into backlog values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12');")
            .arg(backLog.getId()).arg(backLog.getName()).arg(backLog.getAge()).arg(backLog.isSex())
            .arg(backLog.getIdNumber()).arg(backLog.getOperation()).arg(backLog.getMsg())
            .arg(backLog.getInoculateCount()).arg(backLog.getInoculateTimeLast()).arg(backLog.getInoculateName())
            .arg(backLog.getNadCount()).arg(backLog.getNadLastTime());

//   cout<<"\n"<<"sql语句："<<sql.toStdString();
    Application::getDatabase_Connection()->addBackLogItem(sql);

}

bool User::apply_becomeToDoctor(QString msg,QByteArray data) {
    cout<<"User这边触发"<<endl;
    User *pUser = Application::getCurrentUser();
    if(pUser->isDoctor1()){
        return false;
    }
    Application::getDatabase_Connection()->addApply_UserToDoctor(pUser->getId(),pUser->getNameZh(),msg,data);
    return true;
}

QStringList User::getListWantBeDoctor() {
   return Application::getDatabase_Connection()->getListDoctorApply();
}

QPixmap User::getDoctorMaterialPIC(QString name) {
    const QByteArray &data = Application::getDatabase_Connection()->getUser_to_Doctor_PICTURE(name);
    QPixmap pixmap;
    pixmap.loadFromData(data,"png");
    return pixmap;
}

bool User::dealFinishedDoctorApply(QString name,int flag) {
    Application::getDatabase_Connection()->dealFinishedDoctorApply(name,flag);
    return true;
}


