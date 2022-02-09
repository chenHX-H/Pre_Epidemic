//
// Created by chenhonxinh on 2021/12/16.
//

#ifndef PRE_EPIDEMIC_PANEL_2_H
#define PRE_EPIDEMIC_PANEL_2_H


#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include "Header/GUI/MySwitch_Icon.h"
#include <QInputDialog>
class Panel_2: public QWidget{
public:
    Panel_2();
    ~Panel_2();
    QTableWidget* table;
    void setTableData(QStringList,int flag=0);
    const QStringList &getAllData() const;
    void setAllData(const QStringList &allData);
    void refreshUI(int flag=0);

protected:
    class Right: public QWidget{
    public:
        static Panel_2* parent_pointer;
        Right();
        ~Right();

        MySwitch_Icon *getIcon1() const;

        MySwitch_Icon *getIcon2() const;

    protected:
        void initLayout();
        void initStyle();
        void bindingEvent();

    private:
        QHBoxLayout   hbox;
        MySwitch_Icon *icon1;
        MySwitch_Icon *icon2;
//        MySwitch_Icon icon3;
        void onClickedLabel(int i);

    };
    void initUI();
    void initStyle();
    void initLayout();
    void bindingEvent();

private:
    QStringList allData;


};


#endif //PRE_EPIDEMIC_PANEL_2_H
