//
// Created by chenhonxinh on 2021/12/24.
//

#ifndef PRE_EPIDEMIC_PRE_BASE_H
#define PRE_EPIDEMIC_PRE_BASE_H
#include "Header/GUI/MySwitch_Icon.h"
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
using namespace std;
class Pre_Base: public QWidget{
public:
    Pre_Base(QString title);
    ~Pre_Base();

protected:
    void initUI();
    void initLayout();
    void initStyle();
    void bindingEvent();
    QVBoxLayout* vbox;
    QHBoxLayout* hbox_top;
    QWidget* main_QWidget;
    MySwitch_Icon* back_lb;
    QLabel* title_lb;


private:
    void backToSuper();


};


#endif //PRE_EPIDEMIC_PRE_BASE_H
