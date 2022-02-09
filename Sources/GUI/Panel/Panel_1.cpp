//
// Created by chenhonxinh on 2021/12/16.
//

#include "Header/GUI/Panel/Panel_1.h"
#include "Header/Application.h"


Panel_1::Panel_1(){
    list=new QListWidget(this);
    msgBox=new MsgBox;
    initNotice();
    initStyle();
    bindingEvent();

}

void Panel_1::refreshData() {
    cout<<"Panel1刷新:"<<endl;
    while (list->count() > 0)
    {
        QListWidgetItem *item = list->takeItem(0);
        list->removeItemWidget(item);
        delete item;
    }
    const QStringList &qStringList = Application::getDatabase_Connection()->getAnnouncement();
    for (const auto &strItem : qStringList){
        QListWidgetItem * pItem=new QListWidgetItem();
        pItem->setSizeHint(QSize(1000,50));
        ItemModel *pModel = new ItemModel(strItem,this);
        pModel->setRows(list->count());
        listWidget.append(pModel);
        list->addItem(pItem);
        list->setItemWidget(pItem,pModel);
    }
}
void Panel_1::initNotice() {

    const QStringList &qStringList = Application::getDatabase_Connection()->getAnnouncement();
    for (const auto &strItem : qStringList){
        QListWidgetItem * pItem=new QListWidgetItem();
            pItem->setSizeHint(QSize(1000,50));
        ItemModel *pModel = new ItemModel(strItem,this);
        pModel->setRows(list->count());
        listWidget.append(pModel);
        list->addItem(pItem);
        list->setItemWidget(pItem,pModel);
    }


}

void Panel_1::initStyle() {
    this->setFixedHeight(650);
    this->setFixedWidth(700);
//    list->setGridSize(QSize(620,650)); //--->导致严重bug
    list->setFixedSize(700,650);
    list->setFont(QFont("黑体",18));
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    list->setFrameShape(QListView::NoFrame);
    list->setCursor(QCursor(Qt::PointingHandCursor));



}

void Panel_1::bindingEvent() {
    QObject::connect(list,&QListWidget::itemClicked,this,&Panel_1::onClicked);
}

void Panel_1::onClicked() {
  for(int  i=0;i<list->count();i++){
      QListWidgetItem *pItem = list->item(i);
      ItemModel *pWidget = dynamic_cast<ItemModel *>(list->itemWidget(pItem));
      pWidget->setAllEnabled(false);
  }
  
    ItemModel *currentWidget = dynamic_cast<ItemModel *>(list->itemWidget(list->currentItem()));
    currentWidget->setAllEnabled(true);

}


void Panel_1::deleteWidget() {
    cout<<"\n开始执行delte操作，当前总数:"<<list->count()<<endl;
    cout<<"执行之前:当前编号:"<<list->currentRow();

    QListWidgetItem *pItem = list->currentItem();
    list->setItemWidget(pItem, nullptr);
    list->removeItemWidget(list->takeItem(list->currentRow()));
    delete pItem;
    cout<<"执行完后:当前编号:"<<list->currentRow()<<endl;

    ItemModel *currentNew = dynamic_cast<ItemModel *>(list->itemWidget(list->currentItem()));
    currentNew->setAllEnabled(true);

}

void Panel_1::setWidget_to_Top() {

    cout<<"置顶之前coutn="<<list->count()<<endl;
    QListWidgetItem *pItem = new QListWidgetItem();
    ItemModel *pWidget = dynamic_cast<ItemModel *>(list->itemWidget(list->currentItem()));
    ItemModel* itemModel=new ItemModel(pWidget->str,this);
    pItem->setSizeHint(QSize(50,50));

        list->insertItem(0,pItem);
    list->setItemWidget(pItem,itemModel);


    cout<<"置顶之后cout="<<list->count()<<endl;
    deleteWidget();

}

void Panel_1::showMessage(ItemModel* itemModel) {
    const QStringList &stringList = itemModel->str.split('=');
    msgBox->setContent(stringList);
}

QListWidget *Panel_1::getList() const {
    return list;
}

