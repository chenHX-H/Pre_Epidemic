//
// Created by chenhonxinh on 2021/12/9.
//

#include "Header/Application.h"
#include "Header/Role/Admin.h"
#include "Header/Role/Doctor.h"
MainWindow* Application::contentWindow=nullptr;/***主窗口****/
LoginWindow* Application::loginWindow=nullptr;/**登录窗口**/
User* Application::currentUser=nullptr; /**当前用户**/
QFont* Application::iconFont=nullptr;   /**IconFont字体图标**/
Operate_Database* Application:: db= nullptr;/**数据库操作类**/
QIcon* Application::favicon= nullptr;/**程序图标**/
bool Application::start() {
     initData();
     loginWindow->start();

}
void Application::initData() {
    initIconFont();
    db=new Operate_Database;
    loginWindow=new LoginWindow;
    favicon=new QIcon(QPixmap("../favicon.ico"));
}
void Application::initIconFont() {
    QFontDatabase fontDb;
    if (!fontDb.families().contains("iconfont")) {
        int fontId = fontDb.addApplicationFont("../Resources/iconfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load iconfont.ttf error";
        }
    }
    if (fontDb.families().contains("iconfont")) {
        iconFont = new QFont("iconfont");
        iconFont->setHintingPreference(QFont::PreferNoHinting);
    }
}

QIcon *Application::getFaviconIcon() {
    return favicon;
}

void Application::stepMainWindow_User(UserData* currentUserData) {

    if(loginWindow!=nullptr){
        loginWindow->close();

    }
    currentUser=new User(*currentUserData);
    contentWindow=new ClientWindow(currentUser);

    dynamic_cast<MainWindow*>(contentWindow)->start();

}

void Application::stepMainWindow_Admin() {
    if(loginWindow!=nullptr){
        loginWindow->close();

    }
     UserData data = UserData("1613007", "123456");
    auto *pAdmin = new Admin(new User(data));
    pAdmin->setSex(true);
    pAdmin->setAge(19);
    pAdmin->setIdNumber("5002312002080633378");
    pAdmin->setNameZh("陈红鑫--管理员");
    currentUser=pAdmin;
    contentWindow=new AdminWindow(pAdmin);
    dynamic_cast<MainWindow*>(contentWindow)->start();

}

MainWindow* Application::getContentWindow() {
    return contentWindow;
}

QFont *Application::getIconFont() {
    return iconFont;
}

Operate_Database *Application::getDatabase_Connection() {
    return db;
}

User *Application::getCurrentUser() {
    return currentUser;
}

void Application::clear_and_exit() {
    delete loginWindow;
    delete contentWindow;
    delete iconFont;
    delete db;
    delete currentUser;



}
