#ifndef CONNETIONFORM_H
#define CONNETIONFORM_H

#include <QMainWindow>
#include "QSqlDatabase"

namespace Ui {
class ConnetionForm;
}

class ConnetionForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnetionForm(QWidget *parent = 0);
    QSqlDatabase dataBase;
    ~ConnetionForm();

private slots:
    void on_establishConnetion_pushButton_clicked();

    void on_terminateConnection_pushButton_clicked();

    void on_signInSystem_pushButton_clicked();

private:
    Ui::ConnetionForm *ui;
};

#endif // CONNETIONFORM_H
