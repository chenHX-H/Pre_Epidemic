# 使用说明:
+ **本项目基于 Clion集成开发环境，使用C++语言 Qt框架开发而成；**
+ **本项目着重练习Qt，使用了大量Qt提供的基础库（如QList...)而非使用C++原生库**
+ **本项目是纯桌面应用程序项目，未使用后台服务器，数据方面，使用的是Qt提供的数据库**
+ **快速开始：**
    **找到 ./Sources/Data/Operate_Database.cpp文件，修改里面的数据库**








# 设计架构：
    main（启动Application类）
    ——>:
    Application(掌管全局,负责存储每个大窗口，以及窗口之间的交互)
    ——>:
    LoginWindow(负责,登录/注册..;并决定进入管理员界面、用户界面 其一):——>

    ### 管理员界面 和 用户界面 <--(继承于) MainWindow <---QMainWindow
    ###MainWindow设计架构:
        *
        *
        *

# 目录:
    Header:
        Data:数据库数据存储类（对应字段）
        GUI:负责GUI模块
            StakedLayout_Widgets
            xx1
            xx2
        Role:不同角色之间有不同的功能
    Sources:与Header目录保持结构一致
    Resources: 图片资源/字体资源.ttf(iconfont图标)
    CMakeLists.txt:Cmake配置文件
    favicon.ico:应用程序图标
    main:程序入口

# 通用函数和方法：
    对于GUI类，您将频繁的看见以下方法:
        start():一般为启动入口
        initUI():负责UI的初始化，主要用于调用其他UI模块;
        initLayout:设置布局
        initWidget():对控件进行赋值 ，大小、文字处理-->在此之后框架应该显示出来;
        initStyle():控件的具体样式，颜色，字体...
        initBidingEvent():绑定各控件的事件
 
## 图片和图标：iconfont+.png