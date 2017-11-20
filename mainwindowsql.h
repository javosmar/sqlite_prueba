#ifndef MAINWINDOWSQL_H
#define MAINWINDOWSQL_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class MainWindowsql;
}

class MainWindowsql : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowsql(QWidget *parent = 0);
    ~MainWindowsql();

    void crearTablaUsuarios();

private:
    Ui::MainWindowsql *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOWSQL_H
