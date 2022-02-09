//
// Created by chenhonxinh on 2021/12/24.
//

#ifndef PRE_EPIDEMIC_REPORT_H
#define PRE_EPIDEMIC_REPORT_H
#include "Header/GUI/prevent/Pre_Base.h"
#include <QFormLayout>
class Report: public Pre_Base{
public:
    Report(const QString &title);
    ~Report();
    QFormLayout *formLayout1;
    void initLayout();
    void initStyle();
    void refreshUIData();

private:
    QLabel* lb_seal;//印章
    QLabel* lb_name;
    QLabel* lb_sex;
    QLabel* lb_age;
    QLabel* lb_id;
    QLabel* lb_NADCount;
    QLabel* lb_NADLastTime;
    QLabel* lb_InoculateName;
    QLabel* lb_InoculateLastTime;
    QLabel* lb_InoculateCount;
    QLabel* lb_status;

};


#endif //PRE_EPIDEMIC_REPORT_H
