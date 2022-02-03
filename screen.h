#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <ApplicationServices/ApplicationServices.h>
#include "virtualmouse.h"

class Screen : public QWidget
{
    Q_OBJECT

    QIcon m_ico;
    QPixmap m_pixmap;

    VirtualMouse* m_vmouse;

    bool m_vmouse_enabled = false;
    bool m_first;

    CGPoint m_center;

public:
    Screen(QWidget* parent = nullptr);
    ~Screen() { }

    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void enterEvent(QEvent* e) override;
    virtual void leaveEvent(QEvent* e) override;
    virtual void resizeEvent(QResizeEvent* e) override;
    virtual void paintEvent(QPaintEvent*) override;

};

#endif // SCREEN_H
