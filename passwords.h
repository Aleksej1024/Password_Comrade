#ifndef PASSWORDS_H
#define PASSWORDS_H
#include <QSqlDatabase>
#include<QSqlError>
#include<QSqlRecord>
#include<QSqlQuery>
#include <QSqlTableModel>
#include <QWidget>

namespace Ui {
class Passwords;
}

class Passwords : public QWidget
{
    Q_OBJECT

public:
    explicit Passwords(QWidget *parent = nullptr);
    ~Passwords();

signals:
    void firstWindow();
public slots:
    void poluchenie(QString name);
private slots:
    //void on_QVhodButton_clicked();
    void on_backToLogin2_clicked();

    void on_pushToAdd_clicked();


    void on_pushToDelete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Passwords *ui;
    QSqlDatabase db2;
    QSqlTableModel *model;
    int currentRow;

};

#endif // PASSWORDS_H
