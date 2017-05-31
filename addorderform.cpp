#include "addorderform.h"
#include "ui_addorderform.h"

#include "QMessageBox"
#include "QSqlDatabase"
#include "QtSql"

QSqlQueryModel *modelOfItems;

AddOrderForm::AddOrderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOrderForm)
{
    ui->setupUi(this);

    modelOfItems = new QSqlQueryModel();
}

AddOrderForm::~AddOrderForm()
{
    delete ui;
}

void AddOrderForm::reciveOrderID(QString orderID)
{
    ui->orderID_lineEdit->setText(orderID);

    QSqlQuery getInfoQuery;
    getInfoQuery.prepare("SELECT * FROM orders WHERE ORDER_ID = :id");
    getInfoQuery.bindValue(":id", orderID);
    getInfoQuery.exec();

    getInfoQuery.first();
    QString _orderID = getInfoQuery.value(0).toString();
    QDate date = getInfoQuery.value(1).toDate();
    QString fullName = getInfoQuery.value(2).toString();
    QString livingAdress = getInfoQuery.value(3).toString();
    QString deliveryAdress = getInfoQuery.value(4).toString();
    QString telephoneNumber = getInfoQuery.value(5).toString();
    QDate birthdayDate = getInfoQuery.value(6).toDate();
    QString orderStatus = getInfoQuery.value(7).toString();

    ui->orderRegDate_dateEdit->setDate(date);
    ui->fullName_lineEdit->setText(fullName);
    ui->livingAdress_lineEdit->setText(livingAdress);
    ui->deliveryAdress_lineEdit->setText(deliveryAdress);
    ui->phoheNumber_lineEdit->setText(telephoneNumber);
    ui->birhtDay_dateEdit->setDate(birthdayDate);
    ui->orderStatus_lineEdit->setText(orderStatus);

    QString queryStr = "SELECT ITEM_NAME as 'Название товара/услуги', QUANTITY as 'Количество/Объем', COST as 'Цена за ед.' FROM items WHERE ORDER_ID = ";
    queryStr.append(_orderID);
    modelOfItems->setQuery(queryStr);
    ui->tableView->setModel(modelOfItems);
}
