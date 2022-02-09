//
// Created by chenhonxinh on 2021/12/28.
//

#include "Header/GUI/Panel/Panel_6.h"

// Created by chenhonxinh on 2021/12/17.
//

#include "Header/Application.h"

Panel_6::Panel_6() {
    initUI();
    bindingEvent();

}

void Panel_6::initUI() {
    noticeMsg=new Notice_Msg;
    gridLayout=new QGridLayout;
    addMaterial=new Add_Material;
    ratifyDocotor=new RatifyDoctor(this);
    lookOverMsg=new LookOverMsg(this);

   pBxo = new ItemBxo;
   pBxo1 = new ItemBxo;
   pBxo2 = new ItemBxo;

   pBxo->lb_title->setText("公告发布");
   pBxo1->lb_title->setText("新加物资");
   pBxo2->lb_title->setText("医护人员身份审核");
//   pBxo->lb_icon->setText()

    
    initLayout();
    initStyle();
}

void Panel_6::initLayout() {
    this->setLayout(gridLayout);
    gridLayout->addWidget(pBxo,0,0,1,2);
    gridLayout->addWidget(pBxo1,1,0);
    gridLayout->addWidget(pBxo2,1,1);
    gridLayout->setRowStretch(0,1);
    gridLayout->setRowStretch(1,2);


}


void Panel_6::bindingEvent() {

    QObject::connect(pBxo->lb_icon,&MySwitch_Icon::clicked,this,&Panel_6::sendNotice);
    QObject::connect(pBxo1->lb_icon,&MySwitch_Icon::clicked,this,&Panel_6::addMaterials);
    QObject::connect(pBxo2->lb_icon,&MySwitch_Icon::clicked,this,&Panel_6::stepRatify);

}

void Panel_6::stepRatify() {
    ratifyDocotor->show();
}

void Panel_6::sendNotice() {
    noticeMsg->show();
}

void Panel_6::addMaterials() {
 addMaterial->show();

}

void Panel_6::initStyle() {
    QFont pFont = *Application::getIconFont();
    pFont.setPixelSize(100);
    pBxo->lb_icon->setFont(pFont);
    pBxo1->lb_icon->setFont(pFont);
    pBxo2->lb_icon->setFont(pFont);
    pBxo->lb_icon->setText(QChar(0xe64d));
    pBxo1->lb_icon->setText(QChar(0xe603));
    pBxo2->lb_icon->setText(QChar(0xe61e));
    this->setStyleSheet("QLabel{color:white;}");
    gridLayout->setMargin(120);

}

Panel_6::~Panel_6() {
    cout<<"即将delete NotceMsg"<<endl;
    delete pBxo;
    delete pBxo1;
    delete pBxo2;
    delete addMaterial;
    delete ratifyDocotor;
//    delete gridLayout;
    //  delete noticeMsg; //释放报错!不明白?
    cout<<"Panel_5析构执行完毕"<<endl;
}

void Panel_6::refreshUIData() {
   this->ratifyDocotor->refreshUIData();
}

/******公告发布Dialog*******/
Panel_6::Notice_Msg::Notice_Msg() {
    this->setWindowModality(Qt::ApplicationModal);
    this->setLayout(&vbox);
    initUI();
    initLayout();
    initStyle();
    bindingEvent();
}

void Panel_6::Notice_Msg::initUI() {
    this->setFixedSize(600,500);
    this->setWindowTitle("公告发布");
    this->setWindowIcon(*Application::getFaviconIcon());
    lb_title.setText("标题");
    lb_content.setText("正文");
}

void Panel_6::Notice_Msg::initLayout() {
    vbox.addLayout(&form,9);
    vbox.addLayout(&hbox,1);
    form.addRow(&lb_title,&edit_title);
    form.addRow(&lb_content,&edit_content);
    hbox.addWidget(&btn_confirm);
    hbox.addWidget(&btn_cancel);
}

