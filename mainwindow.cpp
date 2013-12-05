#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "targetsdialog.h"
#include "dronesdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    __drones = new QStandardItemModel(0, 4, this);


    __flightBases = new QVector<FlightBase>;
    __targets = new QVector<Target>;
    __drones = new QVector<Drone>;




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
    basesDialog diallog;
    diallog.setBases(__flightBases);
    diallog.exec();
}



void MainWindow::on_action_2_triggered()
{
    dronesDialog diallog;
    diallog.setData(__flightBases, __drones);
    diallog.exec();

}

void MainWindow::on_action_3_triggered()
{
    targetsDialog diallog;
    diallog.setTargets(__targets);
    diallog.exec();
}
