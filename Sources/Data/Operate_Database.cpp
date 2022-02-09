//
// Created by chenhonxinh on 2021/12/17.
//

#include "Header/Data/Operate_Database.h"
#include <QFile>
#include <QSqlError>
Operate_Database::Operate_Database() {
    cout<<"数据库连接bb";
    db =  QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("数据库所在主机ip地址");
    db.setPort(3306);
    db.setDatabaseName("pre_epidemic"); /* 数据库名 */
    db.setUserName("数据库用户名");
    db.setPassword("数据库用户名密码");
    bool ok = db.open();
    if (ok){
        cout<<" connect database Successful"<<endl;
        sqlQuery=new QSqlQuery(db);
    }
    else {
        sqlQuery= nullptr;
        cout<<"connect database failed"<<endl;
    }
}

bool Operate_Database::addBackLogItem(QString sql) {
    cout<<"\n"<<"正在执行addBackLogItem——当前sql语句:"<<sql.toStdString();
    sqlQuery->exec(sql);
}

Pre_user *Operate_Database::getPreUser(QString sql) {
    sqlQuery->exec(sql);
    Pre_user* preUser=new Pre_user;
    if(sqlQuery->size()==0){

    }else{
        sqlQuery->next();
        preUser->setNadLastTime(sqlQuery->value("NADLastTime").toString());
        preUser->setNadCount(sqlQuery->value("NADCount").toInt());
        preUser->setInoculateName(sqlQuery->value("inoculateName").toString());
        preUser->setInoculateTimeLast(sqlQuery->value("inoculateTime_last").toString());
        preUser->setInoculateCount(sqlQuery->value("inoculateCount").toInt());
    }
    return preUser;
}

QSqlQuery* Operate_Database::getSqlQuery() {
    return sqlQuery;
}



bool Operate_Database::check_user_isExist(const char * username) {
    sqlQuery->exec(QString("select * from user where name='%1'").arg(username));
    if(sqlQuery->size()==0)
        return false;
    else
        return true;
}

UserData *Operate_Database::loginQuery(const char * id, const char * pwd) {
    sqlQuery->exec(QString("select * from user where username='%1' and password='%2'").arg(id).arg(pwd));
    if(sqlQuery->size()!=0){
        cout<<"成功得到";
        sqlQuery->next();
        QString id=sqlQuery->value("id").toString();
        QString name=sqlQuery->value("username").toString();
        QString job=sqlQuery->value("job").toString();
        bool isDoctor=sqlQuery->value("isDoctor").toBool();
        const QString &name_ZH = sqlQuery->value("name_ZH").toString();
        bool sex = sqlQuery->value("sex").toBool();
        int age = sqlQuery->value("age").toInt();
        const QString &isNumber = sqlQuery->value("idNumber").toString();

        UserData *currentUser=new UserData();
        currentUser->setId(id);
        currentUser->setUsername(name);
        currentUser->setJob(job);
        currentUser->setIsDoctor(isDoctor);
        currentUser->setNameZh(name_ZH);
        currentUser->setSex(sex);
        currentUser->setAge(age);
        currentUser->setIdNumber(isNumber);
        return currentUser;
    }
    return nullptr;
}

void Operate_Database::showAllUser() {
    sqlQuery->exec("select * from user");
    while(sqlQuery->next()){
        string username= sqlQuery->value("name").toString().toStdString();
        string password=sqlQuery->value("password").toString().toStdString();
        cout<<"用户名:"<<username<<"       "<<"密码:"<<password<<endl;
    }
}




bool Operate_Database::addNewMaterials(const Materials & materials) {
    sqlQuery->exec(QString("insert into material values('%1',%2,'%3',%4)")
                          .arg(materials.getName().c_str()).arg(materials.getCount()).arg(materials.getKind().c_str()).arg(materials.isRegulate())
    );
    if(sqlQuery->size()==0){
        return false;
    }
    return true;
}

QStringList Operate_Database::getMaterial(QString sql) {
    QStringList list;
    sqlQuery->exec(sql);

    while(sqlQuery->next()){

        QString name = sqlQuery->value("name").toString();
         int count=sqlQuery->value("count").toInt();
         QString kind=sqlQuery->value("kind").toString();
         bool is_regulate=sqlQuery->value("is_regulate").toBool();
         list.append(QString("%1=%2=%3=%4").arg(name).arg(count).arg(kind).arg(is_regulate));
    }

    return list;
}

bool Operate_Database::addMaterials(QString sql) {
    sqlQuery->exec( sql);
    if(sqlQuery->size()==0){
        return false;
    }
    return true;
}

void Operate_Database::ReConnect() {
    bool ok = db.open();
    if (ok){
        cout<<" connect database Successful"<<endl;
        sqlQuery=new QSqlQuery(db);
    }
    else {
        sqlQuery= nullptr;
        cout<<"connect database failed"<<endl;
    }
}

QStringList Operate_Database::getAnnouncement() {
    sqlQuery->exec(QString("select * from announcement"));
    QStringList list;
    QString order;
    QString sketch;
    QString content;
    QString time;
    while (sqlQuery->next()){
        order=sqlQuery->value("order").toString();
        sketch = sqlQuery->value("sketch").toString();
        content= sqlQuery->value("content").toString();
        time=sqlQuery->value("time").toString();
        list.append(QString("%1=%2=%3=%4").arg(order).arg(sketch).arg(content).arg(time));
    }
    return list;
}

