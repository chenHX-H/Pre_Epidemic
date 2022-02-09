//
// Created by chenhonxinh on 2021/12/15.
//

#include "Header/GUI/MainWindow.h"
#include "Header/Application.h"
void MainWindow::start() {
    this->initUI();
    this->show();

}


MainWindow::MainWindow() {
    lb_refresh=new MySwitch_Icon;
    treeWidgets=new QTreeWidget;
    windows_layout=new QStackedLayout;
    centerQWidget=new QWidget;
    hbox_outest=new QHBoxLayout(centerQWidget);
    vbox_fiexd=new QVBoxLayout();
    currentUser=Application::getCurrentUser();
    lb_tip=new QLabel("提示框");
}

void MainWindow::addList_and_window(QTreeWidgetItem * pItem, QWidget *pWidget) {

    itemList.append(pItem);
    widgetList.append(pWidget);
    treeWidgets->addTopLevelItem(pItem);
    if(pWidget!= nullptr){
        windows_layout->addWidget(pWidget);
    }
    initStyle();
}



void MainWindow::initUI() {

    this->setFixedSize(850,650);
    this->setWindowIcon(QPixmap("../favicon.ico"));

    this->setWindowTitle("疫情管理监控系统-客户端");
    initLayout();
    initStyle();
    initBindingEvent();
    int i = treeWidgets->currentIndex().row();
}

void MainWindow::initLayout() {
    lb_refresh->setParent(this);
    this->setCentralWidget(centerQWidget);
    hbox_outest->addWidget(treeWidgets,2);
    hbox_outest->addLayout(vbox_fiexd,9);
//    vbox_fiexd->addWidget(panelBar ,1);
    vbox_fiexd->addLayout(windows_layout);
    lb_tip->setParent(this);
    /************/
}

void MainWindow::initStyle() {
    lb_refresh->setFixedSize(50,50);
    lb_refresh->setObjectName("refresh");
    lb_refresh->setStyleSheet("#refresh{background:rgb(18,150,219);color:white;}"
                              "#refresh:hover{background:rgba(18,150,219,0.7);color:rgba(0,0,0,0.8);}");
    lb_refresh->move(840,0);
    lb_refresh->raise();
    lb_refresh->setCursor(QCursor(Qt::PointingHandCursor));
    QFont ppFont = *Application::getIconFont();
    lb_refresh->setFont(ppFont);
    lb_refresh->setText(QChar(0xe604));
    lb_refresh->setAlignment(Qt::AlignCenter);


    lb_tip->setStyleSheet("background-color:rgba(0,0,0,0.7);color:white;");
    lb_tip->setFixedHeight(50);
    lb_tip->setMaximumWidth(500);
    lb_tip->setAlignment(Qt::AlignCenter);
    lb_tip->move(this->width()/2-lb_tip->width()/2,this->height()/2-lb_tip->height()/2-50);
    lb_tip->setFont(QFont("黑体",18,QFont::Bold));
    lb_tip->setVisible(false);



    hbox_outest->setMargin(0);
    treeWidgets->setRootIsDecorated(false); //是否显示左边的折叠三角形
    treeWidgets->setHeaderHidden(true);     //隐藏控件头
    treeWidgets->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏滚动条
    treeWidgets->setStyleSheet("QTreeView{ outline: 0px;}"
                               "QTreeView::item::hover{background-color:transparent;}"
                               "QTreeWidget{background:rgba(77,88,181,0.9);}"
                               "QTreeWidget::item::selected{background-color:rgba(0,0,0,0.1);};");
//    treeWidgets->setStyleSheet(QString("background:%1;").arg("rgb(77,88,181)"));
    treeWidgets->setCursor(QCursor(Qt::PointingHandCursor));
    treeWidgets->setAnimated(true);
    treeWidgets->setIconSize(QSize(28,30));


    for (int i = 0; i < treeWidgets->topLevelItemCount(); i++) {
        QTreeWidgetItem *topItem = treeWidgets->topLevelItem(i);
        topItem->setTextAlignment(0, Qt::AlignCenter);
        topItem->setSizeHint(0, QSize(100, 120));
        topItem->setTextColor(0, QColor(Qt::white));
        topItem->setFont(0, QFont("楷体", 14, QFont::Bold));
        for (int j = 0; j < topItem->childCount(); j++) {
            topItem->child(j)->setSizeHint(0, QSize(100, 50));
        }
    }
    /**处理医生和普通用户的界面差异**/
    for (int i = 0; i < widgetList.count(); ++i) {
        if(widgetList.value(i)== nullptr)
        {
            itemList.value(i)->setTextColor(0,QColor("gray"));
            itemList.value(i)->setToolTip(0,"没有权限");
            itemList.value(i)->setFlags(itemList.value(i)->flags() & ~Qt::ItemFlag::ItemIsSelectable);//设置不能被选择 (~位取反)
        }
    }

}

