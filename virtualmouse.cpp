#include "virtualmouse.h"
#include <QIcon>
#include <QPainter>

VirtualMouse::VirtualMouse(QPixmap const& pixmap) :
    QCursor(pixmap, 0, 0)
{


}
