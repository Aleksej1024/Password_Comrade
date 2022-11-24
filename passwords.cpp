#include "passwords.h"
#include "ui_passwords.h"
//
Passwords::Passwords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Passwords)

{
    ui->setupUi(this);

}


Passwords::~Passwords()
{
    delete ui;
}


void Passwords::poluchenie(QString name)
{
    db2=QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName("NKVD.db");
    QString adress;
    adress="passwords_"+name;
    //ui->passwordsError->setText(adress);
    if(db2.open()){
        ui->passwordsError->setText("Database "+db2.databaseName()+" is connected");
        model=new QSqlTableModel(this,db2);
        model->setTable(adress);
        model->select();
        ui->tableView->setModel(model);

        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Пароль"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Сервис"));
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->setColumnHidden(3,true);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else{ui->passwordsError->setText(db2.lastError().databaseText());}

}

void Passwords::on_backToLogin2_clicked()
{

    this->close();
    emit firstWindow();

}



void Passwords::on_pushToAdd_clicked()
{
    model->insertRow(model->rowCount());
    model->submitAll();

}

void Passwords::on_pushToDelete_clicked()
{   if(currentRow!=0){
    model->removeRow(currentRow);
    model->select();
    model->submitAll();
    }
}

void Passwords::on_tableView_clicked(const QModelIndex &index)
{
    currentRow=index.row();
}
