    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include"registration.h"

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    registration=new Registration;
    connect(registration,&Registration::firstWindow,this,&MainWindow::show);
    passwords=new Passwords;
    connect(passwords,&Passwords::firstWindow,this,&MainWindow::show);

    connect(this,&MainWindow::peredacha,passwords,&Passwords::poluchenie);
    ui->loginInput->setPlaceholderText("Введите ваш логин ");
    ui->passwordInput->setPlaceholderText("Введите ваш пароль ");
    /*Check databse connections*/

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("NKVD.db");
    if(db.open()){
        ui->labelv->setText("Database "+db.databaseName()+" is connected");
    }else{ui->labelv->setText(db.lastError().databaseText());}

    QSqlQuery (newtabs);
    newtabs.exec("CREATE TABLE users(id  INTEGER PRIMARY KEY AUTOINCREMENT,login VARCHAR(255) NOT NULL,password varchar(255) NOT NULL);");
    newtabs.exec("CREATE TABLE temp(username VARCHAR(255) NOT NULL);");


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_QVhodButton_clicked()
{
    QString username,password;
    username=ui->loginInput->text();
    password=ui->passwordInput->text();
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("NKVD.db");
    if(db.open()){
        ui->labelv->setText("Database "+db.databaseName()+" is connected");
    QSqlQuery zapros1;
    zapros1.exec("SELECT * FROM users WHERE login='"+username+"'and password='"+password+"'");
        bool flag=false;
        while(zapros1.next()){
            flag=true;
        }
        if ((username=="")|(password=="")){
            ui->labelv->setText("Поля не могут быть пустыми!");
        }
        else if (!flag){
            ui->labelv->setText("Неверный Логин или пароль!");
            ui->loginInput->setText("");
            ui->passwordInput->setText("");
        }
        else if (flag){
            if(db.open()){ui->labelv->setText("Database "+db.databaseName()+" is connected");}
            ui->loginInput->setText("");
            ui->passwordInput->setText("");
            emit peredacha(username);
            passwords->close();
            passwords->show();
            this->close();

    }
}else{ui->labelv->setText(db.lastError().databaseText());}
}

void MainWindow::on_registration_next_clicked()

{
    ui->loginInput->setText("");
    ui->passwordInput->setText("");
    if(db.open()){
        ui->labelv->setText("Database "+db.databaseName()+" is connected");
    }else{ui->labelv->setText(db.lastError().databaseText());}
    registration->show();
    this->close();
}



