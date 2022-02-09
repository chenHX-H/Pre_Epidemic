//
// Created by chenhonxinh on 2021/12/13.
//

#include "Header/GUI/LoginWindow.h"
#include "Header/Application.h"


void LoginWindow::start() {
    initUI();
    show();
}
void LoginWindow::initUI() {
    setWindowIcon(QIcon(QPixmap("../favicon.ico")));
    setWindowTitle("疫情管理系统");
    setFixedSize(500,400);

    this->initWidget();
    this->initStyle();
    this->initLayout();
    this->initBindingEvent();
}

void LoginWindow::initLayout() {

    hbox.addWidget(forgetPwd_lb,0,Qt::AlignLeft);
    hbox.addWidget(register_lb,0,Qt::AlignRight);
    vbox.addWidget(toggle_side,0,Qt::AlignLeft);
    vbox.addStretch(1);
    vbox.addWidget(logo,0,Qt::AlignHCenter);
    vbox.addStretch(1);
    vbox.addWidget(&username_edit);
    vbox.addWidget(&password_edit);
    vbox.addWidget(loginBtn);
        vbox.setAlignment(Qt::AlignHCenter);
        vbox.setContentsMargins(50,0,50,5);
        vbox.addLayout(&hbox);
        vbox.addWidget(tip_lb,1);

    toggle->move(35,0);
    this->setLayout(&vbox);
}
void LoginWindow::initStyle() {
    tip_lb->setStyleSheet("QLabel{color:transparent;}");
    tip_lb->setText("账号或密码错误!");
    tip_lb->setFont(QFont("楷体",12,QFont::Bold));
    tip_lb->setAlignment(Qt::AlignHCenter);

    toggle_side->setStyleSheet("margin:8,0,0,0");
    username_edit.setStyleSheet("font-size:24px;font-family:'楷体'");
    password_edit.setStyleSheet("font-size:20px;font-family:'楷体'");


    logo->setStyleSheet("border:1px solid black");
    logo->setAlignment(Qt::AlignRight);

    loginBtn->setCursor(QCursor(Qt::PointingHandCursor));
    toggle->setCursor(QCursor(Qt::PointingHandCursor));
    forgetPwd_lb->setCursor(QCursor(Qt::PointingHandCursor));
    register_lb->setCursor(QCursor(Qt::PointingHandCursor));

    forgetPwd_lb->setStyleSheet("QLabel:hover{color:red;}");
    register_lb->setStyleSheet("QLabel:hover{color:red;}");
}
void LoginWindow::initWidget() {
    validator= new QRegExpValidator(QRegExp("^[0-9]*$"), this);
    forgetPwd_lb=new MySwitch_Icon("忘记密码");
    register_lb=new MySwitch_Icon("注册账号");
    logo=new QLabel();
    loginBtn=new QPushButton("登录");
    toggle=new MySwitchButton(this);
    toggle_side=new QLabel("(管理员登录)");
    tip_lb=new QLabel;

    registerDialog=new RegisterDialog(this);

    username_edit.setFixedSize(300,50);
    password_edit.setFixedSize(300,50);
    loginBtn->setFixedSize(295,45);
    logo->setFixedSize(100,100);

    username_edit.setPlaceholderText("  账号");
    password_edit.setPlaceholderText("  密码");
    logo->setPixmap(QPixmap("../Resources/logo.png").scaled(logo->width(),logo->height()));

    username_edit.setClearButtonEnabled(true);
//    username_edit.setValidator(validator);  //正则表达式设置纯数字
    password_edit.setClearButtonEnabled(true);
    password_edit.setEchoMode(QLineEdit::Password);





}

void LoginWindow::initBindingEvent() {
    QObject::connect(register_lb,&MySwitch_Icon::clicked,this,&LoginWindow::registerUser);
    QObject::connect(loginBtn,&QPushButton::clicked,this,&LoginWindow::login);
}

void LoginWindow::registerUser() {
    registerDialog->show();
}

bool LoginWindow::login() {
    if(Application::getDatabase_Connection()->getSqlQuery()== nullptr){
        cout<<"网络异常";
        this->show_and_hidden("网络异常!");
        return false;
    }
    string username_t=username_edit.text().toStdString();
    string password_t=password_edit.text().toStdString();


    if(toggle->isCurrentStateChecked()){
        cout<<"管理员登录中...";
        if(username_t.compare("chenhonxinh")==0 && password_t.compare("123456")==0){
            cout<<"管理员登录成功";
            Application::stepMainWindow_Admin();
        } else{
            cout<<"管理员登录失败";
        }
    } else{
        cout<<"用户登录中...";
        UserData *current= Application::getDatabase_Connection()->loginQuery(username_t.c_str(), password_t.c_str());
        if(current!=NULL){
            cout<<"当前用户已获取到:是否医生="<<current->isDoctor1();
            Application::stepMainWindow_User(current);
        }else
        {
            show_and_hidden("用户名或密码错误!");
        }
        delete current;
    }
}

