//
// Created by chenhonxinh on 2021/12/16.
//

#include "Header/GUI/Panel/Panel_4.h"
#include "Header/Application.h"
Panel_4::Panel_4() {
    Doctor *pDoctor = dynamic_cast<Doctor *>(Application::getCurrentUser());
    dataList=pDoctor->getALLBackLog();
    initUI();


}

void Panel_4::initUI() {
    vbox_rightFrame=new QVBoxLayout;
    dockRightWidget=new DockWidget_My("信息",this);
    dockRightWidget_second=new DockWidget_My("疫情相关",this);
    dockWidgetBottom=new DockWidget_My("相应操作",this);
    frameRight=new QFrame;
    frameRight_second=new QFrame;
    frameBottom=new QFrame;
    tabWidget=new QTabWidget;

    rightBottomLayout=new RightBottomLayout;
    bottomLayout=new BottomLayout(this);


    listTab.append(new Tab_Frame(this));
    listTab.append(new Tab_Frame(this));
    listTab.append(new Tab_Frame(this));
    listTab.append(new Tab_Frame(this));
    listTab.append(new Tab_Frame(this));

    rightMsg=new RightMsg();

    this->setALLTabData();

    initLayout();
    initStyle();
    bindingEvent();
    this->onTabClicked(0);
    dockRightWidget->close();
    dockRightWidget_second->close();


}

void Panel_4::initLayout() {
    this->setCentralWidget(tabWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, dockRightWidget);
    this->addDockWidget(Qt::RightDockWidgetArea,dockRightWidget_second);
    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidgetBottom);
    this->setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);

    dockRightWidget->setWidget(frameRight);
    dockRightWidget_second->setWidget(frameRight_second);
    dockWidgetBottom->setWidget(frameBottom);




    tabWidget->addTab(listTab.value(0),"ALL");
    tabWidget->addTab(listTab.value(1),"疫苗");
    tabWidget->addTab(listTab.value(2),"核酸检测");
    tabWidget->addTab(listTab.value(3),"门诊");
    tabWidget->addTab(listTab.value(4),"住院");

    frameRight->setLayout(vbox_rightFrame);
    frameRight_second->setLayout(rightBottomLayout);
    frameBottom->setLayout(bottomLayout);
    vbox_rightFrame->addWidget(rightMsg,1);

    this->setDockOptions(AnimatedDocks|AllowNestedDocks
                         |AllowTabbedDocks);
    dockRightWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

}

void Panel_4::initStyle() {
    this->dockRightWidget->close();
    this->dockRightWidget_second->close();
    this->dockWidgetBottom->close();
    this->setAnimated(true);
//    frameRight->setStyleSheet("background:gray;");
    frameRight->setMinimumWidth(300);
    frameBottom->setMinimumHeight(100);
//    frameRight_second->setStyleSheet("background:red");


}

void Panel_4::bindingEvent() {
    QObject::connect(tabWidget,&QTabWidget::tabBarClicked,this,&Panel_4::onTabClicked);
//    dockRightWidget.event
}

void Panel_4::onTabClicked(int i) {
    Tab_Frame *pWidget = dynamic_cast<Tab_Frame *>(tabWidget->widget(i));
    pWidget->setTableData(pWidget->getDataPrivate());
}

void Panel_4::setALLTabData() {
    for ( auto &item : listTab){
        item->getDataPrivate().clear();
    }
    for (const auto &item : dataList){
        const QStringList &valueRow = item.split('=');
        const QString &item_operation = valueRow.value(5);
        listTab.value(0)->getDataPrivate().append(item);
        if(item_operation.compare("疫苗")==0){
            listTab.value(1)->getDataPrivate().append(item);
        }else if(item_operation.compare("核酸")==0){
            listTab.value(2)->getDataPrivate().append(item);
        }else if(item_operation.compare("门诊")==0){
            listTab.value(3)->getDataPrivate().append(item);
        }else if(item_operation.compare("住院")==0){
            listTab.value(4)->getDataPrivate().append(item);
        }
    }
 ;
    tabWidget->tabBarClicked(   tabWidget->currentIndex());

}

void Panel_4::refreshUIData() {
    dataList.clear();
    Doctor *pUser = dynamic_cast<Doctor *>(Application::getCurrentUser());
    dataList=pUser->getALLBackLog();
    setALLTabData();
}

