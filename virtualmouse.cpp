#include "virtualmouse.h"
#include <QPainter>
#include <QDebug>

VirtualMouse::VirtualMouse(QPixmap const& pixmap, QWidget* parent) :
    QWidget(parent),
    m_parent(parent),
    m_pixmap(pixmap)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void VirtualMouse::updatePosition(float deltaX, float deltaY) {
    m_positionX += deltaX;
    m_positionY += deltaY;
    BoundBools bools = checkCursor();
    if (bools.Xinside == false) {
        //revert
        m_positionX -= deltaX;
    }

    if (bools.Yinside == false) {
        //revert
        m_positionY -= deltaY;
    }

    update();

    qDebug() << "position" << m_positionX << m_positionY;

}

void VirtualMouse::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect original_rect = m_pixmap.rect();
    QRectF target_Rect(QRectF(m_positionX, m_positionY, original_rect.width(), original_rect.height()));
    p.drawPixmap(target_Rect, m_pixmap, original_rect);
}

BoundBools VirtualMouse::checkCursor()
{
    BoundBools obj;
    if (m_positionX < 0 || m_positionX > m_parent->width()) {
        obj.Xinside = false;
    }

    if (m_positionY < 0 || m_positionY > m_parent->height()) {
        obj.Yinside = false;
    }

    return obj;
}

VirtualMouse::~VirtualMouse() {
}




