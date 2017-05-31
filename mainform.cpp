#include "mainform.h"
#include "ui_mainform.h"

#include "QMessageBox"
#include "QSqlDatabase"
#include "QtSql"
#include "QDebug"

#include "addorderform.h"
#include "addneworderform.h"

AddOrderForm * addOrderForm;
AddNewOrderForm * addNewOrderForm;

QSqlQueryModel *model;

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    addOrderForm = new AddOrderForm();
    addNewOrderForm = new AddNewOrderForm();

    model = new QSqlQueryModel();

    connect(this, SIGNAL(sendOrderID(QString)), addOrderForm, SLOT(reciveOrderID(QString)));
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::reciveUserType(int UserType)
{
    if(UserType == 0)
    {
        ui->admin_groupBox->setEnabled(false);
        ui->admin_groupBox_1->setEnabled(false);
    }
    else
    {
        ui->admin_groupBox_1->setEnabled(true);
        ui->admin_groupBox->setEnabled(true);
    }
}

void MainForm::on_showOrders_pushButton_clicked()
{
    model->setQuery("SELECT ORDER_ID as 'ИД заказа', DATE as 'Дата оформления заказа', FULL_NAME as 'ФИО', TELEPHONE_NUMBER as 'Номер мобильного телефона', STATUS as 'Статус заказа' FROM orders");
    ui->tableView->setModel(model);
}

void MainForm::on_exit_pushButton_clicked()
{
    emit mainFormIsClosedSend();
    this->setVisible(false);
}

void MainForm::on_showInformation_pushButton_clicked()
{
    QString selectedIndex = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
    emit sendOrderID(selectedIndex);
    addOrderForm->show();
}

void MainForm::on_pushButton_3_clicked()
{
    addNewOrderForm->show();
}

void MainForm::on_findByID_pushButton_clicked()
{
    QString queryString = "SELECT ORDER_ID as 'ИД заказа', DATE as 'Дата оформления заказа', FULL_NAME as 'ФИО', TELEPHONE_NUMBER as 'Номер мобильного телефона', STATUS as 'Статус заказа' FROM orders WHERE ORDER_ID = '";
    queryString.append(ui->orderID_lineEdit->text());
    queryString.append("'");
    model->setQuery(queryString);
    ui->tableView->setModel(model);
}

void MainForm::on_findByFullName_pushButton_clicked()
{
    QString queryString = "SELECT ORDER_ID as 'ИД заказа', DATE as 'Дата оформления заказа', FULL_NAME as 'ФИО', TELEPHONE_NUMBER as 'Номер мобильного телефона', STATUS as 'Статус заказа' FROM orders WHERE FULL_NAME = '";
    queryString.append(ui->fullName_lineEdit->text());
    queryString.append("'");
    model->setQuery(queryString);
    ui->tableView->setModel(model);
}

void MainForm::on_utverditi_pushButton_clicked()
{
    QString selectedIndex = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
    QString queryString = "UPDATE `orders` SET `STATUS` = 'Утверждён' WHERE `orders`.`ORDER_ID` = '";
    queryString.append(selectedIndex);
    queryString.append("'");

    QSqlQuery newQuery;
    newQuery.prepare(queryString);
    if(newQuery.exec()) QMessageBox::information(0, "Успех", "Утверждено!");
    else QMessageBox::information(0, "Ошибка", "Проверьте соединение с БД");
}

void MainForm::on_deleteObject_pushButton_clicked()
{
    QString selectedIndex = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
    QString queryString = "DELETE FROM `orders` WHERE `orders`.`ORDER_ID` = '";
    queryString.append(selectedIndex);
    queryString.append("'");

    QSqlQuery newQuery;
    newQuery.prepare(queryString);
    if(newQuery.exec()) QMessageBox::information(0, "Успех", "Удалено!");
    else QMessageBox::information(0, "Ошибка", "Проверьте соединение с БД");
}

void MainForm::on_showAutomobiles_pushButton_clicked()
{

}

void MainForm::on_showDetails_pushButton_clicked()
{

}

void MainForm::on_showServices_pushButton_clicked()
{

}