Panel_1::~Panel_1() {
    cout<<"Panel_1析构函数被执行"<<endl;
    for(int i=0;i<list->count();i++){
        delete list->item(i);
    }
    delete list;
    delete msgBox;
}




/****以下为内部类->ItemModel定义****/

Panel_1::ItemModel::ItemModel(QString str,Panel_1* parent_p) {
    this->str.append(str);
    this->parent_potiner=parent_p;
    hbox=new QHBoxLayout(this);
    const QStringList &stringList = str.split('=');
    lb_left=new QLabel();
    lb_time=new QLabel(stringList.last());
    lb_center=new MyLabelOnly_DoubleClicked(stringList.value(1));

    right=new QHBoxLayout;
    right_1=new MySwitch_Icon;
    right_2=new MySwitch_Icon;
    right_3=new MySwitch_Icon;


    this->initLayout();
    this->initStyle();
    bindingEvent();
}

void Panel_1::ItemModel::initLayout() {
    hbox->addWidget(lb_left,1);
    hbox->addWidget(lb_time,1);
    hbox->addWidget(lb_center,6);
    hbox->addLayout(right,1);
    right->addWidget(right_1,2);
    right->addWidget(right_2,2);
    right->addWidget(right_3,2);
    lb_left->setText("[未读]");
}

void Panel_1::ItemModel::initStyle() {
    this->setMaximumWidth(670);
    lb_left->setFont(QFont("黑体",12));
    lb_time->setAlignment(Qt::AlignLeft);
    lb_center->setFont(QFont("宋体",16));
    lb_center->setContentsMargins(15,0,0,0);
    right_1->setFont(*Application::getIconFont());
    right_2->setFont(*Application::getIconFont());
    right_3->setFont(*Application::getIconFont());

    right_1->setText(QChar(0xe62a)+QString(" "));
    right_2->setText(QChar(0xe74b)+QString(" "));
    right_3->setText(QChar(0xe601));

    right_1->setToolTip("置顶");
    right_2->setToolTip("删除");
    right_3->setToolTip("已读");

    right_1->setEnabled(false);
    right_2->setEnabled(false);
    right_3->setEnabled(false);

//    lb_center->setStyleSheet("background-color:red");
    lb_center->setAlignment(Qt::AlignLeft);
    this->setStyleSheet("QWidget{background-color:rgba(244,244,244,0.5)};");
    lb_center->setStyleSheet("QWidget:hover{color:rgba(0,0,0,0.5);}");


}

void Panel_1::ItemModel::bindingEvent() {

    right_1->setFlag(1);
    right_2->setFlag(2);
    right_3->setFlag(3);
    lb_center->setFlag(4);
    QObject::connect(right_1,&MySwitch_Icon::clicked,this,&Panel_1::ItemModel::onClicked);
    QObject::connect(right_2,&MySwitch_Icon::clicked,this,&Panel_1::ItemModel::onClicked);
    QObject::connect(right_3,&MySwitch_Icon::clicked,this,&Panel_1::ItemModel::onClicked);
    QObject::connect(lb_center,&MyLabelOnly_DoubleClicked::doubleClicked,this,&Panel_1::ItemModel::onClicked);

}

void Panel_1::ItemModel::onClicked(int i) {
    switch (i) {
        case 1:{
            cout<<"开始置顶事件"<<endl;
           parent_potiner-> setWidget_to_Top();
            break;
        }
        case 2:{
            cout<<"开始ItemModel删除事件"<<endl;
            parent_potiner->deleteWidget();
            break;}
        case 3:{
            if(!isRead){
                lb_left->setText("[已读]");
                QFont qFont = lb_center->font();
                qFont.setStrikeOut(true);
                lb_center->setFont(qFont);
                lb_center->setStyleSheet("color:gray;");
                lb_left->setEnabled(false);
                lb_time->setEnabled(false);
               
            }else{
                lb_left->setText("[未读]");
                lb_left->setEnabled(true);
                lb_time->setEnabled(true);
                QFont qFont = lb_center->font();

                qFont.setStrikeOut(false);
                lb_center->setFont(qFont);
                lb_center->setStyleSheet("color:black;");
            }
            isRead=!isRead;
            break;
        }
        case 4:{
            parent_potiner->showMessage(this);
            break;
        }
    }
}

