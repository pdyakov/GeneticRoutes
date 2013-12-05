#include <QMutableVectorIterator>
#include "basesdialog.h"
#include "ui_basesdialog.h"


basesDialog::basesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basesDialog)
{


    ui->setupUi(this);

    //bases default
    __flightBasesList = new QStandardItemModel(0, 3, this);

    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setRootIsDecorated(false);

    __flightBasesList->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));
    __flightBasesList->setHeaderData(1, Qt::Horizontal, QObject::tr("X"));
    __flightBasesList->setHeaderData(2, Qt::Horizontal, QObject::tr("Y"));
    ui->treeView->setModel(__flightBasesList);
}

basesDialog::~basesDialog()
{
    delete ui;
}

void basesDialog::setBases(QVector<FlightBase> *bases)
{
    __flightBases = bases;
    for(int i = __flightBases->count()-1; i >= 0; i--)
    {
        FlightBase temp = __flightBases->at(i);
        QString *name = new QString(temp.getBaseName().c_str());
        float x = temp.getBasePosition().getPointX();
        float y = temp.getBasePosition().getPointY();
        addBase(__flightBasesList, *name, x, y);
    }

}


void basesDialog::addBase(QStandardItemModel *bases, const QString &name, const float x, const float y)
{
    bases->insertRow(0);
    bases->setData(bases->index(0, 0), name);
    bases->setData(bases->index(0, 1), x);
    bases->setData(bases->index(0, 2), y);
}

void basesDialog::on_plusButton_clicked()
{
    __flightBasesList->insertRow(__flightBasesList->rowCount());
    __flightBasesList->setData(__flightBasesList->index(__flightBasesList->rowCount()-1, 0), "Name");
    __flightBasesList->setData(__flightBasesList->index(__flightBasesList->rowCount()-1, 1), 0);
    __flightBasesList->setData(__flightBasesList->index(__flightBasesList->rowCount()-1, 2), 0);
}

void basesDialog::on_minusButton_clicked()
{
    QModelIndex list = ui->treeView->currentIndex();
    __flightBasesList->removeRow(list.row());
}

void basesDialog::on_okbutton_clicked()
{
    __flightBases->clear();
    for(int i = 0; i < __flightBasesList->rowCount(); i++ )
    {
        QString name = (__flightBasesList->item(i,0)->text());

        float X = __flightBasesList->item(i, 1)->text().toFloat();
        float Y = __flightBasesList->item(i, 2)->text().toFloat();
        Coordinates cords;
        cords.setPointX(X);
        cords.setPointY(Y);

        FlightBase *base = new FlightBase(name.toStdString(), cords);
        __flightBases->append(*base);
    }
    this->close();
}
