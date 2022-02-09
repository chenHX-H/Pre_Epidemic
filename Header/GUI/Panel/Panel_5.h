//
// Created by chenhonxinh on 2021/12/17.
//

#ifndef PRE_EPIDEMIC_PANEL_5_H
#define PRE_EPIDEMIC_PANEL_5_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
class Panel_5: public QWidget{
public:
    Panel_5();
    ~Panel_5();

protected:
    class MyPieChart:public QtCharts::QChartView{
    public:
        MyPieChart();
        ~MyPieChart();
        QtCharts::QChart* pieChart;
        QtCharts::QPieSeries* pieSeries;

    protected:
        void initUI();
        void initLayout();
        void initStyle();
    };
    void initUI();
    void initLayout();
    void initStyle();
    void test();
private:
    QScrollArea* scrollArea;
    QVBoxLayout* vbox;
    MyPieChart* myPieChart;
    QLabel* lb=new QLabel("sfdf",this);


};


#endif //PRE_EPIDEMIC_PANEL_5_H
