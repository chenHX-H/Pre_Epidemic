cmake_minimum_required(VERSION 3.21)
project(Pre_Epidemic)
set(CMAKE_CXX_STANDARD 14)
#自动生成
set(CMAKE_EXE_LINKER_FLAGS "-static")#预防exe不能运行bug


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH F:/C++/QT/5.12.2/mingw73_64) #这里需要填入自己安装的路径


find_package(Qt5Widgets)
find_package( Qt5Core)
find_package( Qt5Gui)
find_package(Qt5sql)
find_package(Qt5Charts)
set(UI_FILES)

set(RC_FILES)

set(QRC_FILES)

set(SOURCE_FILES main.cpp
        Sources/Data/Materials.cpp
        Sources/Application.cpp
        Sources/GUI/LoginWindow.cpp
        Sources/Data/UserData.cpp
        Sources/Role/User.cpp
        Sources/Role/Admin.cpp
        Sources/Role/Doctor.cpp

        Sources/GUI/MySwitchButton.cpp
        Sources/GUI/AdminWindow.cpp
        Sources/GUI/MainWindow.cpp
        Sources/GUI/ClientWindow.cpp
        )

add_executable(Pre_Epidemic main.cpp
        ${RC_FILES}${SOURCE_FILES}${UI_FILES}${QRC_FILES}
        Sources/GUI/Panel/Panel_1.cpp Header/GUI/Panel/Panel_1.h
        Sources/GUI/Panel/Panel_2.cpp Header/GUI/Panel/Panel_2.h
        Sources/GUI/Panel/Panel_3.cpp Header/GUI/Panel/Panel_3.h
        Sources/GUI/Panel/Panel_4.cpp Header/GUI/Panel/Panel_4.h
        Sources/Data/Operate_Database.cpp
        Header/Data/Operate_Database.h
        Sources/GUI/Panel/Panel_5.cpp Header/GUI/Panel/Panel_5.h
        Header/GUI/MySwitch_Icon.h Header/GUI/MyLabelOnly_DoubleClicked.h
        Sources/GUI/prevent/Appointment.cpp Header/GUI/prevent/Appointment.h
        Sources/GUI/prevent/Pre_Base.cpp Header/GUI/prevent/Pre_Base.h
        Sources/GUI/prevent/Report.cpp Header/GUI/prevent/Report.h
        Sources/GUI/prevent/Clarify.cpp Header/GUI/prevent/Clarify.h
        Sources/Data/BackLog.cpp Header/Data/BackLog.h
        Header/GUI/TextEDit_DoubleClickable.h
        Header/Data/Pre_user.h
        Sources/GUI/Panel/Panel_6.cpp Header/GUI/Panel/Panel_6.h)

target_link_libraries(Pre_Epidemic Qt5::Widgets Qt5::Charts)


qt5_use_modules(Pre_Epidemic Core Widgets  Sql Charts )