void Panel_1::ItemModel::setRows(int rows) {
    ItemModel::rows = rows;
}
int Panel_1::ItemModel::getRows() const {
    return rows;
}
void Panel_1::ItemModel::setAllEnabled(bool b) {
    if(b){


        right_1->setStyleSheet("QLabel:hover{color:rgba(18,150,219,0.8);}"
                               "QLabel{color:rgb(18,150,219);}");
        right_2->setStyleSheet("QLabel:hover{color:rgba(216,30,6,0.8);}"
                               "QLabel{color:rgb(216,30,6)}");
        right_3->setStyleSheet("QLabel:hover{color:rgba(81,81,81,0.8);}"
                               "QLabel{color:rgb(81,81,81)}");
    }else{
        right_1->setStyleSheet("QLabel:hover{color:rgba(0,0,0,0.7);}"
                               "QLabel{color:rgba(0,0,0,1);}");
        right_2->setStyleSheet("QLabel:hover{color:rgba(0,0,0,0.7);}"
                               "QLabel{color:rgba(0,0,0,1)}");
        right_3->setStyleSheet("QLabel:hover{color:rgba(0,0,0,0.7);}"
                               "QLabel{color:rgba(0,0,0,1)}");
    }

    right_1->setEnabled(b);
    right_2->setEnabled(b);
    right_3->setEnabled(b);
    /******
     *    lb_center->setStyleSheet("QWidget:hover{color:rgba(0,0,0,0.5);}");

    right_1->setStyleSheet("QLabel:hover{color:rgba(18,150,219,0.8);}"
                           "QLabel{color:rgb(18,150,219);}");
    right_2->setStyleSheet("QLabel:hover{color:rgba(216,30,6,0.8);}"
                           "QLabel{color:rgb(216,30,6)}");
    right_3->setStyleSheet("QLabel:hover{color:rgba(81,81,81,0.8);}"
                           "QLabel{color:rgb(81,81,81)}");
     *
     * ******/
}

Panel_1::ItemModel::~ItemModel() {
    cout<<"ItemModel析构函数被执行"<<endl;
    delete hbox;
    delete lb_left;
    delete lb_center;
    delete right_1;
    delete right_2;
    delete right_3;
    cout<<"ItemModel析构函数执行完毕"<<endl;
//    delete right;

}

/*******以下为MsgBox类的********/
Panel_1::MsgBox::MsgBox() {
    this->setLayout(&vbox);
    initLayout();
    Panel_1::MsgBox::initStyle();
}
void Panel_1::MsgBox::initStyle() {
    this->setFixedSize(750,550);
    lb_content.setFont(QFont("宋体",18));
    QFont lb_font("宋体",15);
    lb_top_left.setFont(lb_font);
    lb_top_center.setFont(lb_font);
    lb_top_right.setFont(lb_font);
    btn_line.setMaximumHeight(1);
    btn_line.setEnabled(false);
    lb_content.setAlignment(Qt::AlignTop);
//    this->setWindowFlag(Qt::FramelessWindowHint);
}

void Panel_1::MsgBox::initLayout() {
    vbox.addLayout(&hbox_top,1);
    vbox.addWidget(&btn_line);
    vbox.addWidget(&lb_content,6);
    vbox.addLayout(&hbox_bottom,1);
    hbox_top.addWidget(&lb_top_left,1);
    hbox_top.addWidget(&lb_top_center,1);
    hbox_top.addWidget(&lb_top_right,1);

}

void Panel_1::MsgBox::setContent(QStringList stringList) {
    lb_content.setText(stringList.value(2));
    lb_top_left.setText("发件人:管理员");
    lb_top_center.setText("标题:"+stringList.value(1));
    lb_top_right.setText("发送时间:"+stringList.value(3));

    this->show();
}


