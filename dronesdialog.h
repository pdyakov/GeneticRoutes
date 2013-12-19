#ifndef DRONESDIALOG_H
#define DRONESDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "src/DataAccess/DataRepository.h"
namespace Ui {
class dronesDialog;
}

class DronesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DronesDialog(QWidget *parent = 0);
    ~DronesDialog();
    void setData(QVector<FlightBase> *flightBases, QVector<Drone> *drones);

private slots:
    void on_okButton_clicked();

    void on_minusButton_clicked();

    void on_plusButton_clicked();

private:
    Ui::dronesDialog *ui;

    QVector<FlightBase> *__flightBases;
    QVector<Drone> *__drones;

    QStandardItemModel *__dronesModel;




};

#endif // DRONESDIALOG_H
