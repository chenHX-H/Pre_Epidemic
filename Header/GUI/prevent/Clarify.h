//
// Created by chenhonxinh on 2021/12/24.
//

#ifndef PRE_EPIDEMIC_CLARIFY_H
#define PRE_EPIDEMIC_CLARIFY_H

#include "Header/GUI/prevent/Pre_Base.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
class Clarify: public Pre_Base{
public:
    Clarify(const QString &title);
    ~Clarify();
    class ClarifyItem:public QFrame{
    public:
        ClarifyItem();
        ~ClarifyItem();
        QFormLayout* form;
        QLabel* lb_title;
        QLabel* lb_content;

    };
    QVBoxLayout* listVBox;
    QScrollArea* scrollArea;
    QFrame* scrollFrame;
    QVBoxLayout* scrollLayout;

};


#endif //PRE_EPIDEMIC_CLARIFY_H
