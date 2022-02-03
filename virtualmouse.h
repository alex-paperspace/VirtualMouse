#ifndef VIRTUALMOUSE_H
#define VIRTUALMOUSE_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

struct BoundBools {
    bool Xinside = true;
    bool Yinside = true;
};

class VirtualMouse : public QWidget {
    Q_OBJECT

    QWidget* m_parent;
    QPixmap m_pixmap;

public:
    VirtualMouse(QPixmap const& pixmap, QWidget* parent = nullptr);
    ~VirtualMouse();

     virtual void paintEvent(QPaintEvent* e) override;

    float m_positionX = 0;
    float m_positionY = 0;

    BoundBools checkCursor();
    void updatePosition(float deltaX, float deltaY);

};

#endif // VIRTUALMOUSE_H
