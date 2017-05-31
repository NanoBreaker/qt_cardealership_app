#include "additemform.h"
#include "ui_additemform.h"

#include "QMessageBox"
#include "QSqlDatabase"
#include "QtSql"

AddItemForm::AddItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddItemForm)
{
    ui->setupUi(this);
}

AddItemForm::~AddItemForm()
{
    delete ui;
}

void AddItemForm::on_addItem_pushButton_clicked()
{
    QString orderID = ui->orderID_lineEdit->text();
    QString itemName = ui->itemName_lineEdit->text();
    int index = ui->quantity_spinBox->value();
    QString indexStr = QString::number(index);
    QString cost = ui->cost_lineEdit->text();

    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO items (ORDER_ID, ITEM_NAME, QUANTITY, COST) VALUES (:orderid, :itemname, :quantity, :cost)");
    addQuery.bindValue(":orderid", orderID);
    addQuery.bindValue(":itemname", itemName);
    addQuery.bindValue(":quantity", indexStr);
    addQuery.bindValue(":cost", cost);

    if(addQuery.exec())
    {
        QMessageBox::information(0, "Успех", "Товар/услуга был(а) успешно добавлен(а)");
        emit askForRefreshTable();
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Проверьте правильность заполнения полей!");
    }
}

void AddItemForm::reciveOrderID(QString orderID)
{
    ui->orderID_lineEdit->setText(orderID);
}

