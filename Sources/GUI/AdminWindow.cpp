//
// Created by chenhonxinh on 2021/12/15.
//

#include "Header/GUI/AdminWindow.h"

AdminWindow::AdminWindow(Admin* admin): ClientWindow((User*)admin) {


}

void AdminWindow::initDifference() {

    QTreeWidgetItem *pItem5 = new QTreeWidgetItem(QStringList("系统管理"));
    this->addList_and_window(pItem5,new Panel_6);
    iconlist.append("../Resources/left-item/system_unselected.png");
    pItem5->setIcon(0,QIcon(iconlist.value(5)));

    this->setWindowTitle("疫情管理系统-管理端");
    for(int i=0;i<treeWidgets->topLevelItemCount();i++){
        treeWidgets->topLevelItem(i)->setSizeHint(0,QSize(100,105));
    }

}

void AdminWindow::start() {
    ClientWindow::start();
    initDifference();

}