void Panel_4::showAllMsg(BackLog backlog ) {
    dockRightWidget->show();
    dockRightWidget_second->show();
    dockWidgetBottom->show();
    rightMsg->setMsg(backlog);
    rightBottomLayout->setMsg(backlog);
    cout<<"接种数量"<<backlog.getInoculateCount();
    cout<<"接种数量下的核酸总数"<<backlog.getNadCount()<<endl;
//    Application::getContentWindow()->setFixedWidth(1050);
}

BackLog Panel_4::transformToBackLog(QString str) {
    QStringList item=str.split('=');
    BackLog backLog;
    backLog.setId(item.value(0));
    backLog.setName(item.value(1));
    backLog.setSex(item.value(2).toInt());
    backLog.setAge(item.value(3).toInt());
    backLog.setIdNumber(item.value(4));
    backLog.setOperation(item.value(5));
    backLog.setMsg(item.value(6));
    backLog.setInoculateCount(item.value(7).toInt());
    backLog.setInoculateTimeLast(item.value(8));
    backLog.setInoculateName(item.value(9));
    backLog.setNadCount(item.value(10).toInt());
    backLog.setNadLastTime(item.value(11));
    return backLog;
}

Panel_4::~Panel_4() {
    cout<<"~Panel_4析构正在执行"<<endl;


    qDeleteAll(listTab);
    listTab.clear();


    delete tabWidget;

    delete rightBottomLayout;
    delete bottomLayout;
    delete vbox_rightFrame;

    delete frameBottom;
    delete frameRight_second;
    delete frameRight;

    delete dockRightWidget_second;
    delete dockWidgetBottom;
    delete dockRightWidget;


//


    cout<<"~Panel_4析构执行完毕"<<endl;

}



/*******Tab_Frame*********/
Panel_4::Tab_Frame::Tab_Frame(Panel_4* parent) {
    table=new QTableWidget(0,3);
    layout.addWidget(table,1);
    this->setLayout(&layout);
    this->parent_Panel4=parent;
    Panel_4::Tab_Frame::initUI();
}

void Panel_4::Tab_Frame::initUI() {
    table->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"年龄"<<"操作");
    QHeaderView *pView = table->verticalHeader();
    pView->setVisible(false);
    QHeaderView *pHeaderView = table->horizontalHeader();
    pHeaderView->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior ( QAbstractItemView::SelectRows);

    /***bindingEvent**/
    QObject::connect(table,&QTableWidget::itemDoubleClicked,this,&Panel_4::Tab_Frame::onClicked);
}

void Panel_4::Tab_Frame::onClicked(QTableWidgetItem *pItem) {
    QTableWidgetItem *pWidgetItem = table->item(pItem->row(), 0);
    QString name = pWidgetItem->text();
    for (const auto &item : dataPrivate){
         QStringList list = item.split('=');
        if(list.contains(name)){
            BackLog backLog;
            backLog.setName(list.value(1));
            backLog.setSex(list.value(2).toInt());
            backLog.setAge(list.value(3).toInt());
            backLog.setId(list.value(0));
            backLog.setOperation(list.value(5));
            backLog.setMsg(list.value(6));

            backLog.setIdNumber(list.value(4));
            backLog.setNadLastTime(list.value(11));
            backLog.setInoculateTimeLast(list.value(8));
            backLog.setInoculateCount(list.value(7).toInt());
            backLog.setInoculateName(list.value(9));
            backLog.setNadCount(list.value(10).toInt());

            parent_Panel4->showAllMsg(backLog);

        }
    }
}

void Panel_4::Tab_Frame::setTableData(QStringList data) {
    table->setRowCount(0);
    for(int i=0;i<data.count();i++){
        table->setRowCount(table->rowCount()+1);
        const QStringList &item = data.value(i).split('=');
        /******set table******/

            QTableWidgetItem *pItem = new QTableWidgetItem(item.value(1));
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
            table->setItem(i,0,pItem);

        QTableWidgetItem *pItem2 = new QTableWidgetItem(item.value(3));
        pItem2->setFlags(pItem2->flags() & ~Qt::ItemIsEditable);
        table->setItem(i,1,pItem2);

        QTableWidgetItem *pItem3 = new QTableWidgetItem(item.value(5));
        pItem3->setFlags(pItem3->flags() & ~Qt::ItemIsEditable);
        table->setItem(i,2,pItem3);
    }

}

