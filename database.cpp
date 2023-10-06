#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    pTableModel = nullptr;
    pQueryModel = nullptr;
    pTableView = nullptr;
}

DataBase::~DataBase()
{
    delete pTableModel;
    delete pQueryModel;
    delete pTableView;
    delete dataBase;
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

    if (status) {
        pTableModel = new QSqlTableModel(nullptr, *dataBase);
        pQueryModel = new QSqlQueryModel;
        pTableView = new QTableView;
    }
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    delete pTableModel;
    delete pQueryModel;
    delete pTableView;

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
    if (requestType == requestAllFilms) {
        pTableModel->setQuery("SELECT title, description FROM film", *dataBase);
        pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        pTableModel->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        pTableModel->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));

        pTableView->setModel(pTableModel);

        emit sig_SendDataFromDB(pTableView, requestAllFilms);
    }
    else if (requestType == requestComedy){
        pQueryModel->setQuery("SELECT title, description FROM film f "
                              "JOIN film_category fc on f.film_id = fc.film_id "
                              "JOIN category c on c.category_id = fc.category_id "
                              "WHERE c.name = 'Comedy'",
                               *dataBase);

        pQueryModel->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        pQueryModel->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));

        pTableView->setModel(pQueryModel);

        emit sig_SendDataFromDB(pTableView, requestComedy);
    }
    else if (requestType == requestHorrors){
        pQueryModel->setQuery("SELECT title, description FROM film f "
                               "JOIN film_category fc on f.film_id = fc.film_id "
                               "JOIN category c on c.category_id = fc.category_id "
                               "WHERE c.name = 'Horror'",
                               *dataBase);

        pQueryModel->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        pQueryModel->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));

        pTableView->setModel(pQueryModel);

        emit sig_SendDataFromDB(pTableView, requestComedy);
    }
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
