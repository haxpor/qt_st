#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QPointF>
#include <QTimer>
#include <QRandomGenerator>

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // What we gonna do is that
    // we gonna render line chart from streaming input data by limiting the number of data to be taken into rendering of the chart itself
    // this lineSeries will be fed in real-time in timer function
    lineSeries = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->setMinimumSize(640, 320);
    chart->addSeries(lineSeries);
    chart->setTitle("Line Chart");

    // note: setting up axes is very important for being able to plot live data for a chart
    // set a-axis
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, SAMPLE_COUNT);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    // set y-axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 256);
    axisY->setTitleText("Value");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    // create QChartView so we don't have to create QGraphicsView scene ourselves
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);

    // seed random generator
    QRandomGenerator::global()->securelySeeded();

    // set up timer to call in interval
    // it's good to set the parent object to timer as well to get memory management for free at the time of MainWindow widget is closed
    QTimer *timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);

    // connect timer event function via lambda function
    // notice: no need to specify object as parameter inside the connect() function
    // notice 2: we captured *this* object
    connect(timer, &QTimer::timeout, [=]() {
        qDebug() << "Called from timer: streaming in a new line data";

        this->streamInNewLineData();
    });

    // set interval to be every 1 secs
    // this is for our live data to be fed into the line series
    timer->setInterval(SAMPLE_RATE);
    // start timer
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete lineSeries;  lineSeries = nullptr;
    delete chart;       chart = nullptr;
}

void MainWindow::streamInNewLineData()
{
    // if empty then
    if (liveDataBuffer.isEmpty())
    {
        for (int i=0; i<SAMPLE_COUNT; ++i)
        {
            int y = QRandomGenerator::global()->bounded(256);
            qDebug() << "y: " << y;
            liveDataBuffer.append(QPointF(i, y));

            // save the last element data point
            if (i == SAMPLE_COUNT - 1)
            {
                prevLiveData = QPointF(i, y);
            }
        }

        // replace data from previous frame
        lineSeries->replace(liveDataBuffer);
        // emit the signal to let QChartView catches up with rendering
        emit lineSeries->pointsReplaced();

        qDebug() << "Initialize live data buffer";
    }
    else
    {
        // random whether this frame it will have new data or not
        // if not then we will add the same value of the last data point we have currently in the
        // chart
        // 50-50 percent to go in either same value or different one
        bool genNewData = QRandomGenerator::global()->bounded(10) > 5;

        // stream a new line data point
        int y = prevLiveData.y();
        if (genNewData)
        {
            y = QRandomGenerator::global()->bounded(256);
            // update previous live data
            prevLiveData.ry() = y;
        }
        QPointF point(SAMPLE_COUNT-1, y);

        // remove the first element
        liveDataBuffer.dequeue();

        // iterate through each element to increment x-axis value as we shift left by 1
        // Qt container classes are compatible with for range based
        for (auto& e : liveDataBuffer)
        {
            --e.rx();   
        }

        // append a new data point
        liveDataBuffer.enqueue(point);
        
        // update line series
        lineSeries->replace(liveDataBuffer);
        emit lineSeries->pointsReplaced();
        qDebug() << "Streamed in a new line data";
    }
}
