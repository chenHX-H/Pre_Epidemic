//
// Created by chenhonxinh on 2021/12/20.
//

#ifndef PRE_EPIDEMIC_MYSWITCH_ICON_H
#define PRE_EPIDEMIC_MYSWITCH_ICON_H

#include <QLabel>
class MySwitch_Icon: public QLabel {
Q_OBJECT
public:
    MySwitch_Icon(QString str): QLabel(str){};
    MySwitch_Icon(){};
    void setFlag(int i){
    flag=i;
}
    int flag=0;
protected:
    void mousePressEvent(QMouseEvent *ev) override{
    emit clicked(flag);
};

    void enterEvent(QEvent *event) override {
        QWidget::enterEvent(event);
        emit mouseOver(flag);
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event);
        emit mouseOff(flag);
    }

private:

signals:
     void clicked(int);
     void mouseOver(int );
     void mouseOff(int );

};


#endif //PRE_EPIDEMIC_MYSWITCH_ICON_H