QTableWidget *Panel_4::Tab_Frame::getTable() {
    return table;
}

QStringList &Panel_4::Tab_Frame::getDataPrivate()  {
    return dataPrivate;
}

void Panel_4::Tab_Frame::setDataPrivate(const QStringList &dataPrivate) {
    Tab_Frame::dataPrivate = dataPrivate;
}

Panel_4::Tab_Frame::~Tab_Frame() {
    cout<<"Tab_Frame析构正在执行"<<endl;

    delete table;
    cout<<"Tab_Frame执行完毕"<<endl;
}
/*******RightMsg*******/
Panel_4::RightMsg::RightMsg() {
    msgForm=new QFormLayout(this);
    lb_name=new QLabel("陈红鑫");
    lb_sex=new QLabel("性别");
    lb_age=new QLabel("年龄");
    lb_id=new QLabel("sdfds");
    btnLien=new QPushButton;
    lb_fenge=new QLabel("病情:");
    textIllness=new QTextEdit;

    msgForm->addRow("姓名:",lb_name);
    msgForm->addRow("性别",lb_sex);
    msgForm->addRow("年龄:",lb_age);
    msgForm->addRow("身份证号码:",lb_id);
    msgForm->addRow(btnLien);
    msgForm->addRow(lb_fenge);
    msgForm->addRow(textIllness);

    Panel_4::RightMsg::initStyle();
//    QObject::connect(textIllness,QTextEdit::cl)

}

void Panel_4::RightMsg::initStyle() {
    btnLien->setMaximumHeight(1);
    btnLien->setEnabled(false);

    lb_name->setFont(QFont("黑体", 12));
    lb_age->setFont(QFont("黑体", 12));
    lb_sex->setFont(QFont("黑体", 12));
    lb_id->setFont(QFont("黑体", 12));
    textIllness->setEnabled(false);
    textIllness->setFixedHeight(250);
    }


void Panel_4::RightMsg::onDoubleClick() {
}

void Panel_4::RightMsg::setMsg(BackLog backLog) {
    lb_name->setText(backLog.getName());
    lb_age->setText(QString("%1").arg(backLog.getAge()));

    if(backLog.isSex())
        lb_sex->setText("男");
    else
        lb_sex->setText("女");
    lb_id->setText(backLog.getIdNumber());
    textIllness->setText(backLog.getMsg());

}

Panel_4::RightMsg::~RightMsg() {
    cout<<"RightMsg析构正在执行"<<endl;


    delete lb_name;
    delete lb_age;
    delete lb_id;
    delete lb_sex;
    delete btnLien;
    delete lb_fenge;
    delete  textIllness;
    delete msgForm;
    cout<<"RightMsg析构执行完毕"<<endl;
}
/*****RightBottomLayout布局******/
Panel_4::RightBottomLayout::RightBottomLayout() {
    lb_NADLastTime=new QLabel("核酸时间");
    lb_NADCount=new QLabel("核酸次数");
    inoculate_count=new QLabel("疫苗针数");
    inoculate_lastTime=new QLabel("疫苗时间");
    inoculate_name=new QLabel("疫苗名称");

    this->addRow("核酸检测次数:", lb_NADCount);
    this->addRow("核酸检测时间:",lb_NADLastTime);
    this->addRow("接种疫苗针数:",inoculate_count);
    this->addRow("接种疫苗名称:",inoculate_name);
    this->addRow("接种疫苗时间(最近一次):",inoculate_lastTime);
}