bool Operate_Database::insertNotice(QString title,QString content,QString sendTime) {
     QString  sql = QString("insert into announcement (sketch,content,time) values('%1','%2','%3')")
             .arg(title).arg(content).arg(sendTime);
    bool isSucceed=sqlQuery->exec(sql);
    cout<<"执行:"<<isSucceed;
    return true;
}
/******backlog*******/
QStringList Operate_Database::getBackLog(QString sql) {
    sqlQuery->exec(sql);
    QStringList list;
    while (sqlQuery->next()){
        const QString &id = sqlQuery->value("id").toString();
        const QString &name = sqlQuery->value("name").toString();
        bool sex = sqlQuery->value("sex").toBool();
        int age = sqlQuery->value("age").toInt();
        const QString &idNumber = sqlQuery->value("idNumber").toString();
        const QString &operation = sqlQuery->value("operation").toString();
        const QString &msg = sqlQuery->value("msg").toString();
        const int inoculateCount = sqlQuery->value("inoculateCount").toInt();
        const QString &InoculateTime_last = sqlQuery->value("InoculateTime_last").toString();
        const QString &inoculateName = sqlQuery->value("inoculateName").toString();
        const QString &NADCount = sqlQuery->value("NADCount").toString();
        const QString &NADLastTime = sqlQuery->value("NADLastTime").toString();

        list.append(QString("%1=%2=%3=%4=%5=%6=%7=%8=%9=%10=%11=%12")
        .arg(id).arg(name).arg(sex).arg(age).arg(idNumber).arg(operation)
        .arg(msg).arg(inoculateCount).arg(InoculateTime_last).arg(inoculateName)
        .arg(NADCount).arg(NADLastTime));
    }
    return list;
}

//bool Operate_Database::vccinate(QString sql) {
//    sqlQuery->exec("delete * from backlog where  ")
//}

bool Operate_Database::deleteBackLogItem(QString id,QString operation) {
    sqlQuery->exec(QString("delete from backlog where idNumber='%1' and operation='%2';").arg(id).arg(operation));
    return true;
}

void Operate_Database::dealWithEpidemic(QString( sql)) {
    sqlQuery->exec(sql);
}




Operate_Database::~Operate_Database() {
    delete sqlQuery;
}

void Operate_Database::addNewUser(UserData data) {
    sqlQuery->exec("select MAX(id) from user");
    sqlQuery->next();
    int  cid=sqlQuery->value(0).toInt()+1;
    QString sql=QString("insert into user (id,username,password,isDoctor,name_ZH,sex,age,idNumber,job)"
                        "values('%0','%1','%2',0,'%3',%4,%5,'%6','%7')")
                                .arg(cid)
                                .arg(data.getUsername(),data.getPassword(),data.getNameZh()).arg(data.isSex())
                                .arg(data.getAge()).arg(data.getIdNumber(),data.getJob());
    QString sql2=QString("insert into pre_user values('%1',0,'2021/12/29','科兴',0,'2021/12/29')").arg(cid);
    sqlQuery->exec(sql);
    sqlQuery->exec(sql2);
}

/***医生权限申请***/
void Operate_Database::addApply_UserToDoctor(QString id,QString name,QString msg,QByteArray data) {
    cout<<"最里面来了";
    QString sql=QString("insert into applyFor(id,name,msg,img) values(:id,:name,:msg,:data);");
    sqlQuery->prepare(sql);
    sqlQuery->bindValue(":id",id);
    sqlQuery->bindValue(":name",name);
    sqlQuery->bindValue(":msg",msg);
    sqlQuery->bindValue(":data",data);
    sqlQuery->exec();
    cout<<"name;"<<name.toStdString();

}



QStringList Operate_Database::getListDoctorApply() {
    QStringList list;
    sqlQuery->exec("select name,msg from applyFor;");
    while (  sqlQuery->next()){
        const QString &name = sqlQuery->value("name").toString();
        const QString &msg = sqlQuery->value("msg").toString();
        list.append(QString("%1=%2").arg(name).arg(msg));

    }
    return list;
    
}

QByteArray Operate_Database::getUser_to_Doctor_PICTURE(QString name) {
    bool b = sqlQuery->exec(QString("select img from applyFor where name='%1'").arg(name));
    if(b){
     sqlQuery->next();
        const QByteArray &array = sqlQuery->value("img").toByteArray();
        return array;
    }
}

bool Operate_Database::dealFinishedDoctorApply(QString name,int flag) {
    bool b = sqlQuery->exec(QString("select id from applyFor where name='%1'").arg(name));
    if(b){
        cout<<"这里已经执行1"<<endl;
        sqlQuery->next();
        const QString &id= sqlQuery->value("id").toString();
        cout<<"得到的id"<<id.toStdString();
        bool b2 = sqlQuery->exec(QString("delete from applyFor where name='%1'").arg(name));
        if(b2){
            cout<<"这里已经执行2"<<endl;
            sqlQuery->exec(QString("update user set isDoctor='%1' where id='%2'").arg(flag).arg(id));
            cout<<"这里已经执行3"<<endl;

        }
    }
}

