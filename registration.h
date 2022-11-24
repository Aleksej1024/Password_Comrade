#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <QWidget>
#include <QSqlDatabase>
#include<QSqlError>
#include<QSqlRecord>
#include<QSqlQuery>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

signals:
    void firstWindow();

private slots:
    void on_backToLogin_clicked();
    void on_registrationButton_clicked();

private:
    Ui::Registration *ui;
    QSqlDatabase db1;


};
#endif // REGISTRATION_H

