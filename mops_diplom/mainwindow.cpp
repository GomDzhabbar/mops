#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gw = new GLW;
    gw->setBaseSize(600,600);
    gw->setMaximumSize(1000,1000);


    ui->verticalLayout->addWidget( gw );
}

MainWindow::~MainWindow()
{
    delete ui;
}
