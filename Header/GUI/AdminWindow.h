//
// Created by chenhonxinh on 2021/12/15.
//

#ifndef PRE_EPIDEMIC_ADMINWINDOW_H
#define PRE_EPIDEMIC_ADMINWINDOW_H

#include "ClientWindow.h"
#include "Header/GUI/Panel/Panel_5.h"
#include "Header/Role/Admin.h"
class AdminWindow: public ClientWindow{
public:

   AdminWindow(Admin*);

    void start() override;

protected:

private:
    void initDifference();

};
#endif //PRE_EPIDEMIC_ADMINWINDOW_H
