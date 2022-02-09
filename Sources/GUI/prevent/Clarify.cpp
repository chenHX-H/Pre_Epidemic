//
// Created by chenhonxinh on 2021/12/24.
//

#include "Header/GUI/prevent/Clarify.h"

Clarify::Clarify(const QString &title) : Pre_Base(title) {
        listVBox=new QVBoxLayout;
        scrollArea=new QScrollArea;
        scrollFrame=new QFrame;
        scrollLayout=new QVBoxLayout;

    main_QWidget->setLayout(listVBox);
    listVBox->addWidget(scrollArea);
    ClarifyItem *pItem = new ClarifyItem;
    ClarifyItem *pItem2 = new ClarifyItem;

    pItem->lb_title->setText("板蓝根可以治疗新冠吗?:");
    pItem->lb_content->setText("众所周知，板蓝根是一种神药，吃了能上天...");

    pItem2->lb_title->setText("连花清瘟胶囊真的有用吗？");
    pItem2->lb_content->setText("真的可以");
    scrollFrame->setLayout(scrollLayout);
    scrollLayout->addWidget(pItem);
    scrollLayout->addWidget(pItem2);
    scrollArea->setWidget(scrollFrame);
    scrollArea->setAlignment(Qt::AlignCenter);



}

Clarify::~Clarify() {
    delete listVBox;
}
/***ClarifyItem***/
Clarify::ClarifyItem::ClarifyItem() {
    form=new QFormLayout;
    lb_title=new QLabel;
    lb_content=new QLabel;


    this->setLayout(form);
    form->addWidget(lb_title);
    form->addWidget(lb_content);


    /**style**/
    lb_title->setFixedSize(500,50);
    lb_content->setMinimumHeight(300);
    lb_content->setAlignment(Qt::AlignTop);
    lb_title->setFont(QFont("宋体",16));
    lb_content->setFont(QFont("宋体",12));

    form->setAlignment(lb_title,Qt::AlignCenter);
    this->setStyleSheet(".QFrame,QLabel{border:2px solid gray ;color:white;}");
    this->lb_title->setStyleSheet("background:rgb(18,150,219);");
    this->lb_content->setStyleSheet("color:black");
    lb_title->setAlignment(Qt::AlignCenter);

}

Clarify::ClarifyItem::~ClarifyItem() {
    delete lb_title;
    delete lb_content;
    delete form;
}
