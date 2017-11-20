#include "mainwindowsql.h"
#include "ui_mainwindowsql.h"
#include <QDebug>

MainWindowsql::MainWindowsql(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowsql)
{
    ui->setupUi(this);

    qDebug() << "Iniciado";

    QString nombre;
    nombre.append("base_datos.sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombre);

    if(db.open()){
        qDebug() << "base de datos iniciada";
    }
    else{
        qDebug() << "error al abrir base de datos";
    }
}

MainWindowsql::~MainWindowsql()
{
    delete ui;
}
