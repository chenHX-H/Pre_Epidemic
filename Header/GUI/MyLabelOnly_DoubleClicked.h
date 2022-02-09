//
// Created by chenhonxinh on 2021/12/21.
//

#ifndef PRE_EPIDEMIC_MYLABELONLY_DOUBLECLICKED_H
#define PRE_EPIDEMIC_MYLABELONLY_DOUBLECLICKED_H
#include <QLabel>
class MyLabelOnly_DoubleClicked:public QLabel{
    Q_OBJECT

public:
    MyLabelOnly_DoubleClicked(){};
    MyLabelOnly_DoubleClicked(QString str): QLabel(str){};
    void setFlag(int i){
        this->flag=i;
    };
    signals: void doubleClicked(int flag);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override{
        emit doubleClicked(flag);
    };

private:
    int flag=0;

};

#endif //PRE_EPIDEMIC_MYLABELONLY_DOUBLECLICKED_H
