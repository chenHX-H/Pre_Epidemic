
#include "Header/GUI/Panel/Panel_5.h"

#include "Header/Application.h"
Panel_5::Panel_5() {
    scrollArea=new QScrollArea;
    vbox=new QVBoxLayout;
    myPieChart= new MyPieChart;
    initUI();
}

void Panel_5::initUI() {
    initLayout();
    initStyle();
}

void Panel_5::initLayout() {
    scrollArea->setParent(this);
    scrollArea->setLayout(vbox);

    vbox->addWidget(myPieChart);
    vbox->addStretch(3);

}

void Panel_5::initStyle() {

    scrollArea->setFixedSize(680,700);

}

Panel_5::~Panel_5() {
    cout<<"Panel_5析构正在执行"<<endl;
    delete myPieChart;
    delete vbox;
    delete scrollArea;
    cout<<"Panel_%析构执行完毕"<<endl;

}
/*****MyPieChart*****/
Panel_5::MyPieChart::MyPieChart() {
    pieChart=new QtCharts::QChart;
    pieSeries=new QtCharts::QPieSeries;
    Panel_5::MyPieChart::initUI();
}

void Panel_5::MyPieChart::initUI() {
    pieSeries->append("医疗物资:50%",5);
    pieSeries->append("生活物资:20%",2);
    pieSeries->append("食品物资:30%",3);

    pieSeries->setLabelsVisible(true);
    pieSeries->setUseOpenGL(true);
    Panel_5::MyPieChart::initLayout();
    Panel_5::MyPieChart::initStyle();
}

void Panel_5::MyPieChart::initLayout() {
    this->setChart(pieChart);
    pieChart->addSeries(pieSeries);
}

void Panel_5::MyPieChart::initStyle() {
    this->setFixedSize(650,600);
    pieSeries->slices().at(0)->setColor(QColor(13, 128, 217)); //设置颜色
    pieSeries->slices().at(0)->setLabelColor(QColor(13, 128, 217));
    pieSeries->slices().at(1)->setColor(QColor(69, 13, 217)); //设置颜色
    pieSeries->slices().at(1)->setLabelColor(QColor(69, 13, 217));
    pieSeries->slices().at(2)->setColor(QColor(13, 217, 152)); //设置颜色
    pieSeries->slices().at(2)->setLabelColor(QColor(13, 217, 152));
    pieChart->legend()->setMinimumHeight(50);
    pieChart->legend()->setMaximumHeight(150);
    pieChart->legend()->setMinimumWidth(100);
    pieChart->legend()->setMaximumWidth(200);
    pieChart->legend()->setVisible(true);
    pieChart->legend()->setBackgroundVisible(true);
    pieChart->legend()->setAlignment(Qt::AlignRight);//底部对齐***
    pieChart->setTheme(QtCharts::QChart::ChartThemeLight);//设置白色主题
    pieChart->setDropShadowEnabled(true);//背景阴影
    pieChart->setTitleBrush(QBrush(QColor(0, 0, 255))); //设置标题Brush
    pieChart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    pieChart->setTitle("物资存量图");
    this->setRenderHint(QPainter::Antialiasing);
    pieChart->legend()->setAutoFillBackground(true);//设置背景自动填充
}
Panel_5::MyPieChart::~MyPieChart() {
    cout<<"MyPieChart析构正在执行"<<endl;
    delete pieChart;
    delete pieSeries;
    cout<<"MyPieChart析构执行完毕"<<endl;
}