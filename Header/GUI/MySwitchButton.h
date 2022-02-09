//
// Created by chenhonxinh on 2021/12/14.
//

#ifndef PRE_EPIDEMIC_MYSWITCHBUTTON_H
#define PRE_EPIDEMIC_MYSWITCHBUTTON_H
//#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <iostream>

class MySwitchButton: public QLabel{
public:
    MySwitchButton();
    MySwitchButton(QWidget* parent);
    bool isCurrentStateChecked() const;
    void setCurrentStateChecked(bool currentStateChecked);

protected:
    void mousePressEvent(QMouseEvent *ev) override;

private:
    bool current_state_checked= false;
    void toggle_impl();
    void initUI();


};


#endif //PRE_EPIDEMIC_MYSWITCHBUTTON_H
