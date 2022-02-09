//
// Created by chenhonxinh on 2021/12/24.
//

#include "Header/GUI/prevent/Report.h"
#include "Header/Application.h"
Report::Report(const QString &title) : Pre_Base(title) {
    formLayout1=new QFormLayout;
    lb_name=new QLabel("陈红鑫");
    lb_sex=new QLabel("男");
    lb_age=new QLabel("19");
    lb_id=new QLabel("500231200208063378");
    lb_NADCount=new QLabel("2");
    lb_NADLastTime=new QLabel("2020/8/6");
    lb_InoculateName=new QLabel("科兴");
    lb_InoculateLastTime=new QLabel("2020/8/7");
    lb_InoculateCount=new QLabel("3");
    lb_status=new QLabel("合格");
    lb_seal=new QLabel;
    initLayout();
    initStyle();
    refreshUIData();
}



void Report::initLayout() {

    this->setFont(QFont("黑体",20));
    this->main_QWidget->setFont(QFont("黑体",20));
    lb_seal->setParent(this);
    main_QWidget->setLayout(formLayout1);
    formLayout1->addRow("姓名:",lb_name);
    formLayout1->addRow("性别",lb_sex);
    formLayout1->addRow("年龄",lb_age);
    formLayout1->addRow("身份证号",lb_id);
    formLayout1->addRow("核酸检测次数:",lb_NADCount);
    formLayout1->addRow("最近一次核酸检测时间",lb_NADLastTime);
    formLayout1->addRow("接种疫苗名:",lb_InoculateName);
    formLayout1->addRow("最后接种疫苗时间",lb_InoculateLastTime);
    formLayout1->addRow("接种疫苗针数:",lb_InoculateCount);
    formLayout1->addRow("检验状态",new QLabel("正常"));

}

void Report::initStyle() {
    lb_seal->setFont(*Application::getIconFont());
    lb_seal->setText(QChar(0xe606));
    lb_seal->setStyleSheet("color:red;font-size:120px;");
    lb_seal->move(350,210);
    this->main_QWidget->setStyleSheet(".QLabel{font-size:20px;font-family:'黑体';}");
//    this->formLayout1->setSpacing(20);
    formLayout1->setHorizontalSpacing(30);
    formLayout1->setVerticalSpacing(25);
    this->formLayout1->setAlignment(Qt::AlignCenter);
    formLayout1->setContentsMargins(100,0,0,0);


}

void Report::refreshUIData() {
    User *pUser = Application::getCurrentUser();
    pUser->queryPreEpidemicMsg();
    Pre_user *pPreUser = pUser->getPreEpidemicData();
    lb_name->setText(pUser->getNameZh());
    lb_id->setText(pUser->getIdNumber());
    if(pUser->isSex()){
        lb_sex->setText("男");
    }else{
        lb_sex->setText("女");
    }
    lb_age->setText(QString("%1").arg(pUser->getAge()));
    lb_InoculateName->setText(pPreUser->getInoculateName());
    lb_InoculateLastTime->setText(pPreUser->getInoculateTimeLast());
    lb_InoculateCount->setText(QString("%1").arg(pPreUser->getInoculateCount()));
    lb_NADCount->setText(QString("%1").arg(pPreUser->getNadCount()));
    lb_NADLastTime->setText(pPreUser->getNadLastTime());


}

Report::~Report() {
    delete lb_name;
    delete lb_sex;
    delete lb_age;
    delete lb_id;
    delete lb_NADCount;
    delete lb_NADLastTime;
    delete lb_InoculateCount;
    delete lb_InoculateLastTime;
    delete lb_InoculateName;
    delete lb_status;
}

