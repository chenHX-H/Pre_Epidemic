//
// Created by chenhonxinh on 2021/12/9.
//

#ifndef PRE_EPIDEMIC_APPLICATION_H
#define PRE_EPIDEMIC_APPLICATION_H
#include "Header/GUI/LoginWindow.h"
#include "Header/Role/User.h"
#include <QMainWindow>
#include <QFontDatabase>
#include "Header/Data/Operate_Database.h"
#include "Header/GUI/AdminWindow.h"
#include "Header/GUI/ClientWindow.h"
#include "Header/GUI/MainWindow.h"
class Application{

public:
    static QFont *getIconFont();
    static QIcon *getFaviconIcon();
    static Operate_Database* getDatabase_Connection();
    static User *getCurrentUser();
    static bool start();
    static void stepMainWindow_Admin();
    static void stepMainWindow_User(UserData* currentUser);
    static void clear_and_exit();
    static MainWindow* getContentWindow();


private:
    static User* currentUser;
    static LoginWindow* loginWindow;
    static MainWindow* contentWindow;
    static QFont* iconFont;
    static Operate_Database* db;
    static QIcon* favicon;
    static void initData();
    static void initIconFont();



};


#endif //PRE_EPIDEMIC_APPLICATION_H
