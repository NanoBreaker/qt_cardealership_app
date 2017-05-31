#include "authorizationform.h"
#include "ui_authorizationform.h"
#include "QMessageBox"
#include "QSqlDatabase"
#include "QtSql"
#include "QDebug"

#include "connetionform.h"
#include "authorizationform.h"
#include "mainform.h"

MainForm * mainForm;

AuthorizationForm::AuthorizationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationForm)
{
    mainForm = new MainForm();

    ui->setupUi(this);
    ui->userID_lineEdit->setText("111111");
    ui->userPassword_lineEdit->setText("admin");

    connect(this, SIGNAL(sendUserType(int)), mainForm, SLOT(reciveUserType(int)));
    connect(mainForm, SIGNAL(mainFormIsClosedSend()), this, SLOT(mainFormIsCloseRecived()));
}

AuthorizationForm::~AuthorizationForm()
{
    delete ui;
}

void AuthorizationForm::mainFormIsCloseRecived()
{
    this->setVisible(true);
}

void AuthorizationForm::on_signInSystem_pushButton_clicked()
{
    QString userID = ui->userID_lineEdit->text();
    QString userPassword = ui->userPassword_lineEdit->text();

    QSqlQuery authQuery;
    authQuery.prepare("SELECT COUNT(USER_ID) FROM users WHERE USER_ID = :userid AND USER_PASSWORD = :userpassword");
    authQuery.bindValue(":userid", userID);
    authQuery.bindValue(":userpassword", userPassword);
    authQuery.exec();
    authQuery.first();

    int index = authQuery.value(0).toInt();

    if(index == 1)
    {
        QMessageBox::information(0, "Успешно", "Успешная авторизация");

        QSqlQuery getUserType;
        getUserType.prepare("SELECT TYPE FROM users WHERE USER_ID = :userid");
        getUserType.bindValue(":userid", userID);
        getUserType.exec();
        getUserType.first();

        QString userType_string = getUserType.value(0).toString();
        if(userType_string.compare("Управляющий")) emit sendUserType(0);
        else emit sendUserType(1);

       // this->setVisible(false);
        mainForm->show();
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Такого пользователя не существует");
    }
}
