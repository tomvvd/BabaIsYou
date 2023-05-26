#include "endwindow.h"
#include "ui_endwindow.h"

EndWindow::EndWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndWindow)
{
    ui->setupUi(this);
}

EndWindow::~EndWindow()
{
    delete ui;
}