void Panel_4::RightBottomLayout::setMsg(BackLog backLog) {
    lb_NADLastTime->setText(backLog.getNadLastTime());
    lb_NADCount->setText(QString("%1").arg(backLog.getNadCount()));
    inoculate_name->setText(backLog.getInoculateName());
    inoculate_count->setText(QString("%1").arg(backLog.getInoculateCount()));
    inoculate_lastTime->setText(backLog.getInoculateTimeLast());
}
Panel_4::RightBottomLayout::~RightBottomLayout() {
    cout<<"RightBottomLayout析构正在执行"<<endl;

    delete lb_NADLastTime;
    delete lb_NADCount;
    delete inoculate_lastTime;
    delete inoculate_count;
    delete inoculate_name;
    cout<<"RightBottomLayout析构执行完毕"<<endl;
}
/****BottomLayout*****/
Panel_4::BottomLayout::BottomLayout(Panel_4* parent_pointer) {
    btn_NAD=new QPushButton("核酸检测");
    btn_vaccinate=new QPushButton("打疫苗");
    btn_cure=new QPushButton("确诊");
    btn_InHospital=new QPushButton("住院");
    this->parent_pointer=parent_pointer;

    this->addWidget(btn_NAD);
    this->addWidget(btn_vaccinate);
    this->addWidget(btn_cure);
    this->addWidget(btn_InHospital);
    Panel_4::BottomLayout::initStyle();
    Panel_4::BottomLayout::bindingEvent();
}

void Panel_4::BottomLayout::initStyle() {
    btn_InHospital->setCursor(QCursor(Qt::PointingHandCursor));
    btn_cure->setCursor(QCursor(Qt::PointingHandCursor));
    btn_vaccinate->setCursor(QCursor(Qt::PointingHandCursor));
    btn_NAD->setCursor(QCursor(Qt::PointingHandCursor));

}

void Panel_4::BottomLayout::bindingEvent() {
    QObject::connect(btn_vaccinate,&QPushButton::clicked,this,&Panel_4::BottomLayout::onBtn_vaccinate_clicked);
    QObject::connect(btn_NAD,&QPushButton::clicked,this,&Panel_4::BottomLayout::onBtn_NAD_clicked);
}

void Panel_4::BottomLayout::onBtn_NAD_clicked() {
    BackLog backLog;
    Tab_Frame *pQWidget = dynamic_cast<Tab_Frame *>(parent_pointer->tabWidget->currentWidget());
    int i = pQWidget->getTable()->currentRow();
    const QString &naem = pQWidget->getTable()->item(i, 0)->text();
    const QString &op = pQWidget->getTable()->item(i, 2)->text();
    for (const auto &itemRow : pQWidget->getDataPrivate()){
        const QStringList &item = itemRow.split('=');
        if(item.contains(naem) && item.contains(op)){
            backLog = parent_pointer->transformToBackLog(itemRow);
        }
    }
    Doctor *pUser = dynamic_cast<Doctor *>(Application::getCurrentUser());
    pUser->doNAD(backLog);
    parent_pointer->closeALL();
    parent_pointer->refreshUIData();


}

void Panel_4::BottomLayout::onBtn_vaccinate_clicked() {
    BackLog backLog;
    Tab_Frame *pQWidget = dynamic_cast<Tab_Frame *>(parent_pointer->tabWidget->currentWidget());
    int i = pQWidget->getTable()->currentRow();
    const QString &naem = pQWidget->getTable()->item(i, 0)->text();
    const QString &op = pQWidget->getTable()->item(i, 2)->text();
    for (const auto &itemRow : pQWidget->getDataPrivate()){
        const QStringList &item = itemRow.split('=');
        if(item.contains(naem) && item.contains(op)){
             backLog = parent_pointer->transformToBackLog(itemRow);
        }
    }
    Doctor *pUser = dynamic_cast<Doctor *>(Application::getCurrentUser());
    pUser->vaccinate(backLog);
    parent_pointer->refreshUIData();
    parent_pointer->closeALL();

}

Panel_4::BottomLayout::~BottomLayout() {
    cout<<"BottomLayout析构正在执行"<<endl;

    delete btn_NAD;
    delete btn_vaccinate;
    delete btn_cure;
    delete btn_InHospital;
    cout<<"BottomLayout析构执行完毕"<<endl;

}

void Panel_4::DockWidget_My::closeEvent(QCloseEvent *event) {
    QDockWidget::closeEvent(event);
    parent_pointer->closeALL();


}

Panel_4::DockWidget_My::DockWidget_My(QString title,Panel_4 *panel41): QDockWidget(title) {
    this->parent_pointer=panel41;
}

void Panel_4::closeALL() {
    dockRightWidget->close();
    dockRightWidget_second->close();
    dockWidgetBottom->close();
}
