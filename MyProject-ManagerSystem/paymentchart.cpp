#include "paymentchart.h"
#include <QChart>
#include <QPieSeries>
#include<QDate>
#include<QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
#include "dbmanager.h"


PaymentChart::PaymentChart(QWidget *parent) : QChartView(parent)
{
    series = new QPieSeries();
    piechart = new QChart();
    piechart->addSeries(series);
    piechart->setTitle("支付方式分布");
    piechart->legend()->setVisible(true);
    piechart->legend()->setAlignment(Qt::AlignRight);


    //折线图实现
    lineSeries = new QLineSeries();
    lineChart = new QChart();
    lineChart->addSeries(lineSeries);
    lineChart->setTitle("支付金额趋势");
    lineChart->legend()->setVisible(true);
    lineChart->legend()->setAlignment(Qt::AlignRight);
}

void PaymentChart::updateChart()
{
    series->clear();

    DbManager db("E:\\database\\manage.db");
    if (!db.isOpen()) {
          qDebug() << "数据库打开失败";
        return;
    }

    QMap<QString, double> paymentMap;
    QList<QList<QVariant>> funds = db.getAllFunds();

    for (const auto &fund : funds) {
        QString paymentMode = fund[3].toString(); // paymentMode列
        double amount = fund[2].toDouble(); // money列
        paymentMap[paymentMode] += amount;
    }

    for (auto it = paymentMap.begin(); it != paymentMap.end(); ++it) {
        series->append(QString("%1 (%2元)").arg(it.key()).arg(it.value()), it.value());
    }

     setChart(piechart);
}

void PaymentChart::updateLineChart()
{
    lineSeries->clear();

    DbManager db("E:\\database\\manage.db");
    if (!db.isOpen()) {
        return;
    }

    QMap<QDate, double> dateAmountMap;
    QList<QList<QVariant>> funds = db.getAllFunds();

    for (const auto &fund : funds) {
        QDate payDate = QDate::fromString(fund[4].toString(), "yyyy-MM-dd"); // payDate列
        double amount = fund[2].toDouble(); // money列
            dateAmountMap[payDate] += amount;
    }

    QList<QDate> dates = dateAmountMap.keys();
    std::sort(dates.begin(), dates.end());

    //debug语句
      qDebug() << "共找到" << dates.size() << "个日期数据点";
    for (const auto &date : dates) {
          qDebug() << "日期:" << date.toString("yyyy-MM-dd") << "金额:" << dateAmountMap[date];
        lineSeries->append(QDateTime(date.startOfDay()).toMSecsSinceEpoch(), dateAmountMap[date]);
    }

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText("日期");
    axisX->setMin(QDateTime(QDate(2010, 1, 1), QTime(0, 0)));
    axisX->setMax(QDateTime(QDate(2026, 12, 31), QTime(0, 0)));

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 8000);
    axisY->setTickInterval(2000);
    axisY->setTitleText("金额(元)");


    lineChart->addAxis(axisX, Qt::AlignBottom);
    lineChart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    qDebug() << "X轴范围:" << axisX->min() << "-" << axisX->max();
    qDebug() << "Y轴范围:" << axisY->min() << "-" << axisY->max();
    qDebug() << "折线图数据点数量:" << lineSeries->count();

    setChart(lineChart);
}
