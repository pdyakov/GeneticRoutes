#ifndef BASESDIALOG_H
#define BASESDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "src/DataAccess/DataRepository.h"

namespace Ui {
class BasesDialog;
}

class BasesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BasesDialog(QWidget *parent = 0);
    ~BasesDialog();
    void setBases(QVector<FlightBase> *bases);

private slots:
    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_okbutton_clicked();

private:
    Ui::BasesDialog *ui;

    QVector<FlightBase> *__flightBases;

    QStandardItemModel *__flightBasesList;

    void addBase(QStandardItemModel *bases, const QString &name, const float x, const float y);

};

#endif // BASESDIALOG_H
