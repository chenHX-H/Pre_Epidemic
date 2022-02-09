//
// Created by chenhonxinh on 2021/12/14.
//

#include "Header/GUI/MySwitchButton.h"
#include "Header/Application.h"

MySwitchButton::MySwitchButton() {
    this->initUI();
}
MySwitchButton::MySwitchButton(QWidget *parent): QLabel(parent) {
    this->initUI();
}
bool MySwitchButton::isCurrentStateChecked() const {
    return current_state_checked;
}

void MySwitchButton::setCurrentStateChecked(bool currentStateChecked) {
    current_state_checked = currentStateChecked;
}
void MySwitchButton::initUI() {
    this->setFixedSize(200,30);
//    this->setStyleSheet("border:1px solid black");
    QFont *qfont=Application::getIconFont();
    qfont->setPixelSize(24);
    this->setFont(*qfont);
    this->setText(QChar(0xe60f));
}

void MySwitchButton::toggle_impl() {
    current_state_checked=!current_state_checked;
    if(current_state_checked){
      this->setText(QChar(0xe608));
        this->setStyleSheet("color:DeepSkyBlue;");

    }else{
        this->setText(QChar(0xe60f));
        this->setStyleSheet("color:black;");


    }
}

void MySwitchButton::mousePressEvent(QMouseEvent *ev) {
    QLabel::mousePressEvent(ev);
    toggle_impl();
    qDebug()<<QString("11");
}


