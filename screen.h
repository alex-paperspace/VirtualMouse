#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPushButton>
#include "virtualmouse.h"

class Screen : public QWidget
{
    Q_OBJECT

    QIcon m_ico;
    QPixmap m_pixmap;
    VirtualMouse m_vmouse;

    bool m_vmouse_enabled = false;

    QPushButton* tstbtn;

public:
    Screen(QWidget* parent = nullptr);

    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void enterEvent(QEvent* e) override;
    virtual void leaveEvent(QEvent* e) override;

    virtual void paintEvent(QPaintEvent*) override;
};

#endif // SCREEN_H
