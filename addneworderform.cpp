#include "addneworderform.h"
#include "ui_addneworderform.h"
#include "additemform.h"

#include "QMessageBox"
#include "QSqlDatabase"
#include "QtSql"

AddItemForm * addItemForm;

QSqlQueryModel * modelOfNewItems;

AddNewOrderForm::AddNewOrderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewOrderForm)
{
    ui->setupUi(this);

    modelOfNewItems = new QSqlQueryModel();

    addItemForm = new AddItemForm();

    connect(this, SIGNAL(sendOrderID(QString)), addItemForm, SLOT(reciveOrderID(QString)));
    connect(addItemForm, SIGNAL(askForRefreshTable()), this, SLOT(doRefreshTable()));
}

AddNewOrderForm::~AddNewOrderForm()
{
    delete ui;
}

void AddNewOrderForm::on_addItem_pushButton_clicked()
{
    if(ui->orderID_lineEdit->text().isEmpty())
    {
        QMessageBox::information(0, "Ошибка", "Сначала введите ИД заказа!");
    }
    else
    {
        emit sendOrderID(ui->orderID_lineEdit->text());
        addItemForm->show();
    }
}

void AddNewOrderForm::doRefreshTable()
{
    QString queryStr = "SELECT ITEM_NAME as 'Название товара/услуги', QUANTITY as 'Количество/Объем', COST as 'Цена за ед.' FROM items WHERE ORDER_ID = ";
    queryStr.append(ui->orderID_lineEdit->text());
    modelOfNewItems->setQuery(queryStr);
    ui->tableView->setModel(modelOfNewItems);
}

void AddNewOrderForm::on_addOrder_pushButton_clicked()
{
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO orders (`ORDER_ID`, `DATE`, `FULL_NAME`, `LIVING_ADRESS`, `DELIVERY_ADRESS`, `TELEPHONE_NUMBER`, `BIRTHDAY_DATE`, `STATUS`) VALUES (:orderid, :date, :fullname, :livingadress, :deliveryadress, :telnumber, :birthdaydate, :status)");
    addQuery.bindValue(":orderid", ui->orderID_lineEdit->text());
    addQuery.bindValue(":date", ui->orderRegDate_dateEdit->date());
    addQuery.bindValue(":fullname", ui->fullName_lineEdit->text());
    addQuery.bindValue(":livingadress", ui->livingAdress_lineEdit->text());
    addQuery.bindValue(":deliveryadress", ui->deliveryAdress_lineEdit->text());
    addQuery.bindValue(":telnumber", ui->phoheNumber_lineEdit->text());
    addQuery.bindValue(":birthdaydate", ui->birhtDay_dateEdit->date());
    addQuery.bindValue(":status", ui->orderStatus_lineEdit->text());

    if(addQuery.exec())
    {
        QMessageBox::information(0, "Успех", "Заказ был добавлен!");
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Проверьте правильность заполнения полей");
    }
}
