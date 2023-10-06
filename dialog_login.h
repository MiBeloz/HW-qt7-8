#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_login(QWidget *parent = nullptr);
    ~Dialog_login();

signals:
    void sig_sendData(QVector<QString> dbData);

private slots:
  void on_bbox_OkCancel_accepted();

private:
    Ui::Dialog_login *ui;
    QVector<QString> data;
};

#endif // DIALOG_LOGIN_H
