#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _scene(this)
{
    ui->setupUi(this);

    //we set the size of the scene to the size of the QGraphicsView to simplify the coordinated system
    QRect viewContentsRect = ui->myGraphicsView->contentsRect();
    _scene.setSceneRect(viewContentsRect);
    ui->myGraphicsView->setScene(&_scene);

    //draw a rectangle at 20,20 (top-left coordinates)
    _scene.addRect(20,20,100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
