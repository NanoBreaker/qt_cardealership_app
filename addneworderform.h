#ifndef ADDNEWORDERFORM_H
#define ADDNEWORDERFORM_H

#include <QWidget>

namespace Ui {
class AddNewOrderForm;
}

class AddNewOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewOrderForm(QWidget *parent = 0);
    ~AddNewOrderForm();

private slots:
    void on_addItem_pushButton_clicked();

    void on_addOrder_pushButton_clicked();

    void doRefreshTable();

signals:
    void sendOrderID(QString orderID);

private:
    Ui::AddNewOrderForm *ui;
};

#endif // ADDNEWORDERFORM_H
