//
// Created by chenhonxinh on 2021/12/16.
//

#include "Header/GUI/Panel/Panel_2.h"
#include "Header/Application.h"
Panel_2* Panel_2::Right::parent_pointer= nullptr;
Panel_2::Panel_2() {
    initUI();
    initLayout();
    initStyle();
    allData=Application::getCurrentUser()->getSupply_Information();
    setTableData(allData);

}

void Panel_2::initUI() {
    table=new QTableWidget(0,4,this);
    Panel_2::Right::parent_pointer=this;
    

    QStringList list;
    list<<"物资名"<<"总数"<<"类属"<<"操作";

    table->setHorizontalHeaderLabels(list);
    table->verticalHeader()->setVisible(false);





}

void Panel_2::initStyle(){
    table->setFixedWidth(table->parentWidget()->width()+50);
    table->setFixedHeight(table->parentWidget()->height()+150);
    table->setColumnWidth(0,250);
    table->setColumnWidth(1,100);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers );
    QHeaderView *pView = table->horizontalHeader();
    pView->setFont(QFont("黑体",14));
    pView->setDefaultAlignment(Qt::AlignCenter);
    pView->setStyleSheet("QHeaderView::section{background:rgba(0,0,0,0.1);color: black;}");

    pView->setStretchLastSection(true);//最后一项占完


}

void Panel_2::initLayout() {

}

void Panel_2::bindingEvent() {

}

void Panel_2::setTableData(QStringList data,int flag) {
    cout<<"setTableData执行"<<endl;
//    flag==1表明当前选中的是3个类属子项，使其保持状态
    if(flag!=0){
        Application::getContentWindow()->onTreeItemClicked();
        return;
    }

    table->clearContents();
    table->setRowCount(0);
    
    for(int i=0;i<data.count();i++){
        const QStringList &itemRow = data.value(i).split('=');
        table->setRowCount(table->rowCount()+1);
        for (int j = 0; j < itemRow.count() - 1; ++j) {
            table->setItem(i,j,new QTableWidgetItem(itemRow.value(j)));
        }
        table->setCellWidget(i,3,new Right);

        /***每一次刷新数据，每一行执行 都要进行按钮权限管理***/
        Right *pWidget = dynamic_cast<Right *>(table->cellWidget(i, 3));

        if(Application::getCurrentUser()->isAdmin1()){
            pWidget->getIcon1()->setEnabled(true);
            pWidget->getIcon2()->setEnabled(true);
        }else if(Application::getCurrentUser()->isDoctor1()){
            pWidget->getIcon1()->setEnabled(true);
            pWidget->getIcon2()->setEnabled(false);
        }else{
            if(itemRow.value(3).toInt()){
                pWidget->getIcon1()->setEnabled(false);
                pWidget->getIcon2()->setEnabled(false);
            }else{
                pWidget->getIcon1()->setEnabled(true);
                pWidget->getIcon2()->setEnabled(false);
            }

        }
    }
    /****表格设置不可选中****/
    for(int i=0;i<table->rowCount();i++){
        table->item(i,0)->setFont(QFont("黑体",12));
        table->setRowHeight(i,50);
        cout<<table->columnCount();
        for (int j = 0; j <table->columnCount()-1 ;j++) {
            QTableWidgetItem *pItem = table->item(i, j);
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
        }
    }
    
 
}




const QStringList &Panel_2::getAllData() const {
    return allData;
}

void Panel_2::setAllData(const QStringList &allData) {
    Panel_2::allData = allData;
}

