//
// Created by chenhonxinh on 2021/12/24.
//

#ifndef PRE_EPIDEMIC_APPOINTMENT_H
#define PRE_EPIDEMIC_APPOINTMENT_H

#include "Header/GUI/prevent/Pre_Base.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QComboBox>
#include <QDateEdit>
#include "QCalendarWidget"
#include "Header/Data/BackLog.h"
class Appointment : public Pre_Base {
public:
    Appointment(QString title = "默认");

    ~Appointment();


protected:
    void initUI();

    void initLayout();

    void initStyle();

    void bindingEvent();

private:
    QFormLayout*     form;
    QLineEdit*       name;
    QSpinBox *       spin;
    QLineEdit*       idNumber;
    QWidget*         radios;
    QRadioButton*    radio1;
    QRadioButton*    radio2;
    QComboBox*       combo;
    QPushButton*     dateBtn;
    QCalendarWidget* calendarWidget;
    QPushButton*     btnSubmit;
    void openDateSelection();
    void selectionDate(QDate);
    void onSubmit();



};


#endif //PRE_EPIDEMIC_APPOINTMENT_H
