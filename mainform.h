#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:
    void reciveUserType(int UserType);

    void on_showOrders_pushButton_clicked();

    void on_exit_pushButton_clicked();

    void on_showInformation_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_findByID_pushButton_clicked();

    void on_findByFullName_pushButton_clicked();

    void on_utverditi_pushButton_clicked();

    void on_deleteObject_pushButton_clicked();

    void on_showAutomobiles_pushButton_clicked();

    void on_showDetails_pushButton_clicked();

    void on_showServices_pushButton_clicked();

signals:
    void mainFormIsClosedSend();

    void sendOrderID(QString orderID);

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
