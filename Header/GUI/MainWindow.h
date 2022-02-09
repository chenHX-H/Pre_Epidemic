//
// Created by chenhonxinh on 2021/12/15.
//

#ifndef PRE_EPIDEMIC_MAINWINDOW_H
#define PRE_EPIDEMIC_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QMap>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTime>
#include "Header/Role/User.h"
#include "Header/GUI/Panel/Panel_6.h"

class MainWindow : public QMainWindow {
public:
    virtual void start();
    MainWindow();
    ~MainWindow();
    void showTipsWord(QString tip,int duration=3000);
    void onTreeItemClicked();
    QStackedLayout* getWindowsLayout();
    QTreeWidget* getTreeWidget();
protected:
    MySwitch_Icon* lb_refresh;
    User* currentUser;
    QList<QTreeWidgetItem *> itemList;
    QList<QWidget *> widgetList;
    QList<QString> iconlist;


    QWidget *centerQWidget; //中心控件，QMainWindow
    QHBoxLayout *hbox_outest;
    QVBoxLayout *vbox_fiexd;
    QTreeWidget *treeWidgets;
    QStackedLayout *windows_layout;
    QLabel* lb_tip;

    void addList_and_window(QTreeWidgetItem *, QWidget *);
    //该虚函数由子类实现，本类中为空
    virtual void onNotEnabledItemClicked();

    void closeEvent(QCloseEvent *event) override;
    void endUI();

private:
    void initUI();

    void initLayout();

    void initStyle();

    void initBindingEvent();

    void refreshBtn();
    void refreshBtn_off();
    void refreshUIData();


};


#endif //PRE_EPIDEMIC_MAINWINDOW_H
