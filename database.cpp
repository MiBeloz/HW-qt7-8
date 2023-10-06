#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    pQueryModel = new QSqlQueryModel(this);
    pTableModel = new QSqlTableModel(this, *dataBase);
    pTableView = new QTableView;
}

DataBase::~DataBase()
{
    delete dataBase;
    delete pTableView;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());


    ///Тут должен быть код ДЗ

    bool status;
    status = dataBase->open();
    emit sig_SendStatusConnection(status);
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request, int requestType)
{
    ///Тут должен быть код ДЗ

    //ДЗ

    //end ДЗ

    //ДЗ
//    pQueryModel.setQuery("SELECT title, release_year FROM film", *dataBase);
//    pQueryModel.setHeaderData(0, Qt::Horizontal, QObject::tr("title"));
//    pQueryModel.setHeaderData(1, Qt::Horizontal, QObject::tr("release_year"));
    //end ДЗ


    switch (requestType) {
    case requestAllFilms:
    {
        pTableModel->setTable("film");
        pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        pTableModel->select();
        pTableModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
        pTableModel->setHeaderData(1, Qt::Horizontal, tr("Salary"));

        pTableView->setModel(pTableModel);

        emit sig_SendDataFromDB(pTableView, requestAllFilms);
        break;
    }
    case requestComedy:
    {
        emit sig_SendDataFromDB(pTableView, requestComedy);
        break;
    }
    case requestHorrors:
    {
        //tableWidget->setColumnCount(3);
        //tableWidget->setRowCount(0);
        //QStringList hdrs;
        //hdrs << "Название" << "Год выпуска" << "Жанр";
        //tableWidget->setHorizontalHeaderLabels(hdrs);

        //uint32_t conterRows = 0;

        //while(simpleQuery->next()){
        //    QString str;
        //    tableWidget->insertRow(conterRows);

        //    for(int i = 0; i<tableWidget->columnCount(); ++i){

        //        str = simpleQuery->value(i).toString();
        //        QTableWidgetItem *item = new QTableWidgetItem(str);
        //        tableWidget->setItem(tableWidget->rowCount() - 1, i, item);

        //    }
        //    ++conterRows;
        //}

        emit sig_SendDataFromDB(pTableView, requestHorrors);
        break;
    }

    default:
        break;
    }


}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
