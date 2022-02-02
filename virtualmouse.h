#ifndef VIRTUALMOUSE_H
#define VIRTUALMOUSE_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QIcon>

class VirtualMouse : public QObject {
    Q_OBJECT

    QPixmap m_pixmap;

public:
    VirtualMouse(QPixmap const& pixmap);
    ~VirtualMouse();
};

#endif // VIRTUALMOUSE_H