void Panel_6::Notice_Msg::initStyle() {
    edit_title.setFixedHeight(50);
    QFont qFont = QFont("黑体", 16);
    lb_content.setFont(qFont);
    lb_title.setFont(qFont);
    edit_title.setFont(qFont);
    edit_content.setFont(qFont);
    edit_content.setFixedHeight(350);
    btn_confirm.setText("发布");
    btn_cancel.setText("取消");
    hbox.setContentsMargins(55,0,30,0);
    hbox.setSpacing(50);

}

void Panel_6::Notice_Msg::bindingEvent() {
    QObject::connect(&btn_confirm,&QPushButton::clicked,this,&Panel_6::Notice_Msg::onConfirm_Clicked);
    QObject::connect(&btn_cancel,&QPushButton::clicked,this,&Panel_6::Notice_Msg::onCancel_Clicked);

}

void Panel_6::Notice_Msg::onConfirm_Clicked() {
    Admin *pUser = static_cast<Admin *>(Application::getCurrentUser());
    QStringList stringList;
    stringList.append(edit_title.text());
    stringList.append(edit_content.toPlainText());

    const QString &tiem = QDate::currentDate().toString("MM:dd") + " " + QTime::currentTime().toString("hh:mm");
    stringList.append(tiem);
    pUser->announce(stringList);
    this->close();


}

void Panel_6::Notice_Msg::onCancel_Clicked() {
    this->close();
}



/******ItemBox******/
Panel_6::ItemBxo::ItemBxo() {
    this->setWindowModality(Qt::ApplicationModal);
    vbox=new QVBoxLayout(this);
    lb_title=new QLabel("标题");
    lb_icon=new MySwitch_Icon("名称");

//    this->setFixedSize(150,150);





    Panel_6::ItemBxo::initLayout();
    Panel_6::ItemBxo::initStyle();
    Panel_6::ItemBxo::bindingEvent();
}

void Panel_6::ItemBxo::initStyle() {
    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setStyleSheet("QWidget{background:rgb(18,150,219);border:5px solid gray;}"
                        ".QWidget:hover{background:rgba(18,150,219,0.5)}");
    lb_title->setAlignment(Qt::AlignCenter);
    lb_icon->setAlignment(Qt::AlignCenter);
    lb_icon->setStyleSheet("color:white");
    lb_icon->setStyleSheet("border:null");
    lb_title->setStyleSheet("border:null");
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(8);        // 阴影圆角的大小
    effect->setColor(Qt::gray);      //阴影的颜色
    effect->setOffset(5,5);          //阴影的偏移量
    this->setGraphicsEffect(effect); //给那个控件设置阴影，这里需要注意的是所有此控件的子控件，也都继承这个阴
}

void Panel_6::ItemBxo::initLayout() {
    vbox->addWidget(lb_icon,4);
    vbox->addWidget(lb_title,1);
}

void Panel_6::ItemBxo::bindingEvent() {
//    QObject::connect()
}

Panel_6::ItemBxo::~ItemBxo() {
    delete lb_title;
    delete lb_icon;
    delete vbox;
}
/****Add_Material******/
Panel_6::Add_Material::Add_Material() {
    this->setWindowModality(Qt::ApplicationModal);
    form=new QFormLayout(this);
    name=new QLineEdit;
    kind=new QLineEdit;
    count=new QSpinBox;
    is_regualte=new QComboBox;
    btn_confirm=new QPushButton("添加");
    is_regualte->addItems(QStringList()<<"是"<<"否");
    form->addRow("物资名:",name);
    form->addRow("总量:",count);
    form->addRow("种类:",kind);
    form->addRow("是否管制",is_regualte);
    form->addRow(btn_confirm);

    name->setFixedHeight(30);
    kind->setFixedHeight(30);
    count->setFixedHeight(30);
    is_regualte->setFixedHeight(30);
    btn_confirm->setFixedHeight(30);
    this->setFixedSize(200,200);
    QObject::connect(btn_confirm,&QPushButton::clicked,this,&Panel_6::Add_Material::onBtnClicked);
    this->setWindowModality(Qt::WindowModal);
}

