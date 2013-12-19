#include <QMutableVectorIterator>
#include <QPainter>
#include <QPolygon>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "targetsdialog.h"
#include "dronesdialog.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    __drones = new QStandardItemModel(0, 4, this);

    __flightBases = new QVector<FlightBase>;
    __targets = new QVector<Target>;
    __drones = new QVector<Drone>;


    drFlag = false;

    Target target1 = Target(Coordinates(4, 11));
    Target target2 = Target(Coordinates(10, 7));
    Target target3 = Target(Coordinates(16, 14));
    Target target4 = Target(Coordinates(11, 20));
    Target target5 = Target(Coordinates(9, 14));
    Target target6 = Target(Coordinates(18, 17));
    Target target7 = Target(Coordinates(15, 4));
    Target target8 = Target(Coordinates(19, 10));
    __targets->append(target1);
    __targets->append(target2);
    __targets->append(target3);
    __targets->append(target4);
    __targets->append(target5);
    __targets->append(target6);
    __targets->append(target7);
    __targets->append(target8);



    FlightBase base1 = FlightBase("base1", Coordinates(19, 3));
    __flightBases->append(base1);
    FlightBase base2 = FlightBase("base2", Coordinates(2, 20));
    __flightBases->append(base2);
    FlightBase base3 = FlightBase("base3", Coordinates(3, 3));
    __flightBases->append(base3);


    Drone drone1 = Drone(22, 3, "drone1", __flightBases->at(0));
    Drone drone2 = Drone(12, 3, "drone2", __flightBases->at(1));
    Drone drone3 = Drone(17, 3, "drone3", __flightBases->at(2));
    __drones->append(drone1);
    __drones->append(drone2);
    __drones->append(drone3);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_4_triggered()
{
    this->close();
}

void MainWindow::on_action_triggered()
{
    BasesDialog dialog;
    dialog.setBases(__flightBases);
    dialog.exec();
}



void MainWindow::on_action_2_triggered()
{
    DronesDialog dialog;
    dialog.setData(__flightBases, __drones);
    dialog.exec();

}

void MainWindow::on_action_3_triggered()
{
    TargetsDialog dialog;
    dialog.setTargets(__targets);
    dialog.exec();
}

void MainWindow::on_action_6_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_pushButton_clicked()
{

    DataRepository::getInstance().clearAll();
    QMutableVectorIterator<FlightBase> baseIterator(*__flightBases);
    while(baseIterator.hasNext())
    {
        DataRepository::getInstance().insertBase(baseIterator.next());
    }

    QMutableVectorIterator<Drone> droneIterator(*__drones);
    while(droneIterator.hasNext())
    {
        DataRepository::getInstance().insertDrone(droneIterator.next());
    }

    QMutableVectorIterator<Target> targerIterator(*__targets);
    while(targerIterator.hasNext())
    {
        DataRepository::getInstance().insertTarget(targerIterator.next());
    }

    // Resolve routes.
    RouteManager manager = RouteManager();

    __routes = new QVector<Route>;
   *__routes = QVector<Route>::fromStdVector(manager.calculateBestRoutes(DataRepository::getInstance().getTargets()));
    drFlag = true;
    this->update();
    pixmap = new QPixmap(300, 400);

    ui->textBrowser->clear();
    QPainter qp(pixmap);
    if (drFlag)
    {
        QPen pen(Qt::black, 2, Qt::SolidLine);

        QPolygon routes;
        ui->textBrowser->clear();
        for(int i = 0; i < __routes->count(); i++)
        {
            QString str = "Route for " + QString::number(i + 1) + " - ";

            QString color;

            switch (i) {
            case 0:
                pen.setColor(Qt::magenta);
                color = "Magenta";

                        break;
            case 1:
                pen.setColor(Qt::green);
                color = "Green";
                break;
            case 2:
                pen.setColor(Qt::cyan);
                color = "Cyan";
                break;
            case 3:
                pen.setColor(Qt::white);
                color = "White";
                break;
            case 4:
                pen.setColor(Qt::darkYellow);
                color = "DarkYellow";
                break;
            case 5:
                pen.setColor(Qt::gray);
                color = "Gray";
                break;
            default:
                break;
            }
            str.append(color);
            ui->textBrowser->append(str);

            Route megaRoute = __routes->at(i);
            QVector<Coordinates> coords = QVector<Coordinates>::fromStdVector(megaRoute.getCoordinates());
            for(int j = 0; j < coords.count(); j++)
            {
                routes.append(QPoint(coords.at(j).getPointX()*10, coords.at(j).getPointY()*10));
                QString string = QString::number(coords.at(j).getPointX()) + " - " + QString::number(coords.at(j).getPointY());
                ui->textBrowser->append(string);
            }

            qp.setPen(pen);
            qp.drawPolyline(routes);
            routes.clear();
        }
        pen.setColor(Qt::yellow);
        qp.setPen(pen);
        QPolygon basesPoly;

        for(int i = 0; i < __flightBases->count(); i++)
        {
            QPoint pnt(__flightBases->at(i).getBasePosition().getPointX()*10,__flightBases->at(i).getBasePosition().getPointY()*10);
            qp.drawPoint(pnt);
            qp.drawPoint(pnt.x()+1, pnt.y()+1);
            qp.drawPoint(pnt.x()+1, pnt.y()-1);
            qp.drawPoint(pnt.x()-1, pnt.y()+1);
            qp.drawPoint(pnt.x()-1, pnt.y()-1);
//            basesPoly.append(QPoint(__flightBases->at(i).getBasePosition().getPointX()*10,__flightBases->at(i).getBasePosition().getPointY()*10));
        }
        drFlag = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (pixmap != NULL)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *pixmap);
    }

}
