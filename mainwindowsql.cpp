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

    crearTablaUsuarios();
}

MainWindowsql::~MainWindowsql()
{
    delete ui;
}

void MainWindowsql::crearTablaUsuarios()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(50),"
                    "apellido VARCHAR (50),"
                    "edad INTEGER NOT NULL,"
                    "clase INTEGER NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug() << "tabla creada correctamente";
    }
    else{
        qDebug() << "ERROR! " << crear.lastError();
    }
}