void Panel_2::refreshUI(int flag) {
    switch (flag) {
        case 0:{
            allData=Application::getCurrentUser()->getSupply_Information();
            setTableData(allData,0);
            break;
        }
        case 1:
        case 2:
        case 3:{
            //当使用子项时，数据库查询报错，父项可以，真是te me 的莫名其妙！！！
            QTreeWidget *tree = Application::getContentWindow()->getTreeWidget();
            tree->collapseItem(tree->topLevelItem(1));
            tree->setCurrentItem(tree->topLevelItem(1));
            Application::getContentWindow()->onTreeItemClicked();
            break;
        }
    }
}
/*****2021年12月29日 00:36:30 -debug：分析一下步骤，尝试是否是2次点击的问题****/
Panel_2::~Panel_2() {
    delete table;
    cout<<"Panel_2析构执行"<<endl;
}
/******以下为Right********/
Panel_2::Right::Right() {
    this->setLayout(&hbox);
    icon1=new MySwitch_Icon;
    icon2=new MySwitch_Icon;
    icon1->setText("申请");
    icon2->setText("补充");
    initLayout();
    initStyle();
    bindingEvent();




}

void Panel_2::Right::initLayout() {
    hbox.addWidget(icon1);
    hbox.addWidget(icon2);

}

void Panel_2::Right::initStyle() {
    ///按钮设置为不可点击，Client和Admin Window 类将处理角色之间的差异部分
    icon1->setEnabled(false);
    icon2->setEnabled(false);

    icon2->setFont(*Application::getIconFont());
    icon2->setText(QChar(0xe60e)+QString("补充"));
    icon1->setFont(QFont("宋体",16));
    icon2->setAlignment(Qt::AlignVCenter);
    icon1->setCursor(QCursor(Qt::PointingHandCursor));
    icon2->setCursor(QCursor(Qt::PointingHandCursor));
    icon1->setStyleSheet("QLabel:hover{color:rgba(0,0,0,0.5);}");
    icon2->setStyleSheet("QLabel:hover{color:rgba(23,171,227,0.9);}");

}

void Panel_2::Right::bindingEvent()  {
    icon1->setFlag(1);
    icon2->setFlag(2);
    QObject::connect(icon1,&MySwitch_Icon::clicked,this,&Panel_2::Right::onClickedLabel);
    QObject::connect(icon2,&MySwitch_Icon::clicked,this,&Panel_2::Right::onClickedLabel);

}

void Panel_2::Right::onClickedLabel(int i) {
    int ix = this->frameGeometry().x();
    int iy = this->frameGeometry().y();
    const QModelIndex &index = parent_pointer->table->indexAt(QPoint(ix, iy));
    const QString &nameText = parent_pointer->table->item(index.row(), 0)->text();
    User *pUser = Application::getCurrentUser();
    switch (i) {
        case 1:{
            bool ok= false;
            QString value = QInputDialog::getText(this, "数量:", QString("输入需要多少%1:").arg(nameText),QLineEdit::Normal,"",&ok);
            if(ok){
                if(value.compare("")==0){
                    return;
                }
                Application::getContentWindow()->showTipsWord("已申请:"+value,2000);
                pUser->apply_for_supply(nameText, value.toInt());
                parent_pointer->setAllData(pUser->getSupply_Information());
                parent_pointer->setTableData(parent_pointer->getAllData(),1);
            }
            break;

        }
        case 2:{
            bool ok= false;
            int anInt = QInputDialog::getInt(this, "数量", QString("输入补充多少%1:").arg(nameText),1,0,10000,1,&ok);
            if(ok){
                if(pUser->isAdmin1()){
                Admin *pAdmin = dynamic_cast<Admin *>(pUser);
                const QString &kind = parent_pointer->table->item(index.row(), 2)->text();
                Materials materials(nameText.toStdString(),anInt);
                    bool b = pAdmin->addMaterial(materials);
                    if(b){
                        parent_pointer->setAllData(pUser->getSupply_Information());

                        parent_pointer->setTableData(parent_pointer->getAllData(),1);
                    }
                    Application::getContentWindow()->showTipsWord(QString("成功补充%1个%2").arg(anInt).arg(nameText),2500);
                }else{
                Application::getContentWindow()->showTipsWord(QString("权限不足，添加失败!"));

            }
            }
            break;
        }
    }
}


MySwitch_Icon *Panel_2::Right::getIcon1() const {
    return icon1;
}

MySwitch_Icon *Panel_2::Right::getIcon2() const {
    return icon2;
}
Panel_2::Right::~Right() {
//    cout<<"Right析构执行"<<endl;
    delete icon1;
    delete icon2;
}