void LoginWindow::show_and_hidden(QString msg= nullptr) {
    if(msg!= nullptr){
        tip_lb->setText(msg);
    }

    tip_lb->setStyleSheet(QString("QLabel{color:red;}"));
    /*****延时任务***/
    QTime dieTime = QTime::currentTime().addMSecs(3000);
    while( QTime::currentTime() < dieTime ){
        //该句表示，线程可在等待期间处理其他事务
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    }
    tip_lb->setStyleSheet(QString("QLabel{color:transparent;}"));
}

LoginWindow::~LoginWindow() noexcept {
    delete validator;
    delete forgetPwd_lb;
    delete register_lb;
    delete loginBtn;
    delete logo;
    delete tip_lb;
}

/*****RegisterDialog******/
LoginWindow::RegisterDialog::RegisterDialog(LoginWindow* loginWindow) {
    this->parent_Pointer=loginWindow;
    registerForm=new QFormLayout;
    username=new QLineEdit;
    password=new QLineEdit;
    passwordRepeat=new QLineEdit;
    name_ZH=new QLineEdit;
    sex=new QComboBox;
    age=new QSpinBox;
    job=new QLineEdit;
    btnSubmit=new QPushButton("注册");
    idNumber=new QLineEdit;

    LoginWindow::RegisterDialog::initLayout();
    LoginWindow::RegisterDialog::initStyle();
    QObject::connect(btnSubmit,&QPushButton::clicked,this,&LoginWindow::RegisterDialog::onClicked);

}

void LoginWindow::RegisterDialog::onClicked() {
    if(username->text().isEmpty()){
       QMessageBox::information(this,"错误","用户名不能为空");
        return;
    }
    if(password->text().isEmpty()){
        QMessageBox::information(this,"错误","密码不能为空");
        return;
    }
    if(password->text().compare(passwordRepeat->text())!=0){
        QMessageBox::information(this,"错误","两次密码不一致");

        return;
    }
    if(name_ZH->text().isEmpty()){
        QMessageBox::information(this,"错误","姓名不能为空空");
        return;
    }
    if(age->value()<16 or age->value()>100){
        QMessageBox::information(this,"错误","年龄不符合");
        return;
    }
    if(idNumber->text().isEmpty()){
        QMessageBox::information(this,"错误","身份证号码不能为空");
        return;
    } else if(idNumber->text().length()!=18){
        QMessageBox::information(this,"错误","身份证号码格式不对");
        return;
    }
    bool b=!(sex->currentIndex());
    UserData data;
    data.setAge(age->value());
    data.setNameZh(name_ZH->text());
    data.setIdNumber(idNumber->text());
    data.setSex(b);
    data.setUsername(username->text());
    data.setPassword(password->text());
    if(job->text().isEmpty()){
        data.setJob("未确认");
    }else{
        data.setJob(job->text());
    }
    Application::getDatabase_Connection()->addNewUser(data);
    this->close();
    parent_Pointer->show_and_hidden("注册成功!");
//    Application::getContentWindow()->showTipsWord("注册成功！",1500);
}

void LoginWindow::RegisterDialog::initLayout() {
    this->setLayout(registerForm);
    registerForm->addRow("用户名:", username);
    registerForm->addRow("密码:", password);
    registerForm->addRow("确认密码:",passwordRepeat);
    registerForm->addRow("姓名:",name_ZH);
    registerForm->addRow("性别:",sex);
    registerForm->addRow("年龄:",age);
    registerForm->addRow("身份证号:",idNumber);
    registerForm->addRow("工作:",job);
    registerForm->addRow(btnSubmit);
    job->setPlaceholderText("可选");
}

void LoginWindow::RegisterDialog::initStyle() {
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("用户注册");
    this->setStyleSheet("QLabel{font-size:30px;}"
                        "QSpinBox,QComboBox,QPushButton,QLineEdit{height:30px;font-size:25px;}");
    sex->addItems(QStringList()<<"男"<<"女");
    idNumber->setMaxLength(18);
    password->setEchoMode(QLineEdit::Password);
    passwordRepeat->setEchoMode(QLineEdit::Password);
    btnSubmit->setCursor(QCursor(Qt::PointingHandCursor));


}

LoginWindow::RegisterDialog::~RegisterDialog() {
    delete username;
    delete password;
    delete passwordRepeat;
    delete name_ZH;
    delete sex;
    delete age;
    delete job;
    delete idNumber;
    delete registerForm;

}
