#ifndef ADDORDERFORM_H
#define ADDORDERFORM_H

#include <QWidget>

namespace Ui {
class AddOrderForm;
}

class AddOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddOrderForm(QWidget *parent = 0);
    ~AddOrderForm();

private slots:
    void reciveOrderID(QString orderID);

private:
    Ui::AddOrderForm *ui;
};

#endif // ADDORDERFORM_H
