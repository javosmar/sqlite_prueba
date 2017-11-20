#ifndef MAINWINDOWSQL_H
#define MAINWINDOWSQL_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSerialPort>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QSerialPortInfo>

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
    void insertarUsuario();
    void mostrarDatos();

private slots:
    void Serial_Conf();
    void Serial_Conect();
    void Serial_Desconect();
    void Serial_Error();
    void Serial_Pedir();
    void on_pushButtoninsertar_clicked();

    void on_pushButtonserie_clicked();

private:
    Ui::MainWindowsql *ui;
    QSqlDatabase db;
    QSerialPort *serial;
};

#endif // MAINWINDOWSQL_H
