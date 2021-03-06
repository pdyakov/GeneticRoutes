#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include "basesdialog.h"
#include "src/DataAccess/DataRepository.h"
#include "src/RouteManager/RouteManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_4_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_6_triggered();

    void on_pushButton_clicked();

private:
    QVector<Drone> *__drones;
    QVector<Target> *__targets;
    QVector<FlightBase> *__flightBases;
    QVector<Route> *__routes;
    bool drFlag;
    QPixmap *pixmap;

//    QStandardItemModel** __drones;
//    QStandardItemModel* __targets;

    Ui::MainWindow *ui;


    void addTarget(QStandardItemModel *targets, const QString &name, const float x, const float y);
    void addDrone(QStandardItemModel *drones, const QString &name, const float x, const float y);
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
