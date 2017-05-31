#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H

#include <QWidget>

namespace Ui {
class AuthorizationForm;
}

class AuthorizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationForm(QWidget *parent = 0);
    ~AuthorizationForm();

private slots:
    void on_signInSystem_pushButton_clicked();

    void mainFormIsCloseRecived();

signals:
    void sendUserType(int UserType);

private:
    Ui::AuthorizationForm *ui;
};

#endif // AUTHORIZATIONFORM_H
