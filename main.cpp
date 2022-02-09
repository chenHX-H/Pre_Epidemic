#include <iostream>
#include <QApplication>
#include "Header/Application.h"
#include <QTextCodec>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]){
    system("CHCP 65001");

    QApplication app(argc, argv);


    UserData* user=new UserData("1613007","123456");
    user->setNameZh("陈红鑫");
    user->setIsDoctor(false);

    Application::start();


//      Application::stepMainWindow_User(user);
//    Application::stepMainWindow_Admin();

    return app.exec();

}
