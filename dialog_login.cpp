#include "dialog_login.h"
#include "database.h"
#include "ui_dialog_login.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);

    ui->le_hostname->setText("981757-ca08998.tmweb.ru");
    ui->le_databaseName->setText("netology_cpp");
    ui->le_login->setText("netology_usr_cpp");
    ui->le_pass->setText("CppNeto3");
    ui->spB_port->setValue(5432);

    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}

Dialog_login::~Dialog_login()
{
    delete ui;
}

void Dialog_login::on_bbox_OkCancel_accepted()
{
    data[hostName] = ui->le_hostname->text();
    data[dbName] = ui->le_databaseName->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_pass->text();
    data[port] = ui->spB_port->text();

    emit sig_sendData(data);
}

