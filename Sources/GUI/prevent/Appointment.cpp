//
// Created by chenhonxinh on 2021/12/24.
//

#include "Header/GUI/prevent/Appointment.h"
#include "Header/Application.h"
Appointment::Appointment(QString title): Pre_Base(title) {

    initUI();
}
void Appointment::initUI() {
    form=new QFormLayout;
    name=new QLineEdit;
    spin=new QSpinBox;
    idNumber=new QLineEdit;
    radios=new QWidget;
    radio1=new QRadioButton("男",radios);
    radio2=new QRadioButton("女",radios);
    combo=new QComboBox;
    combo->addItems(QStringList()<<"大学城医院"<<"垫江县人民医院"
    <<"重庆医科大学附属第一医院"<<"陆军军医大学第二附属医院");
    dateBtn=new QPushButton(QDate().currentDate().toString("yyyy/MM/dd"));
    calendarWidget=new QCalendarWidget;
    btnSubmit=new QPushButton("确认");

    initLayout();
    initStyle();
    bindingEvent();
}

void Appointment::initLayout() {
    this->main_QWidget->setLayout(form);

    form->addRow("姓名",name);
    form->addRow("性别",radios);
    form->addRow("年龄",spin);
    form->addRow("身份证号",idNumber);
    form->addRow("接种医院",combo);
    form->addRow("日期", dateBtn);
    form->addWidget(btnSubmit);



}

void Appointment::initStyle() {
    idNumber->setMaxLength(18);
    this->setStyleSheet(".QPushButton,.QLabel,QLineEdit,QSpinBox,QComboBox,QDateEdit"
                        "{font-size:25px;font-family:'黑体';}"
                        );

    form->setMargin(50);
    form->setSpacing(20);
//    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    name->setFixedSize(300,35);
    spin->setFixedSize(300,35);
    idNumber->setFixedSize(300,35);
    radio2->move(50,0);
    combo->setFixedSize(300,35);
    dateBtn->setFixedSize(300, 35);
    btnSubmit->setFixedSize(300, 35);
    btnSubmit->setCursor(QCursor(Qt::PointingHandCursor));
    dateBtn->setCursor(QCursor(Qt::PointingHandCursor));
    combo->setCursor(QCursor(Qt::PointingHandCursor));


}

void Appointment::bindingEvent() {

    QObject::connect(dateBtn, &QPushButton::clicked, this, &Appointment::openDateSelection);
    QObject::connect(calendarWidget,&QCalendarWidget::clicked,this,&Appointment::selectionDate );
    QObject::connect(btnSubmit,&QPushButton::clicked,this,&Appointment::onSubmit);
}

void Appointment::onSubmit() {
    if(name->text().isEmpty()){
        Application::getContentWindow()->showTipsWord("请输入真实姓名!",1500);
        return;
    } else if(!(radio1->isChecked() || radio2->isChecked())){
        Application::getContentWindow()->showTipsWord("请选择性别",1500);
        return;
    }else if(idNumber->text().length()<18){
        Application::getContentWindow()->showTipsWord("请输入合法身份证号",1500);
        return;
    }else if(spin->value()==0 || spin->value()>100){
        Application::getContentWindow()->showTipsWord("年龄不合法!",1500);
        return;
    }


    User *pUser = Application::getCurrentUser();


    Pre_user *pPreUser = pUser->getPreEpidemicData();
    BackLog pLog;
    pLog.setInoculateCount( pPreUser->getInoculateCount() );
    pLog.setInoculateTimeLast(pPreUser->getInoculateTimeLast());
    pLog.setNadCount(pPreUser->getNadCount());
    pLog.setInoculateName(pPreUser->getInoculateName());
    pLog.setNadLastTime(pPreUser->getNadLastTime());

    pLog.setId(pUser->getId());
//    pLog.setName(pUser->getNameZh());
    pLog.setName(name->text());
    if(radio1->isChecked()){
        pLog.setSex(true);
    }else{
        pLog.setSex(false);
    }
    pLog.setAge(spin->value());
    pLog.setIdNumber(idNumber->text());
    pLog.setOperation(title_lb->text().left(2));
    pLog.setMsg("病情");
    
    cout<<"并且："<<pLog.isSex();
    
    pUser->apply_for_dealWith(pLog);
}

void Appointment::openDateSelection() {
    calendarWidget->show();

}

void Appointment::selectionDate(QDate date) {
    const QString value = date.toString("yyyy/MM/dd");
    cout<<"当前"<<value.toStdString();
    calendarWidget->close();
    dateBtn->setText(value);
}

Appointment::~Appointment() {
    cout<<"Appointment析构执行"<<endl;
    delete btnSubmit;
    delete calendarWidget;
    delete dateBtn;
    delete combo;
    delete radio2;
    delete radio1;
    delete radios;
    delete idNumber;
    delete spin;
    delete name;
    delete form;
}