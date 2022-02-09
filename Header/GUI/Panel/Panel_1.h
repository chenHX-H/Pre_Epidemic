//
// Created by chenhonxinh on 2021/12/16.
//

#ifndef PRE_EPIDEMIC_PANEL_1_H
#define PRE_EPIDEMIC_PANEL_1_H


#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include "Header/GUI/MySwitch_Icon.h"
#include "Header/GUI/MyLabelOnly_DoubleClicked.h"

class Panel_1: public QWidget{
public:
    Panel_1();
    ~Panel_1();

    QListWidget *getList() const;
    void refreshData();


protected:
    class ItemModel:public QWidget{
    public:
        ItemModel(QString,Panel_1*);
        QString str;

        ~ItemModel();
    private:
        int rows=-1;
    public:
        void setRows(int rows);
        int getRows() const;
        void setAllEnabled(bool  b);

    private:
        bool  isRead= false;
        Panel_1* parent_potiner;
        QHBoxLayout* hbox;
        QLabel* lb_left;
        MyLabelOnly_DoubleClicked * lb_center;
        QLabel* lb_time;
        QHBoxLayout* right;
        MySwitch_Icon * right_1;
        MySwitch_Icon* right_2;
        MySwitch_Icon* right_3;
        QString sendTime;
        void initLayout();
        void initStyle();
        void bindingEvent();
        void onClicked(int );

    };
    class MsgBox:public QWidget{
    public:
        MsgBox();
        void setContent(QStringList);

    protected:
      void  initStyle();
      void  initLayout();
    private:
        QVBoxLayout vbox;
        QHBoxLayout hbox_top;
        QLabel lb_content;
        QHBoxLayout hbox_bottom;

        /***hbox-top***/
        QLabel lb_top_left;
        QLabel lb_top_center;
        QLabel lb_top_right;
        QPushButton btn_line;


    };

    void deleteWidget();
    void setWidget_to_Top();
private:
    QList<ItemModel*> listWidget;
    QListWidget* list;
    MsgBox* msgBox;
    void initNotice();
    void initStyle();
    void bindingEvent();
    void onClicked();
    void showMessage(ItemModel*);

};


#endif //PRE_EPIDEMIC_PANEL_1_H
