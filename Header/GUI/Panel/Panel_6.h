//
// Created by chenhonxinh on 2021/12/28.
//

#ifndef PRE_EPIDEMIC_PANEL_6_H
#define PRE_EPIDEMIC_PANEL_6_H
#include <QTableWidget>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include "Header/GUI/MySwitch_Icon.h"
#include <QGraphicsDropShadowEffect>
#include <QSpinBox>
#include <QComboBox>
class Panel_6:public QWidget {
public:
    Panel_6();
    ~Panel_6();
    void refreshUIData();

protected:
    class Notice_Msg:public QDialog{
    public:
        Notice_Msg();
    protected:
        void initUI();
        void initLayout();
        void initStyle();
        void bindingEvent();

    private:
        QFormLayout form;
        QVBoxLayout vbox;
        QHBoxLayout hbox;
        QLabel      lb_title;
        QLabel      lb_content;
        QLineEdit   edit_title;
        QTextEdit   edit_content;
        QPushButton btn_confirm;
        QPushButton btn_cancel;
        void onConfirm_Clicked();
        void onCancel_Clicked();

    };
    class Add_Material:public QDialog{
    public:
        Add_Material();
        ~Add_Material();
        QFormLayout* form;
        QLineEdit* name;
        QSpinBox* count;
        QLineEdit* kind;
        QComboBox* is_regualte;
        QPushButton* btn_confirm;
        void onBtnClicked();
    };
    class ItemBxo:public QWidget{
    public:
        ItemBxo();
        ~ItemBxo();

        QVBoxLayout* vbox;
        QLabel* lb_title;
        MySwitch_Icon* lb_icon;
    private:
        void initStyle();
        void initLayout();
        void bindingEvent();
    };
    class RatifyDoctor:public QDialog{
    public:
        RatifyDoctor(Panel_6*);
        ~RatifyDoctor();
        QStringList getData();
        void refreshUIData();
        QTableWidget* getTable();
        class Btns:public QWidget{
        public:
            Btns(Panel_6*);
            ~Btns();
            Panel_6* parent_pointer;
            QHBoxLayout* hbox;
            MySwitch_Icon* lb_look;
            MySwitch_Icon* lb_agree;
            MySwitch_Icon* lb_refuse;
        private:
            void onClickedLable(int i);

        };
    protected:
        Panel_6* parent_pointer;
        QStringList data;
        QList<Btns*> listBtn;
        QVBoxLayout* vbox;
        QLabel* lb_title;
        QTableWidget* table;
        void initLayout();
        void initStyle();
    };
    class LookOverMsg:public QDialog{
    public:
        LookOverMsg(Panel_6*);
        ~LookOverMsg();

         void showDetail(QString,QPixmap);
        Panel_6* parent_pointer;
    protected:
        void initLayout();
        void initStyle();
    private:
        QFormLayout* form;
        QLabel* lb_content;
        QLabel* lb_img;

    };

    void initUI();
    void bindingEvent();
    RatifyDoctor* ratifyDocotor;

private:
    QGridLayout* gridLayout;
    Notice_Msg *noticeMsg;
    Add_Material* addMaterial;
    LookOverMsg* lookOverMsg;
    ItemBxo *pBxo;
    ItemBxo *pBxo1;
    ItemBxo *pBxo2;
    void sendNotice();
    void addMaterials();
    void stepRatify();
    void initLayout();
    void initStyle();

};


#endif //PRE_EPIDEMIC_PANEL_6_H
