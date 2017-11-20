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
    mostrarDatos();
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

void MainWindowsql::insertarUsuario()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre,"
                    "apellido,"
                    "edad,"
                    "clase)"
                    "VALUES("
                    "'"+ui->lineEditnombre->text()+"',"
                    "'"+ui->lineEditapellido->text()+"',"
                    ""+ui->lineEditedad->text()+","
                    ""+ui->lineEditclase->text()+""
                    ");");
    QSqlQuery insertar;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug() << "usuario agregado correctamente";
    }
    else{
        qDebug() << "ERROR! " << insertar.lastError();
    }
}

void MainWindowsql::mostrarDatos()
{
    QString consulta;
    consulta.append("SELECT * FROM usuarios");
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug() << "consulta realizada con exito";
    }
    else{
        qDebug() << "ERROR! " << mostrar.lastError();
    }

    int fila = 0;
    ui->tableWidgetdato->setRowCount(0);
    while(mostrar.next()){
        ui->tableWidgetdato->insertRow(fila);
        ui->tableWidgetdato->setItem(fila,0,new QTableWidgetItem(mostrar.value(1).toByteArray().constData()));
        ui->tableWidgetdato->setItem(fila,1,new QTableWidgetItem(mostrar.value(2).toByteArray().constData()));
        ui->tableWidgetdato->setItem(fila,2,new QTableWidgetItem(mostrar.value(3).toByteArray().constData()));
        ui->tableWidgetdato->setItem(fila,3,new QTableWidgetItem(mostrar.value(4).toByteArray().constData()));
        fila++;
    }
}

void MainWindowsql::on_pushButtoninsertar_clicked()
{
    insertarUsuario();
    mostrarDatos();
}
