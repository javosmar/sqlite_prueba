#include "mainwindowsql.h"
#include "ui_mainwindowsql.h"
#include <QDebug>

char leido[16] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0};
QString jugador[6];
bool estado_serial, pedir_serial;
int i = 0;

MainWindowsql::MainWindowsql(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowsql)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    Serial_Conf();
    connect(serial,SIGNAL(readyRead()),this,SLOT(Serial_Pedir()));
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
            ui->comboBoxserie->insertItem(0,info.portName());
    }

    qDebug() << "Iniciado";
    QString nombre;
    nombre.append("base_datos_test.sqlite");
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
    consulta.append("CREATE TABLE IF NOT EXISTS equipo("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "numero INTEGER NOT NULL,"
                    "nombre VARCHAR(50),"
                    "apellido VARCHAR (50),"
                    "latitud INTEGER NOT NULL,"
                    "longitud INTEGER NOT NULL,"
                    "velocidad INTEGER NOT NULL"
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
    consulta.append("INSERT INTO equipo("
                    "numero,"
                    "nombre,"
                    "apellido,"
                    "latitud,"
                    "longitud,"
                    "velocidad)"
                    "VALUES("
                    ""+jugador[0]+","
                    "'"+jugador[1]+"',"
                    "'"+jugador[2]+"',"
                    ""+jugador[3]+","
                    ""+jugador[4]+","
                    ""+jugador[5]+""
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
    consulta.append("SELECT * FROM equipo");
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
        ui->tableWidgetdato->setItem(fila,4,new QTableWidgetItem(mostrar.value(5).toByteArray().constData()));
        ui->tableWidgetdato->setItem(fila,5,new QTableWidgetItem(mostrar.value(6).toByteArray().constData()));
        fila++;
    }
}

void MainWindowsql::on_pushButtoninsertar_clicked()
{
    insertarUsuario();
    mostrarDatos();
}

void MainWindowsql::Serial_Conf()
{
    serial->setPortName(ui->comboBoxserie->currentText());
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

void MainWindowsql::Serial_Conect()
{
    if((serial->open(QIODevice::ReadWrite)))
    {
        estado_serial = true;
    }
    else
        Serial_Error();
}

void MainWindowsql::Serial_Desconect()
{
    serial->close();
    estado_serial = false;
}

void MainWindowsql::Serial_Error()
{
    QMessageBox error;
    error.setText("Verifique la conexión de la placa.");
    error.setIcon(QMessageBox::Warning);
    error.exec();
}

void MainWindowsql::Serial_Pedir()
{
    while(serial->bytesAvailable() != 0){
        qint64 quantity = serial->readLine(leido,sizeof(leido));
        if(quantity > 1){
            jugador[i] = leido;
            qDebug() <<"dato: " << jugador[i];
            i++;
        }
        if(i > 5){
            i = 0;
            insertarUsuario();
            mostrarDatos();
            if(ui->checkBoxrepetir->isChecked()){
                serial->write("P");
                qDebug() << "-----";
            }
        }
    }
    ui->labelnumero->setText(jugador[0]);
    ui->labelnombre->setText(jugador[1]);
    ui->labelapellido->setText(jugador[2]);
    ui->labellatitud->setText(jugador[3]);
    ui->labellongitud->setText(jugador[4]);
    ui->labelvelocidad->setText(jugador[5]);
}

void MainWindowsql::on_pushButtonserie_clicked()
{
    Serial_Conf();
    if(estado_serial == false)
    {
        Serial_Conect();
        serial->clear();
    }
    else{
        Serial_Desconect();
    }
}

void MainWindowsql::on_pushButtonpedir_clicked()
{
    serial->write("P");
    qDebug() << "--------";
}
