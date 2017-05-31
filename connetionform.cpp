#include "connetionform.h"
#include "ui_connetionform.h"
#include "authorizationform.h"

#include "QSqlDatabase"
#include "QtSql"
#include "QDebug"

AuthorizationForm * authorizationForm;

ConnetionForm::ConnetionForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnetionForm)
{
    authorizationForm = new AuthorizationForm();

    ui->setupUi(this);
    ui->hostName_lineEdit->setText("127.0.0.1");
    ui->dataBaseName_lineEdit->setText("cardealership_database");
    ui->userName_lineEdit->setText("root");
    ui->password_lineEdit->setText("");
    ui->port_lineEdit->setText("3306");
    ui->connectionStatus_lineEdit->setText("СОЕДИНЕНИЕ ЕЩЕ НЕ УСТАНОВЛЕНО");

    QPalette p = ui->connectionStatus_lineEdit->palette();
    p.setColor(QPalette::Base, Qt::yellow);
    ui->connectionStatus_lineEdit->setPalette(p);

    ui->signInSystem_pushButton->setEnabled(false);

    dataBase = QSqlDatabase::addDatabase("QMYSQL");
}

ConnetionForm::~ConnetionForm()
{
    delete ui;
}

void ConnetionForm::on_establishConnetion_pushButton_clicked()
{
    QString hostName_string = ui->hostName_lineEdit->text();
    QString dataBaseName_string = ui->dataBaseName_lineEdit->text();
    QString userName_string = ui->userName_lineEdit->text();
    QString password_string = ui->password_lineEdit->text();
    QString port_string = ui->port_lineEdit->text();

    bool isSuccessful;
    int port_int = port_string.toInt(&isSuccessful, 10);

    dataBase.setHostName(hostName_string);
    dataBase.setDatabaseName(dataBaseName_string);
    dataBase.setUserName(userName_string);
    dataBase.setPassword(password_string);
    dataBase.setPort(port_int);
    dataBase.setConnectOptions();

    bool connetionEstablished = dataBase.open();

    if(connetionEstablished)
    {
        ui->connectionStatus_lineEdit->setText("СОЕДИНЕНИЕ УСТАНОВЛЕНО");
        QPalette p = ui->connectionStatus_lineEdit->palette();
        p.setColor(QPalette::Base, Qt::green);
        ui->connectionStatus_lineEdit->setPalette(p);
        ui->signInSystem_pushButton->setEnabled(true);
    }
    else
    {
        ui->connectionStatus_lineEdit->setText("СОЕДИНЕНИЕ НЕ УСТАНОВЛЕНО");
        QPalette p = ui->connectionStatus_lineEdit->palette();
        p.setColor(QPalette::Base, Qt::red);
        ui->connectionStatus_lineEdit->setPalette(p);
        ui->signInSystem_pushButton->setEnabled(false);
    }
}

void ConnetionForm::on_terminateConnection_pushButton_clicked()
{
    dataBase.close();
    ui->connectionStatus_lineEdit->setText("СОЕДИНЕНИЕ РАЗОРВАНО");
    QPalette p = ui->connectionStatus_lineEdit->palette();
    p.setColor(QPalette::Base, Qt::yellow);
    ui->connectionStatus_lineEdit->setPalette(p);
    ui->signInSystem_pushButton->setEnabled(false);
}

void ConnetionForm::on_signInSystem_pushButton_clicked()
{
    //this->setVisible(false);
    authorizationForm->show();
}
