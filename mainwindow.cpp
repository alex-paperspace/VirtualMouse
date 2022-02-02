#include "mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_screen(new Screen(this))
{
    m_screen->show();

    QWidget* central_wgt = new QWidget;
    QHBoxLayout* lay = new QHBoxLayout(central_wgt);
    lay->addWidget(m_screen);
    setCentralWidget(central_wgt);

}

MainWindow::~MainWindow()
{
}

