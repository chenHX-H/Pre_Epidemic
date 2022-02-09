//
// Created by chenhonxinh on 2021/12/14.
//

#include "Header/GUI/ClientWindow.h"
#include "Header/GUI/Panel/Panel_5.h"
#include "Header/Application.h"
ClientWindow::ClientWindow(User* user) {
    this->currentUser=user;
    enquiryDialog= new EnquiryDialog(this);
    provideMaterials=new ProvideMaterials(this);


}



void ClientWindow::init_noDoctor_UI(QTreeWidgetItem * p1, QTreeWidgetItem * p2) {
    this->addList_and_window(p1, nullptr);
    this->addList_and_window(p2, nullptr);
}

void ClientWindow::init_Doctor_UI(QTreeWidgetItem *p1, QTreeWidgetItem *p2) {
    this->addList_and_window(p1,new Panel_4);
    this->addList_and_window(p2,new Panel_5);

}



void ClientWindow::initDifference() {
    if(currentUser->isDoctor1()){
        this->setWindowTitle("疫情管理系统-(用户端-医护人员)");

    }else{
        this->setWindowTitle("疫情管理系统-(用户端)");
    }
    auto* pItem2=new QTreeWidgetItem(QStringList("物资申请"));
    auto *pItem2_1 = new QTreeWidgetItem(QStringList("食品物资"));
    auto *pItem2_2 = new QTreeWidgetItem(QStringList("生活物资"));
    auto *pItem2_3 = new QTreeWidgetItem(QStringList("医疗物资"));
    pItem2->addChild(pItem2_1);
    pItem2->addChild(pItem2_2);
    pItem2->addChild(pItem2_3);
    auto *pItem1 = new QTreeWidgetItem(QStringList("公告"));
    auto *pItem3 = new QTreeWidgetItem(QStringList("疫情预防"));

    auto *pItem4 = new QTreeWidgetItem(QStringList("医疗系统"));
    auto *pItem5 = new QTreeWidgetItem(QStringList("疫情监控"));


    iconlist.append("../Resources/left-item/notice_unselected.png");
    iconlist.append("../Resources/left-item/goods_unselected.png");
    iconlist.append("../Resources/left-item/inoculate_unselected.png");
    iconlist.append("../Resources/left-item/medical_unselected.png");
    iconlist.append("../Resources/left-item/monitoring_unselected.png");
    //  一闪而过小窗口的定位,首次new Panel后
    this->addList_and_window(pItem1,new Panel_1);
    this->addList_and_window(pItem2,new Panel_2);
    this->addList_and_window(pItem3, new Panel_3);

    pItem1->setIcon(0,QIcon(iconlist.value(0)));
    pItem2->setIcon(0,QIcon(iconlist.value(1)));
    pItem3->setIcon(0,QIcon(iconlist.value(2)));
    pItem4->setIcon(0,QIcon(iconlist.value(3)));
    pItem5->setIcon(0,QIcon(iconlist.value(4)));



    if(currentUser->isDoctor1()){
        init_Doctor_UI(pItem4,pItem5);
        this->setWindowTitle("疫情管理系统-(用户端-医护人员)");

    }else{
        init_noDoctor_UI(pItem4,pItem5);
        this->setWindowTitle("疫情管理系统-(用户端)");
    }


}
/***主要用于处理角色差异不同，用户/医生/管理员 ——>物资申请 ***/
void ClientWindow::initRoleDifference() {
    Panel_2 *panel2_pontiner = dynamic_cast<Panel_2 *>(widgetList.value(1));

}

void ClientWindow::start() {
    MainWindow::start();
    initDifference();
    initRoleDifference();
}

void ClientWindow::onNotEnabledItemClicked() {
//    QMessageBox::StandardButton result = QMessageBox::information(this, "权限不足","此为医护人员专用功能");
    enquiryDialog->show();

}

/****权限不足时的询问对话框****/
ClientWindow::EnquiryDialog::EnquiryDialog(ClientWindow* parent_pointer) {
    this->parent_ponter=parent_pointer;
    this->setWindowModality(Qt::ApplicationModal);
    grid=new QGridLayout;
    tip_img=new QLabel("图片");
    tipTexts=new QLabel("文本");
    btnConfirm=new QPushButton("确认");
    btnRegister=new QPushButton("注册");

    grid->addWidget(tip_img,0,0);
    grid->addWidget(tipTexts,0,1);
    grid->addWidget(btnRegister,1,0);
    grid->addWidget(btnConfirm,1,1);

    grid->setRowStretch(0,3);
    grid->setRowStretch(1,1);


    tip_img->setFont(*Application::getIconFont());
    tip_img->setText(QChar(0xe604));
    tip_img->setFixedSize(50,50);
    tip_img->setAlignment(Qt::AlignCenter);
    tip_img->setStyleSheet("background:rgb(18,150,219);font-size:40px;");

    tipTexts->setText("权限不足\n医护人员专用功能!");

    QObject::connect(btnConfirm,&QPushButton::clicked,this,&ClientWindow::EnquiryDialog::onConfirm);
    QObject::connect(btnRegister,&QPushButton::clicked,this,&ClientWindow::EnquiryDialog::onRegister);
    this->setLayout(grid);

}