void Panel_6::Add_Material::onBtnClicked() {
    if(name->text().isEmpty()){
        this->close();
        Application::getContentWindow()->showTipsWord("物资名不能为空",1500);
        return;
    }
    if(count->value()==0){
        this->close();
        Application::getContentWindow()->showTipsWord("物资数量不能为空",1500);
        return;
    }
    if(kind->text().isEmpty()){
        this->close();
        Application::getContentWindow()->showTipsWord("请输入物资类属",1500);
        return;
    }
    Admin *pUser = dynamic_cast<Admin *>(Application::getCurrentUser());


    Materials materials(name->text().toStdString(),count->value());
    materials.setKind(kind->text().toStdString());
    if(is_regualte->currentIndex()==0){
        materials.setIsRegulate(true);
    }else {
        materials.setIsRegulate(false);
    }
    bool b = pUser->addNewMaterial(materials);

    this->close();
    if(!b){
        Application::getContentWindow()->showTipsWord("添加失败,已存在同名物资!",1500);
    }else{
        Application::getContentWindow()->showTipsWord("添加成功!",1500);
    }

}

Panel_6::Add_Material::~Add_Material() {
    delete is_regualte;
    delete kind;
    delete count;
    delete name;
    delete form;
}

/****RatifyDoctor*****/
Panel_6::RatifyDoctor::RatifyDoctor(Panel_6* panel6) {
    this->parent_pointer=panel6;
    this->setWindowModality(Qt::ApplicationModal);

    vbox=new QVBoxLayout(this);
    lb_title=new QLabel("申请列表");
    table=new QTableWidget(0,2);


    Panel_6::RatifyDoctor::initLayout();
    Panel_6::RatifyDoctor::initStyle();
    Panel_6::RatifyDoctor::refreshUIData();
}

void Panel_6::RatifyDoctor::refreshUIData() {
    qDeleteAll(listBtn);
    listBtn.clear();
    data.clear();
    data= Application::getCurrentUser()->getListWantBeDoctor();
    table->setRowCount(0);

    for(int i=0;i<data.count();i++){
        table->setRowCount(table->rowCount()+1);
        const QStringList &item= data.value(i).split('=');
        QTableWidgetItem *pItem = new QTableWidgetItem(item.value(0));
        table->setItem(i,0,pItem);
        listBtn.append(new Btns(parent_pointer));
        table->setCellWidget(i,1,listBtn.value(i));
    }
}

void Panel_6::RatifyDoctor::initLayout() {
    vbox->addWidget(lb_title,1);
    vbox->addWidget(table,7);
}

void Panel_6::RatifyDoctor::initStyle() {
    this->setFixedSize(400,600);
    lb_title->setFont(QFont("楷体",22,QFont::Bold));
    lb_title->setAlignment(Qt::AlignCenter);
    table->setColumnWidth(0,100);
    table->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"操作");
    QHeaderView *pView = table->horizontalHeader();
    pView->setStretchLastSection(true);
    
    
    
}

Panel_6::RatifyDoctor::~RatifyDoctor() {
    qDeleteAll(listBtn);
    listBtn.clear();
    delete lb_title;
    delete table;
    delete vbox;

}

QTableWidget *Panel_6::RatifyDoctor::getTable() {
    return  table;
}

QStringList Panel_6::RatifyDoctor::getData() {
    return data;
}

