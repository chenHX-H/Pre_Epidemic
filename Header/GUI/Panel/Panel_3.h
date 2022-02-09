//
// Created by chenhonxinh on 2021/12/16.
//

#ifndef PRE_EPIDEMIC_PANEL_3_H
#define PRE_EPIDEMIC_PANEL_3_H


#include <QLabel>
#include <QListWidget>
#include "Header/GUI/MySwitch_Icon.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Header/GUI/prevent/Appointment.h"
#include "Header/GUI/prevent/Clarify.h"
#include "Header/GUI/prevent/Pre_Base.h"
#include "Header/GUI/prevent/Report.h"

class Panel_3: public QWidget {
public:
    Panel_3();
    ~Panel_3();
    Report* getReport();


protected:
    void initData();
    void initUI();
    void initStyle();
    void initLayout();
    void bindingEvent();

    class Card:public QWidget{
    public:
        Card(QWidget* parent,Panel_3*);
        Card(QString title,QWidget* parent,Panel_3*);
        Card(QString title,Panel_3*);
        Card(Panel_3*);
        ~Card();
        void initUI();
        void setTitle(QString title);
        QString getTitle();
        void openShadow(bool open=false);
        void setIconLB(QChar);
        MySwitch_Icon* getIconLB();
    protected:
        void initStyle();
        void initLayout();
        void bindingEvent();
    private:
        QVBoxLayout vbox;
        QLabel* lb_top;
        MySwitch_Icon* icon_lb;
        Panel_3* parent_pointer;

    };
private:
    QStringList  itemCardName;
    QList<Card*> listCard;
    QWidget* mainQWidget;
    QHBoxLayout *hbox;
    QLabel* lb_title;
    QLabel* lb_bottom;
    Card* left_card;
    Card* center_card;
    Card* right_card;
    MySwitch_Icon *lb_left;
    MySwitch_Icon *lb_right;
    Appointment* appointment;
    Appointment* appointment2;
    Report* report;
    Clarify* clarify;
    void toListItemSlide(int flag);
    void onClicked_ICon(int i);




};


#endif //PRE_EPIDEMIC_PANEL_3_H
