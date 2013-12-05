#ifndef TARGETSDIALOG_H
#define TARGETSDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "src/DataAccess/DataRepository.h"

namespace Ui {
class targetsDialog;
}

class targetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit targetsDialog(QWidget *parent = 0);
    ~targetsDialog();
    void setTargets(QVector<Target> *targets);

private slots:
    void on_minusButton_clicked();

    void on_plusButton_clicked();

    void on_okButton_clicked();

private:
    Ui::targetsDialog *ui;

    QVector<Target> *__targets;

    QStandardItemModel *__targetsList;

    void addTarget(QStandardItemModel *targets, const float x, const float y);

};

#endif // TARGETSDIALOG_H
