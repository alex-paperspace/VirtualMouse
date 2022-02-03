#include "screen.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QResizeEvent>

Screen::Screen(QWidget* parent) :
    QWidget(parent),
    m_ico(":/resources/cursor.png"),
    m_pixmap(m_ico.pixmap(QSize(42,65)))
{
    setMouseTracking(true);
    setCursor(Qt::BlankCursor);
    setStyleSheet(" background-color: green; ");

    m_vmouse = new VirtualMouse(m_pixmap, this);
    m_vmouse->setGeometry(0,0,1000, 1000); // realistically would be in a layout
}

void Screen::mouseMoveEvent(QMouseEvent *e)
{
    if (m_vmouse_enabled) {

        //get center information
        CGPoint cg_global_center_point;
        int centerX = width() / 2;
        int centerY = height() / 2;
        QPoint global_center_point = this->mapToGlobal(QPoint(centerX,centerY));
        cg_global_center_point.x = global_center_point.x();
        cg_global_center_point.y = global_center_point.y();

        if (m_first) {
            m_first = false;

            //move to center
            CGAssociateMouseAndMouseCursorPosition(false);
            CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, cg_global_center_point);
            CGAssociateMouseAndMouseCursorPosition(true);

            //get location of cursor at center to use as a reference for delta calculations
            CGEventRef event = CGEventCreate(NULL);
            m_center = CGEventGetLocation(event);
            CFRelease(event);

        } else {
            float deltaX;
            float deltaY;

            //get location of cursor
            CGEventRef event = CGEventCreate(NULL);
            CGPoint cursor = CGEventGetLocation(event);
            CFRelease(event);

            //calculate new location difference from center reference
            deltaX = cursor.x - m_center.x;
            deltaY = cursor.y - m_center.y;

            qDebug() << "updatePosition Deltas:" << deltaX << deltaY;

            //update Virtual Mouse pixmap location
            m_vmouse->updatePosition(deltaX, deltaY);

            //move back cursor to center
            CGAssociateMouseAndMouseCursorPosition(false);
            CGWarpMouseCursorPosition(cg_global_center_point);
            CGAssociateMouseAndMouseCursorPosition(true);
        }
    }
}

void Screen::enterEvent(QEvent *e)
{
    //qDebug() << "enter";
    m_vmouse_enabled = true;
    m_first = true;

}

void Screen::leaveEvent(QEvent *e)
{
    //qDebug() << "leave";
    m_vmouse_enabled = false;
}

void Screen::resizeEvent(QResizeEvent *e)
{
    //desired behavior for vmouse when window is resized?
    //don't have to worry about when both width and height go ^
    //when one of the dimensions is lower, we have to check:
    //is vmouse in bounds of new size?
    //if it is, do nothing
    //if it is not, adjust proportionally to the resize

    BoundBools bools = m_vmouse->checkCursor();
    if (bools.Xinside == false || bools.Yinside == false) {
        QResizeEvent* ev = static_cast<QResizeEvent*>(e);
        float Xratio = (float)(ev->size().width()) / (float)(ev->oldSize().width());
        float Yratio = (float)(ev->size().height()) / (float)(ev->oldSize().height());
        float deltaX = Xratio * m_vmouse->m_positionX - m_vmouse->m_positionX;
        float deltaY = Yratio * m_vmouse->m_positionY - m_vmouse->m_positionY;
        m_vmouse->updatePosition(deltaX, deltaY);
    }

    //we may need this in edge cases where the screen is resized without the cursor
    //triggering a leave event (an internal resize, how would this occur?)
    m_first = true;

}

void Screen::paintEvent(QPaintEvent*) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
