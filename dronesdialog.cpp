#include "dronesdialog.h"
#include "ui_dronesdialog.h"

DronesDialog::DronesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DronesDialog)
{
    ui->setupUi(this);
    __dronesModel = new QStandardItemModel(0, 4, this);

    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setRootIsDecorated(false);

    __dronesModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));
    __dronesModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Скорость"));
    __dronesModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Дальность"));
    __dronesModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Номер базы"));

    ui->treeView->setModel(__dronesModel);
}

DronesDialog::~DronesDialog()
{
    delete ui;
}

void DronesDialog::setData(QVector<FlightBase> *flightBases, QVector<Drone> *drones)
{
    __flightBases = flightBases;
    __drones = drones;

    for(int j = __drones->count()-1; j >= 0; j--)
    {
        Drone drone = __drones->at(j);
        FlightBase droneHome = drone.getFlightBase();
        Coordinates baseCoords = droneHome.getBasePosition();

        QVectorIterator<FlightBase> iter(*__flightBases);
        int i = 0;
        while(iter.hasNext())
        {
            FlightBase temp = iter.next();
            if ( (baseCoords.getPointX() == temp.getBasePosition().getPointX()) &&
                 (baseCoords.getPointY() == temp.getBasePosition().getPointY()))
            {
                break;
            }
            i++;
        }
        QString *name = new QString(drone.getDroneName().c_str());

        float speed = drone.getDroneSpeed();
        float ftime = drone.getRemainingFlightTime();
        __dronesModel->insertRow(0);
        __dronesModel->setData(__dronesModel->index(0,0), *name);
        __dronesModel->setData(__dronesModel->index(0,1), speed);
        __dronesModel->setData(__dronesModel->index(0,2), ftime);
        __dronesModel->setData(__dronesModel->index(0,3), i+1);
    }
}

void DronesDialog::on_okButton_clicked()
{
    __drones->clear();
    for(int i = 0; i < __dronesModel->rowCount(); i++ )
    {
        QString name = (__dronesModel->item(i,0)->text());

        float speed = __dronesModel->item(i, 1)->text().toFloat();
        float ftime = __dronesModel->item(i, 2)->text().toFloat();

        FlightBase base = __flightBases->at(__dronesModel->item(i,3)->text().toInt()-1);
        Drone *drone = new Drone(speed, ftime, name.toStdString(), base);
        __drones->append(*drone);
    }
    this->close();
}

void DronesDialog::on_minusButton_clicked()
{
    QModelIndex list = ui->treeView->currentIndex();
    __dronesModel->removeRow(list.row());
}

void DronesDialog::on_plusButton_clicked()
{
    __dronesModel->insertRow(__dronesModel->rowCount());
    __dronesModel->setData(__dronesModel->index(__dronesModel->rowCount()-1, 0), "Name");
    __dronesModel->setData(__dronesModel->index(__dronesModel->rowCount()-1, 1), 0);
    __dronesModel->setData(__dronesModel->index(__dronesModel->rowCount()-1, 2), 0);
}
