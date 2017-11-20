#include "mainwindowsql.h"
#include "ui_mainwindowsql.h"

//editado online otra vez

MainWindowsql::MainWindowsql(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowsql)
{
    ui->setupUi(this);
}

MainWindowsql::~MainWindowsql()
{
    delete ui;
}
