#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
#include<QApplication>


Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    db1=QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("NKVD.db");
    if(db1.open()){
        ui->regError->setText("Database "+db1.databaseName()+" is connected");
    }else{ui->regError->setText(db1.lastError().databaseText());}

    ui->newLoginInput->setPlaceholderText("Придумайте и введите логин ");
    ui->newpasswordInput2->setPlaceholderText("Повторите пароль ");
    ui->newpasswordInput1->setPlaceholderText("Придумайте и введите пароль ");
}

Registration::~Registration()
{
    delete ui;
}


void Registration::on_backToLogin_clicked()
{
    this->close();
    emit firstWindow();
    ui->newLoginInput->setText("");
    ui->newpasswordInput1->setText("");
    ui->newpasswordInput2->setText("");

}
void Registration::on_registrationButton_clicked()
{
    ui->regError->setText(db1.lastError().databaseText());
    QString username,password1,password2;
    username=ui->newLoginInput->text();
    password1=ui->newpasswordInput1->text();
    password2=ui->newpasswordInput2->text();
    QSqlQuery zapros2;
    QSqlQuery zapros3;
    bool flag=true;
    zapros2.exec("select * from users where login='"+username+"'");
            while (zapros2.next()) {
            flag=false;}
    if(!flag){ui->regError->setText("Это имя занято другим пользователем!");
        ui->newLoginInput->setText("");
        ui->newpasswordInput1->setText("");
        ui->newpasswordInput2->setText("");}
    else if(password1!=password2){ui->regError->setText("Пароли должны совпадать!");}
    else if((password1=="" )|( password2=="")){ui->regError->setText("Некорректный пароль!");}
    else if(flag){
         zapros3.prepare("INSERT INTO users(login,password) VALUES('"+username+"','"+password1+"');");
        if(zapros3.exec()){ui->regError->setText("Пользователь удачно зарегистрирован!");
            QSqlQuery newtabs;
            newtabs.exec("CREATE TABLE passwords_"+username+"(id  INTEGER PRIMARY KEY AUTOINCREMENT,password VARCHAR(255) NOT NULL,service VARCHAR(255) NOT NULL);");
            QSqlQuery firstRow;
            firstRow.exec("INSERT INTO passwords_"+username+"(password,service) VALUES('"+username+"','Password_Comrade');");
        }
    }

}
