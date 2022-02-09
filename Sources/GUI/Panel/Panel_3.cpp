//
// Created by chenhonxinh on 2021/12/16.
//

#include <QListView>
#include <QGraphicsDropShadowEffect>
#include "Header/GUI/Panel/Panel_3.h"
#include "Header/Application.h"

Panel_3::Panel_3() {
    lb_left=new MySwitch_Icon;
    lb_right=new MySwitch_Icon;
    lb_title=new QLabel("疫情防护，人人有责!",this);
    lb_bottom=new QLabel("版权所有©chenhonxin 重庆师范大学",this);

    appointment=new Appointment("疫苗预约");
    appointment2=new Appointment("核酸检测");
    report=new Report("报告查询");
    clarify=new Clarify("辟谣小知识");
    initData();
    initUI();


}

void Panel_3::initUI() {

    mainQWidget=new QWidget(this);
    hbox=new QHBoxLayout;
    mainQWidget->setLayout(hbox);
    mainQWidget->move(-150,100);
    mainQWidget->setFixedSize(1000,500);

//    mainQWidget->setStyleSheet("background-color:gray;");

        left_card=listCard.value(0);
        center_card=listCard.value(1);
        right_card=listCard.value(2);



    initLayout();
    initStyle();
    bindingEvent();
}

void Panel_3::initStyle() {
    QFont *pFont = Application::getIconFont();
//    this->setStyleSheet("background:rgba(93,103,187,0.5)");
    lb_left->setParent(this);
    lb_right->setParent(this);
    lb_left->setFixedSize(50,150);
    lb_right->setFixedSize(50,150);
    lb_left->move(0,this->height()/2-lb_right->height()/2+20);
    lb_right->move(this->width()+20,this->height()/2-lb_right->height()/2+20);

    lb_left->setCursor(QCursor(Qt::PointingHandCursor));
    lb_right->setCursor(QCursor(Qt::PointingHandCursor));

    lb_left->setStyleSheet("QLabel:hover{color:white;background-color:rgba(0,0,0,0.2);}"
                           "QLabel{font-size:40px;}");
    lb_right->setStyleSheet("QLabel:hover{color:white;background-color:rgba(0,0,0,0.2);}"
                           "QLabel{font-size:40px;}");

    lb_left->setFont(*pFont);
    lb_left->setText(QChar(0xe62c));
    lb_right->setFont(*pFont);
    lb_right->setText(QChar(0xe623));
    lb_left->setFlag(1);
    lb_right->setFlag(2);

    lb_title->setFixedWidth(700);
    lb_title->move(0,30);
    lb_title->setFont(QFont("华文彩云",25,QFont::Bold));
    lb_title->setAlignment(Qt::AlignCenter);

    lb_bottom->setFont(QFont("宋体",18,QFont::Bold));
    lb_bottom->setStyleSheet("color:gray");
    lb_bottom->move(0,600);
    lb_bottom->setFixedWidth(700);
    lb_bottom->setAlignment(Qt::AlignCenter);



}



void Panel_3::bindingEvent() {
    lb_left->setFlag(1);
    lb_right->setFlag(2);
    QObject::connect(lb_left, &MySwitch_Icon::clicked, this, &Panel_3::toListItemSlide);
    QObject::connect(lb_right, &MySwitch_Icon::clicked, this, &Panel_3::toListItemSlide);
}

void Panel_3::toListItemSlide(int flag)  {

        hbox->removeWidget(left_card);
        hbox->removeWidget(center_card);
        hbox->removeWidget(right_card);
        left_card->setParent(nullptr);
        center_card->setParent(nullptr);
        right_card->setParent(nullptr);

    int iLeft=listCard.indexOf(left_card);;
    int iCenter=listCard.indexOf(center_card);;
    int iRingth=listCard.indexOf(right_card);;
    int listCount = listCard.count();
    if(flag==1){

        iRingth=iCenter;
        iCenter=iLeft;
        iLeft-=1;
        if(iLeft<0){
            iLeft=listCount-1;
        }

    }else if(flag==2){
        iLeft=iCenter;
        iCenter=iRingth;
        iRingth+=1;
        if(iRingth>listCount-1){
            iRingth=0;
        }
    }
    cout<<"这时:l c r:"<<iLeft<<" "<<iCenter<<" "<<iRingth<<endl;
    left_card=listCard.value(iLeft);
    center_card=listCard.value(iCenter);
    right_card=listCard.value(iRingth);

    hbox->addWidget(left_card);
    hbox->addWidget(center_card);
    hbox->addWidget(right_card);

    left_card->openShadow(false);
    center_card->openShadow(true);
    right_card->openShadow(false);
//    hbox->update();




}

