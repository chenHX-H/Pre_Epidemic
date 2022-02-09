//
// Created by chenhonxinh on 2021/12/16.
//

#ifndef PRE_EPIDEMIC_PANEL_4_H
#define PRE_EPIDEMIC_PANEL_4_H


#include <QLabel>
#include <QMainWindow>
#include <QDockWidget>
#include <QTableWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QHeaderView>
#include "Header/Data/BackLog.h"
#include <QPropertyAnimation>
#include <QFormLayout>
#include <QTextEdit>

class Panel_4: public QMainWindow {
public:
    Panel_4();
    ~Panel_4();
    void refreshUIData();
protected:
    void initUI();
    void initLayout();
    void initStyle();
    void bindingEvent();
    QStringList getData();
    class Tab_Frame:public QFrame{
    public:
         Tab_Frame(Panel_4*);
        ~Tab_Frame();
        void setTableData(QStringList data);
         QStringList &getDataPrivate() ;
        void setDataPrivate(const QStringList &dataPrivate);
        QTableWidget* getTable();
    protected:
        void initUI();

    private:
        Panel_4* parent_Panel4;
        QStringList dataPrivate;
        QHBoxLayout layout;
        QTableWidget* table;
        void onClicked(QTableWidgetItem*);
    };
    class RightMsg: public QFrame{
    public:
        RightMsg();
        ~RightMsg();
        QFormLayout* msgForm;
        QLabel* lb_name;
        QLabel* lb_age;
        QLabel* lb_id;
        QLabel* lb_sex;
        /****固定控件****/
        QPushButton* btnLien;
        QLabel* lb_fenge;
        QTextEdit* textIllness;
        void setMsg(BackLog);
    protected:
        void initStyle();
    private:
        void onDoubleClick();

    };
    class RightBottomLayout: public QFormLayout{
    public:
        RightBottomLayout();
        ~RightBottomLayout();
        QLabel* lb_NADLastTime;
        QLabel* lb_NADCount;
        QLabel* inoculate_name;
        QLabel* inoculate_lastTime;
        QLabel* inoculate_count;
        void setMsg(BackLog);

    };
    class BottomLayout:public QHBoxLayout{
    public:
    BottomLayout(Panel_4*);
    ~BottomLayout();
    Panel_4* parent_pointer;
    QPushButton* btn_vaccinate;
    QPushButton* btn_NAD;//核酸
    QPushButton* btn_cure;
    QPushButton* btn_InHospital;
    void initStyle();
    void bindingEvent();
        /**响应函数***/
        void onBtn_vaccinate_clicked();
        void onBtn_NAD_clicked();

    };
    class DockWidget_My:public QDockWidget{
    public:
        DockWidget_My(QString,Panel_4*);
        Panel_4* parent_pointer;
    protected:
        void closeEvent(QCloseEvent *event) override;
    };
private:

    QStringList dataList;
    DockWidget_My* dockRightWidget;
    DockWidget_My* dockRightWidget_second;
    DockWidget_My* dockWidgetBottom;
    QFrame* frameRight;
    QFrame* frameRight_second;
    QFrame* frameBottom;
    QVBoxLayout* vbox_rightFrame;
    RightBottomLayout* rightBottomLayout;
    BottomLayout* bottomLayout;
    QTabWidget* tabWidget;
    QList<Tab_Frame*> listTab;
    RightMsg* rightMsg;


    void onTabClicked(int i);
    void showAllMsg(BackLog);
    BackLog transformToBackLog(QString item);
    void closeALL();
    void setALLTabData();



};


#endif //PRE_EPIDEMIC_PANEL_4_H