void ClientWindow::EnquiryDialog::onConfirm() {
    this->close();
}

void ClientWindow::EnquiryDialog::onRegister() {
    cout<<"注册事件被执行";
    this->close();
    this->parent_ponter->provideMaterials->show();
}

ClientWindow::EnquiryDialog::~EnquiryDialog() {
    cout<<"EnquiryDialog析构函数正在执行"<<endl;
    delete tip_img;
    delete tipTexts;
    delete btnConfirm;
    delete btnRegister;
    delete grid;
}
/****内部内部类****/
ClientWindow::ProvideMaterials::ProvideMaterials(ClientWindow* parent_pointer) {
   this->parent_pointer=parent_pointer;
    grid=new QGridLayout;
    this->setLayout(grid);
    lb_title=new QLabel("医护人员权限申请");
    textEdit=new QTextEdit("材料");
    btnConfirm=new QPushButton("申请");
    btnCancel=new QPushButton("取消");
    lb_img=new MySwitch_Icon;

    this->setLayout(grid);
    grid->addWidget(lb_title,0,0,1,2);
    grid->addWidget(textEdit,1,0,1,2);
    grid->addWidget(lb_img,2,0,1,2);
    grid->addWidget(btnConfirm,3,0);
    grid->addWidget(btnCancel,3,1);

    grid->setRowStretch(0,1);
    grid->setRowStretch(1,8);
    grid->setRowStretch(2,3);


    initStyle();
    bidingEvent();
}

void ClientWindow::ProvideMaterials::onConfirm() {
    cout<<"事件触发:"<<textEdit->toPlainText().toStdString()<<endl;
    QFile file(currenPath);
    file.open(QIODevice::ReadOnly);
    const QByteArray data = file.readAll();
    file.close();
    Application::getCurrentUser()->apply_becomeToDoctor(textEdit->toPlainText(),data);
    this->close();
}

void ClientWindow::ProvideMaterials::onCancel() {
    this->close();
}

void ClientWindow::ProvideMaterials::initStyle() {

    this->setFixedSize(500,500);
    lb_title->setStyleSheet("background:red;");
    lb_title->setFont(QFont("楷体",22,QFont::Bold));
    lb_title->setAlignment(Qt::AlignCenter);
    lb_img->setFont(*Application::getIconFont());
    lb_img->setText(QChar(0xe70a));
    lb_img->setStyleSheet("QLabel{background:rgba(18,150,219,0.8);color:white;font-size:50px;}"
                          "QLabel:hover{rgba(18,150,219,0.5)}");
    lb_img->setAlignment(Qt::AlignCenter);
    lb_img->setCursor(QCursor(Qt::PointingHandCursor));

    btnCancel->setEnabled(false);
    btnConfirm->setEnabled(false);




}

void ClientWindow::ProvideMaterials::bidingEvent() {
    QObject::connect(btnConfirm,&QPushButton::clicked,this,&ClientWindow::ProvideMaterials::onConfirm);
    QObject::connect(btnCancel,&QPushButton::clicked,this,&ClientWindow::ProvideMaterials::onCancel);
    QObject::connect(lb_img,&MySwitch_Icon::clicked,this,&ClientWindow::ProvideMaterials::selectFile);
}

void ClientWindow::ProvideMaterials::selectFile() {
    btnCancel->setEnabled(true);
    btnConfirm->setEnabled(true);
    const QString &filePath = QFileDialog::getOpenFileName(this, "1", "", "*.png");
    QFile *pFile = new QFile(filePath);
    pFile->open(QIODevice::ReadOnly);
    const QByteArray &data = pFile->readAll();
    pFile->close();
    QPixmap pic;
    pic.loadFromData(data,".png");
    lb_img->setPixmap(pic);
    lb_img->setScaledContents(true);
    currenPath=filePath;

}

ClientWindow::ProvideMaterials::~ProvideMaterials() {

}