void Panel_3::initData() {
    itemCardName<<"疫苗预约"<<"核算检测"<<"报告查询"<<"辟谣小知识";
    int i=1;
    for (const auto &item : itemCardName){
        Card* pCard=new Card(item,this);
        pCard->getIconLB()->setFlag(i++);
        listCard.append(pCard);
    }
    listCard.value(0)->setIconLB(QChar(0xe654));
    listCard.value(1)->setIconLB(QChar(0xe689));
    listCard.value(2)->setIconLB(QChar(0xe650));
    listCard.value(3)->setIconLB(QChar(0xe6bd));


}

void Panel_3::initLayout() {

    hbox->addWidget(left_card);
    hbox->addWidget(center_card);
    hbox->addWidget(right_card);

}

void Panel_3::Card::setTitle(QString title) {
    this->lb_top->setText(title);
}

MySwitch_Icon* Panel_3::Card::getIconLB() {
    return icon_lb;
}

Panel_3::~Panel_3() {
    delete lb_left;
    delete lb_right;
    delete lb_title;
    delete lb_bottom;
    qDeleteAll(listCard);
    listCard.clear();
//    delete right_card;
//    delete center_card;
//    delete left_card;

    delete hbox;
    delete mainQWidget;



}


/****Card类******/
Panel_3::Card::Card(Panel_3* p) {
    parent_pointer=p;
    Panel_3::Card::initUI();
}
Panel_3::Card::Card(QWidget* parent,Panel_3* p): QWidget(parent) {
    parent_pointer=p;

    Panel_3::Card::initUI();
}

Panel_3::Card::Card(QString title, QWidget *parent,Panel_3* p): QWidget(parent) {
    parent_pointer=p;

    Panel_3::Card::initUI();

    this->setTitle(title);
}

Panel_3::Card::Card(QString title,Panel_3* p) {
    parent_pointer=p;

    Panel_3::Card::initUI();

    this->setTitle(title);

}

void Panel_3::Card::openShadow(bool open) {
    if(open){
        /********/
        this->setWindowFlags(Qt::FramelessWindowHint);
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(8);        // 阴影圆角的大小
        effect->setColor(Qt::gray);      //阴影的颜色
        effect->setOffset(5,5);          //阴影的偏移量
        this->setGraphicsEffect(effect); //给那个控件设置阴影，这里需要注意的是所有此控件的子控件，也都继承这个阴影。
    }else{
        this->setGraphicsEffect(nullptr); //给那个控件设置阴影，这里需要注意的是所有此控件的子控件，也都继承这个阴影。

    }
}

void Panel_3::Card::initUI() {

    cout<<"Card：iniUI执行"<<endl;
    lb_top=new QLabel("标题",this);
    icon_lb=new MySwitch_Icon();


    Panel_3::Card::initStyle();
    Panel_3::Card::initLayout();
    Panel_3::Card::bindingEvent();



}



void Panel_3::Card::bindingEvent() {
QObject::connect(icon_lb,&MySwitch_Icon::clicked,parent_pointer,&Panel_3::onClicked_ICon);
}

void Panel_3::onClicked_ICon(int i) {

    QStackedLayout *pLayout = Application::getContentWindow()->getWindowsLayout();
    Pre_Base *base= nullptr;

    switch (i) {
        case 1:base = appointment; break;
        case 2:base=appointment2;break;
        case 3:base=report;break;
        case 4:base=clarify;break;
        default:return;

    }

    pLayout->addWidget(base);
    pLayout->setCurrentWidget(base);

}

void Panel_3::Card::initLayout() {
    this->setLayout(&vbox);
    vbox.addWidget(lb_top,1);
    vbox.addWidget(icon_lb,5);
    vbox.setAlignment(icon_lb,Qt::AlignCenter);
}

void Panel_3::Card::initStyle() {

    this->setStyleSheet("QWidget{border-radius:5px;border:2px  gray black;background:rgba(51,102,153,1)}");
    this->setFixedSize(320,450);
    lb_top->setFont(QFont("黑体",18));
    lb_top->setStyleSheet("background:rgb(18,150,219);color:white;");
    lb_top->setAlignment(Qt::AlignCenter);

    icon_lb->setStyleSheet("border:1px solid black;");
    icon_lb->setFixedSize(100,100);
    icon_lb->setAlignment(Qt::AlignCenter);
    QFont font1 = *Application::getIconFont();
    font1.setPointSize(50);
    icon_lb->setFont(font1);
    icon_lb->setCursor(QCursor(Qt::PointingHandCursor));
    icon_lb->setStyleSheet("QLabel:hover{background:rgba(0,0,0,0.5);}"
                           "QLabel{color:white;border:3px solid gray;border-radius:5px;}");

}

void Panel_3::Card::setIconLB(QChar qchar) {
    this->icon_lb->setText(qchar);
}

QString Panel_3::Card::getTitle() {
    return lb_top->text();
}

Panel_3::Card::~Card() {
    cout<<"Card析构执行"<<endl;
    delete lb_top;
    delete icon_lb;

}

Report *Panel_3::getReport() {
    return  report;
}