void MainWindow::initBindingEvent() {
    QObject::connect(treeWidgets,&QTreeWidget::itemClicked,this, &MainWindow::onTreeItemClicked);
    QObject::connect(lb_refresh,&MySwitch_Icon::mouseOver,this,&MainWindow::refreshBtn);
    QObject::connect(lb_refresh,&MySwitch_Icon::mouseOff,this,&MainWindow::refreshBtn_off);
    QObject::connect(lb_refresh,&MySwitch_Icon::clicked,this,&MainWindow::refreshUIData);
}

void MainWindow::refreshBtn() {
    lb_refresh->move(lb_refresh->x()-30,0);
}

void MainWindow::refreshUIData() {
    cout<<"准备刷新UI数据"<<endl;
    QTreeWidgetItem *pItem = treeWidgets->currentItem();
    int currentIndex = treeWidgets->indexOfTopLevelItem(pItem);
    cout<<"当前点击的是"<<currentIndex;
    QWidget *pWidget = widgetList.value(currentIndex);
    switch (currentIndex+1) {
        case 1:{
            Panel_1 *pPanel1 = dynamic_cast<Panel_1 *>(pWidget);
            pPanel1->refreshData();
            break;
        }
        case 0:
        case 2:
        { int i = treeWidgets->topLevelItem(1)->indexOfChild(pItem);
            Panel_2 *pPanel2 = dynamic_cast<Panel_2 *>(pWidget);
            pPanel2->refreshUI(i+1);
            break;
        }
        case 3:{
            Panel_3 *pPanel3 = dynamic_cast<Panel_3 *>(pWidget);
            pPanel3->getReport()->refreshUIData();
            break;
        }
        case 4:{
            Panel_4 *pPanel4 = dynamic_cast<Panel_4 *>(pWidget);
            pPanel4->refreshUIData();
            break;
        }
        case 5:{
            break;
        }
        case 6:{
            Panel_6* panel6=dynamic_cast<Panel_6*>(pWidget);
            panel6->refreshUIData();
            break;

        }
    }
}

