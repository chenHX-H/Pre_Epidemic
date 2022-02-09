//
// Created by chenhonxinh on 2021/12/7.
//

#include "Header/Role/Admin.h"
#include "Header/Application.h"
Admin::Admin(User* user): Doctor(user) {
    setIsDoctor(true);
    setIsAdmin(true);

}

bool Admin::addUser() {
    return false;
}

bool Admin::ratify() {
    return false;
}

bool Admin::deleteUser() {
    return false;
}

bool Admin::setLimitedSupply() {
    return false;
}

bool Admin::stopSupply() {
    return false;
}

bool Admin::addMaterial(Materials material) {
    QString sql=QString("update material set count=count+%1 where name='%2';")
            .arg(material.getCount()).arg(material.getName().c_str());
    bool b = Application::getDatabase_Connection()->addMaterials(sql);
    if(b){
        return true;
    }
    return false;
}

bool Admin::announce(QStringList data) {
    for (const auto &item : data){
        cout<<item.toStdString();
    }
    Application::getDatabase_Connection()->insertNotice(data.value(0),data.value(1),data.value(2));
    return false;
}

bool Admin::addNewMaterial(Materials materials) {
    bool b = Application::getDatabase_Connection()->addNewMaterials(materials);
    if(!b){
        return false;
    }
    return true;
}
