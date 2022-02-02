#include "screen.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

Screen::Screen(QWidget* parent) :
    QWidget(parent),
    m_ico(":/resources/cursor.png"),
    m_pixmap(m_ico.pixmap(QSize(42,65))),
    m_vmouse(m_pixmap)
{
    setMouseTracking(true);
    setCursor(m_vmouse);
    setStyleSheet(" background-color: green; ");

    tstbtn = new QPushButton("Click me", this);
    qDebug() << width() << height();
    tstbtn->setGeometry(200,200, 100,100);
    tstbtn->show();
}

void Screen::mouseMoveEvent(QMouseEvent *e)
{
    if (m_vmouse_enabled) {
        int centerX = width() / 2;
        int centerY = height() / 2;

        QPoint globalCenter = this->mapToGlobal(QPoint(centerX, centerY));
        QCursor::setPos(globalCenter);
        //this->cursor().setPos(globalCenter);
        qDebug() << this->cursor().pos();
    }
}

void Screen::enterEvent(QEvent *e)
{
    m_vmouse_enabled = true;

}

void Screen::leaveEvent(QEvent *e)
{
    m_vmouse_enabled = false;
}

void Screen::paintEvent(QPaintEvent*) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
