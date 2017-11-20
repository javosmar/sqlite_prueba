#include "mainwindowsql.h"
#include "ui_mainwindowsql.h"

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
