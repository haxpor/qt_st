#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QPointF>

// this is a way to forward class inside a namespace
namespace QtCharts
{
    class QLineSeries;
    class QChart;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // only latest 200 sample will be taken into account, the old ones will get re
    static const int SAMPLE_COUNT = 200;
    // sample rate in millisecond
    static const int SAMPLE_RATE = 17; // with ~17, aim to be nearly 60 fps

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtCharts::QLineSeries *lineSeries;
    QtCharts::QChart *chart;

    // current number of streaming in data
    QQueue<QPointF> liveDataBuffer;
    // cached of previous live data, it's here to be a solution to increase performance in accessing
    // the last element in buffer (as we use QQueue, we cannot use QLinkedList as QLineSeries::replace()
    // doesn't support it).
    QPointF prevLiveData;

    /**
     * @brief streamInNewLineData
     * Stream in new line data by appending new data into the QLineSeries.
     * This simulates the live data plotted in line chart.
     */
    void streamInNewLineData();
};

#endif // MAINWINDOW_H