/***Btn**/
Panel_6::RatifyDoctor::Btns::Btns(Panel_6* panel6) {
    this->parent_pointer=panel6;
    hbox=new QHBoxLayout(this);
    lb_look=new MySwitch_Icon("查看");
    lb_agree=new MySwitch_Icon("批准");
    lb_refuse=new MySwitch_Icon("拒绝");
    hbox->addWidget(lb_look);
    hbox->addWidget(lb_agree);
    hbox->addWidget(lb_refuse);


    this->setStyleSheet("QLabel:hover{color:red;}");
    lb_look->setCursor(QCursor(Qt::PointingHandCursor));
    lb_refuse->setCursor(QCursor(Qt::PointingHandCursor));
    lb_agree->setCursor(QCursor(Qt::PointingHandCursor));


    lb_look->setFlag(1);
    lb_agree->setFlag(2);
    lb_refuse->setFlag(3);
    QObject::connect(lb_look,&MySwitch_Icon::clicked,this,&Panel_6::RatifyDoctor::Btns::onClickedLable);
    QObject::connect(lb_agree,&MySwitch_Icon::clicked,this,&Panel_6::RatifyDoctor::Btns::onClickedLable);
    QObject::connect(lb_refuse,&MySwitch_Icon::clicked,this,&Panel_6::RatifyDoctor::Btns::onClickedLable);

}

void Panel_6::RatifyDoctor::Btns::onClickedLable(int i) {
    cout<<i;
    int ix = this->frameGeometry().x();
    int iy = this->frameGeometry().y();
    const QModelIndex &index = parent_pointer->ratifyDocotor->table->indexAt(QPoint(ix, iy));
    const QString &name = parent_pointer->ratifyDocotor->table->item(index.row(), 0)->text();

    switch (i) {
        case 1:{
            parent_pointer->lookOverMsg->show();
            const QPixmap &pixmap = Application::getCurrentUser()->getDoctorMaterialPIC(name);
            parent_pointer->lookOverMsg->showDetail(name,pixmap);
            break;
        }
        case 2:{
            Application::getCurrentUser()->dealFinishedDoctorApply(name,1);
            break;
        };
        case 3:{
            Application::getCurrentUser()->dealFinishedDoctorApply(name);
            break;
        }
    }
    this->parent_pointer->ratifyDocotor->refreshUIData();

}

Panel_6::RatifyDoctor::Btns::~Btns() {
    cout<<"Btn析构正在执行"<<endl;
    delete lb_agree;
    delete lb_refuse;
    delete lb_look;
    delete hbox;
    cout<<"Btn析构执行完毕"<<endl;
}
/******LookOverMsg*****/
Panel_6::LookOverMsg::LookOverMsg(Panel_6* panel6) {
    parent_pointer=panel6;
    form=new QFormLayout;
    lb_content=new QLabel;
    lb_img=new QLabel;


    Panel_6::LookOverMsg::initLayout();
    Panel_6::LookOverMsg::initStyle();
}

void Panel_6::LookOverMsg::initLayout() {
        form->addRow("申请信息:",lb_content);
        form->addRow("医护人员资格证:",lb_img);

}

void Panel_6::LookOverMsg::initStyle() {
    this->setFixedSize(500,650);
    this->setWindowModality(Qt::ApplicationModal);
    this->setLayout(form);
    lb_content->setFixedHeight(280);
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    lb_content->setStyleSheet("border:2px solid gray;background:white;");
    lb_content->setFont(QFont("楷体",15,QFont::Bold));
    lb_content->setAlignment(Qt::AlignTop);
    lb_img->setFixedHeight(280);
    lb_img->setStyleSheet("border:2px  solid gray ");


}

void Panel_6::LookOverMsg::showDetail(QString name,QPixmap img) {
    const QStringList &list = parent_pointer->ratifyDocotor->getData();
    for (const auto &item : list){
        if(item.contains(name)){
            const QString &msg = item.split('=').value(1);
            lb_content->setText(msg);
        }
    }

    lb_img->setAlignment(Qt::AlignCenter);
    lb_img->setPixmap(img.scaled(lb_img->width()-5,lb_img->height()-5,Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Panel_6::LookOverMsg::~LookOverMsg() {
    delete lb_img;
    delete lb_content;
    delete form;
}