void MainWindow::refreshBtn_off() {
    lb_refresh->move(lb_refresh->x()+30,0);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    Application::clear_and_exit();

}
/*****左侧QListWidget被点击触发事件*****/
void MainWindow::onTreeItemClicked() {
    QTreeWidgetItem* pItem=treeWidgets->currentItem();

    /*******判断是否是顶层子项..医疗、生活物资.. 三个子子项*******/
    Panel_2 *panel2_pontiner = dynamic_cast<Panel_2 *>(widgetList.value(1));

    int index_in_Item2;
    if((index_in_Item2=treeWidgets->topLevelItem(1)->indexOfChild(pItem))!=-1){
        MainWindow *pWindow = Application::getContentWindow();
        pWindow->windows_layout->setCurrentIndex(1);
        QStringList list = panel2_pontiner->getAllData();
        QStringList newList;
        switch (index_in_Item2) {
            case 0:{
                for (const auto &itemRow : list){
                     QStringList item = itemRow.split('=');
                     if(item.value(2).compare("食品物资")==0){
                         newList.append(itemRow);
                     }
                }
                panel2_pontiner->setTableData(newList);
                break;}
            case 1:{
                for (const auto &itemRow : list){
                    QStringList item = itemRow.split('=');
                    if(item.value(2).compare("生活物资")==0){
                        newList.append(itemRow);
                    }
                }
                panel2_pontiner->setTableData(newList);
                break;}
            case 2:{
                for (const auto &itemRow : list){
                    QStringList item = itemRow.split('=');
                    if(item.value(2).compare("医疗物资")==0){
                        newList.append(itemRow);
                    }
                }
                panel2_pontiner->setTableData(newList);
                break;}

        }

        return ;
    }
    /***判断是否是顶层，判断window是否是空，空->不执行***/
    if(widgetList.value(treeWidgets->indexOfTopLevelItem(pItem))== nullptr){
        onNotEnabledItemClicked();//弹出提示框
        return;
    }

    /***到此表明，是点击的顶层节点，且权限足够（对应的窗体不为空）*** ——>切换Item图标****/
    int index_in_topItems;
    if((index_in_topItems=(treeWidgets->indexOfTopLevelItem(pItem))) != -1){
        int index=iconlist.value(index_in_topItems).indexOf('_');   //i为
        QString str=iconlist.value(index_in_topItems).mid(index + 1); //
        if(str.compare("unselected.png")==0){
            /***如果是选中,先将所有的图标置为未选中***/
            for(int i=0;i<treeWidgets->topLevelItemCount();i++){
                QTreeWidgetItem *p = treeWidgets->topLevelItem(i);
                int j = treeWidgets->indexOfTopLevelItem(p);
                int index=iconlist.value(j).indexOf('_');
                iconlist.replace(i,iconlist.value(i).replace(index+1,20,"unselected.png"));
                p->setIcon(0,QIcon(iconlist.value(i)));
            }
          iconlist.replace(index_in_topItems, iconlist.value(index_in_topItems).replace(index + 1, 20, "selected.png"));
            pItem->setIcon(0,QIcon(iconlist.value(index_in_topItems)));
        } else if(str.compare("selected.png")==0){
            iconlist.replace(index_in_topItems, iconlist.value(index_in_topItems).replace(index + 1, 20, "unselected.png"));
            pItem->setIcon(0,QIcon(iconlist.value(index_in_topItems)));
        }

    }

    /*****展开下一层节点*****/
    int index=itemList.indexOf(pItem);
    windows_layout->setCurrentWidget(widgetList.value(index));
    if(index==1){
        panel2_pontiner->setTableData(currentUser->getSupply_Information());
    }
    if(pItem->isExpanded()){
        treeWidgets->collapseItem(pItem);
    }else{
        treeWidgets->expandItem(treeWidgets->currentItem());

    }

}

QStackedLayout *MainWindow::getWindowsLayout() {
    return windows_layout;
}

void MainWindow::onNotEnabledItemClicked() {
    /******ClientWindow作为子类会重写该方法，(虚函数)*****/
    /****弹出对话框******/
}

void MainWindow::showTipsWord(QString tip,int duration) {
    lb_tip->setText(tip);
    lb_tip->setHidden(false);

    QTime dieTime = QTime::currentTime().addMSecs(duration);
    while( QTime::currentTime() < dieTime ){
        //该句表示，线程可在等待期间处理其他事务
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    lb_tip->setHidden(true);
}

MainWindow::~MainWindow() {
    qDeleteAll(widgetList); //释放容器中的指针
    widgetList.clear();
    qDeleteAll(itemList);
    itemList.clear();

    delete windows_layout;
    delete treeWidgets;
    delete hbox_outest;     //应该是先删除子控件，在删除父控件
    delete centerQWidget;
    delete lb_tip;


    std::cout<<"MainWindow析构函数执行"<<std::endl;
    std::cout<<"容器已释放"<<std::endl;
    std::cout<<"容器已清空"<<std::endl;

}

void MainWindow::endUI() {
    treeWidgets->itemClicked(treeWidgets->topLevelItem(0),0);
}

QTreeWidget *MainWindow::getTreeWidget() {
    return treeWidgets;
}
