//
// Created by chenhonxinh on 2021/12/24.
//

#include "Header/GUI/prevent/Pre_Base.h"
#include "Header/Application.h"

Pre_Base::Pre_Base(QString title) {

//    this->setStyleSheet("background:gray");
    initUI();
    this->title_lb->setText(title);
}
void Pre_Base::initUI() {
    back_lb=new MySwitch_Icon;
    main_QWidget=new QWidget;
    hbox_top=new QHBoxLayout;

    vbox=new QVBoxLayout;
    back_lb=new MySwitch_Icon;
    back_lb->setFlag(7);
    title_lb=new QLabel;

    initLayout();
    initStyle();
    bindingEvent();

}

void Pre_Base::initLayout() {
    this->setLayout(vbox);

    hbox_top->addWidget(back_lb);
    hbox_top->addWidget(title_lb);
    vbox->addLayout(hbox_top);
    vbox->addWidget(main_QWidget,9);
    vbox->setContentsMargins(0,0,0,0);
}

void Pre_Base::initStyle() {
    this->setFixedSize(700,700);

    QFont pFont = *Application::getIconFont();
    pFont.setPixelSize(30);
    back_lb->setFont(pFont);
    back_lb->setText(QChar(0xe602));

    back_lb->setFixedSize(50,50);
    back_lb->setCursor(QCursor(Qt::PointingHandCursor));
    back_lb->setToolTip("返回");
    back_lb->setStyleSheet("background:white");
    back_lb->setAlignment(Qt::AlignCenter);


    title_lb->setFont(QFont("黑体",18,QFont::Bold));
//    title_lb->setStyleSheet("color:white");
    title_lb->setAlignment(Qt::AlignCenter);
    main_QWidget->setObjectName("main_QWidget");
    main_QWidget->setStyleSheet("#main_QWidget{border-top:1px solid black;"
                                "background:rgba(255,255,255,1);}");
    title_lb->setStyleSheet("Label{background:rgba(255,255,255,1);}");


}

void Pre_Base::bindingEvent() {
    QObject::connect(back_lb,&MySwitch_Icon::clicked,this,&Pre_Base::backToSuper);
}

void Pre_Base::backToSuper() {
    QStackedLayout *pLayout = Application::getContentWindow()->getWindowsLayout();
    pLayout->setCurrentIndex(2);
    cout<<"back前有:"<<pLayout->count()<<endl;
    pLayout->removeWidget(this);
    cout<<"back后有:"<<pLayout->count()<<endl;
    
}

Pre_Base::~Pre_Base() {
    delete hbox_top;
    delete back_lb;
    delete main_QWidget;
    delete vbox;
}