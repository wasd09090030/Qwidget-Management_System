#ifndef PAYMENTCHART_H
#define PAYMENTCHART_H

#include <QChartView>
#include <QPieSeries>
#include <QLineSeries>


class PaymentChart : public QChartView
{
    Q_OBJECT

public:
    explicit PaymentChart(QWidget *parent = nullptr);
    void updateChart();
    void updateLineChart();

private:
    QPieSeries *series;
    QLineSeries *lineSeries;
    QChart *piechart;
    QChart *lineChart;
};

#endif // PAYMENTCHART_H
