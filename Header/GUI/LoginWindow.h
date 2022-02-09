//
// Created by chenhonxinh on 2021/12/13.
//

#ifndef PRE_EPIDEMIC_LOGINWINDOW_H
#define PRE_EPIDEMIC_LOGINWINDOW_H
#include <QWidget>
#include  <QIcon>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "Header/Data/UserData.h"
#include "Header/GUI/MySwitchButton.h"
#include <QCoreApplication>
#include "Header/GUI/MySwitch_Icon.h"
#include <QDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
class LoginWindow: public QWidget{
public:

    void start();
    ~LoginWindow();


protected:
    class RegisterDialog:public QDialog{
    public:
        RegisterDialog(LoginWindow*);
        ~RegisterDialog();
        QFormLayout* registerForm;
    protected:
        void initLayout();
        void initStyle();
    private:
        LoginWindow* parent_Pointer;
        QLineEdit*      username;
        QLineEdit*      password;
        QLineEdit*      passwordRepeat;
        QLineEdit*      name_ZH;
        QComboBox*      sex;
        QSpinBox*       age;
        QLineEdit*      idNumber;
        QLineEdit*      job;
        QPushButton*    btnSubmit;
        void onClicked();
    };
    QVBoxLayout vbox;       //最外层布局
    QLineEdit username_edit;
    QLineEdit password_edit;
    QHBoxLayout hbox;       //最下层：登录、注册..
    QRegExpValidator *validator ;
    MySwitch_Icon *forgetPwd_lb;
    MySwitch_Icon *register_lb;
    QLabel *logo;
    QPushButton *loginBtn;
    MySwitchButton* toggle;
    QLabel* toggle_side;
    QLabel* tip_lb;
    RegisterDialog* registerDialog;


private:

    void initUI();
    void initLayout();
    void initWidget();
    void initBindingEvent();
    void initStyle();
    bool login();
    void show_and_hidden(QString);
    void registerUser();



};


#endif //PRE_EPIDEMIC_LOGINWINDOW_H
