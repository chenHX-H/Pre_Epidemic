//
// Created by chenhonxinh on 2021/12/14.
//

#ifndef PRE_EPIDEMIC_CLIENTWINDOW_H
#define PRE_EPIDEMIC_CLIENTWINDOW_H


#include "MainWindow.h"
#include "Header/GUI/Panel/Panel_1.h"
#include "Header/GUI/Panel/Panel_2.h"
#include "Header/GUI/Panel/Panel_3.h"
#include "Header/GUI/Panel/Panel_4.h"
#include "Header/GUI/Panel/Panel_5.h"
#include "Header/Data/UserData.h"
#include "Header/Role/User.h"
#include <QMessageBox>
#include <QFileDialog>
class ClientWindow: public MainWindow{
public:
    ClientWindow(User*);

protected:

    /**自定义提示对话框**/
    class ProvideMaterials:public QFrame{
    public:
        ProvideMaterials(ClientWindow*);
        ~ProvideMaterials();
    protected:
        ClientWindow* parent_pointer;
        QGridLayout* grid;
        QLabel* lb_title;
        QTextEdit* textEdit;
        QPushButton* btnConfirm;
        QPushButton* btnCancel;
        MySwitch_Icon* lb_img;
        void initStyle();
        void bidingEvent();
    private:
        void onConfirm();
        void onCancel();
        void selectFile();
        QString currenPath;
    };


    class EnquiryDialog:public QDialog{
    public:
        ClientWindow* parent_ponter;
        EnquiryDialog(ClientWindow*);
        ~EnquiryDialog();
        void onConfirm();
        void onRegister();
        QGridLayout* grid;
        QLabel* tip_img;
        QLabel* tipTexts;
        QPushButton* btnConfirm;
        QPushButton* btnRegister;
    };

    void onNotEnabledItemClicked() override;

public:
    void start() override;

private:
    User* currentUser;
    EnquiryDialog* enquiryDialog;
    ProvideMaterials* provideMaterials;

    void init_noDoctor_UI(QTreeWidgetItem*,QTreeWidgetItem*);
    void init_Doctor_UI(QTreeWidgetItem*,QTreeWidgetItem*);
    void initDifference();
    void initRoleDifference();
};


#endif //PRE_EPIDEMIC_CLIENTWINDOW_H
