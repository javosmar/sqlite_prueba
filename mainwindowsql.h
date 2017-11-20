#ifndef MAINWINDOWSQL_H
#define MAINWINDOWSQL_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

namespace Ui {
class MainWindowsql;
}

class MainWindowsql : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowsql(QWidget *parent = 0);
    ~MainWindowsql();

private:
    Ui::MainWindowsql *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOWSQL_H
