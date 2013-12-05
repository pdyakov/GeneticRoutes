#include "targetsdialog.h"
#include "ui_targetsdialog.h"

TargetsDialog::TargetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetsDialog)
{
    ui->setupUi(this);

    __targetsList = new QStandardItemModel(0, 2, this);

    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setRootIsDecorated(false);

    __targetsList->setHeaderData(0, Qt::Horizontal, QObject::tr("X"));
    __targetsList->setHeaderData(1, Qt::Horizontal, QObject::tr("Y"));
    ui->treeView->setModel(__targetsList);
}

TargetsDialog::~TargetsDialog()
{
    delete ui;
}

void TargetsDialog::on_minusButton_clicked()
{
    QModelIndex list = ui->treeView->currentIndex();
    __targetsList->removeRow(list.row());
    __targets->remove(list.row());
}

void TargetsDialog::on_plusButton_clicked()
{
    __targetsList->insertRow(__targetsList->rowCount());
    __targetsList->setData(__targetsList->index(__targetsList->rowCount()-1, 0), 0);
    __targetsList->setData(__targetsList->index(__targetsList->rowCount()-1, 1), 0);
    Target *target = new Target(Coordinates(0,0));
    __targets->append(*target);
}

void TargetsDialog::on_okButton_clicked()
{
    __targets->clear();
    for(int i = 0; i < __targetsList->rowCount(); i++ )
    {
        float X = __targetsList->item(i, 0)->text().toFloat();
        float Y = __targetsList->item(i, 1)->text().toFloat();
        Coordinates cords;
        cords.setPointX(X);
        cords.setPointY(Y);
        Target *target = new Target(cords);
        __targets->append(*target);
    }
    this->close();
}

void TargetsDialog::setTargets(QVector<Target> *targets)
{
    __targets = targets;
    for(int i = __targets->count()-1; i >= 0; i--)
    {
        Target temp = __targets->at(i);
        float x = temp.getTargetPosition().getPointX();
        float y = temp.getTargetPosition().getPointY();
        addTarget(__targetsList, x, y);
    }

}

void TargetsDialog::addTarget(QStandardItemModel *targets, const float x, const float y)
{
    targets->insertRow(0);
    targets->setData(targets->index(0, 0), x);
    targets->setData(targets->index(0, 1), y);
}
