#include <QPainter>

#include "PixelObject.h"
#include "../BaseDraw.h"

#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/RectGizmo.h"

PixelObject::PixelObject() : BaseDraw("Растровый объект") {
    // name = std::string("Растровый объект");
}

PixelObject::PixelObject(QImage& image, QRect& boundingRect) : BaseDraw("Растровый объект") {

    surface = image.copy(boundingRect);
    this->boundingRect = boundingRect;

    gizmos.push_back(make_shared<RectGizmo>(boundingRect));

    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topRight()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomRight()));
}

PixelObject::PixelObject(QImage& image, QPoint& atopLeft, QPoint& abottomRight) : BaseDraw("Растровый объект") {
    this->boundingRect = QRect(atopLeft, abottomRight);
    surface = image.copy(this->boundingRect);


    gizmos.push_back(make_shared<RectGizmo>(boundingRect));

    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topRight()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomRight()));
}

void PixelObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}