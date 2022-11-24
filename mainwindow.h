#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include<QSqlError>
#include<QSqlRecord>
#include<QSqlQuery>
#include<QKeyEvent>
#include<registration.h>
#include<passwords.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_QVhodButton_clicked();
    //Регистрация
    void on_registration_next_clicked();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    //Окно регистрации
    Registration *registration;
    //Окно паролей
    Passwords *passwords;
signals:
    void peredacha(QString);
};



#endif // MAINWINDOW_H
