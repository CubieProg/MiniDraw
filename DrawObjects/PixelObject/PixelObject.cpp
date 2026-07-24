#include "PixelObject.h"
#include "../BaseDraw.h"
#include <QPainter>
#include <memory>

PixelObject::PixelObject() : BaseDraw("Растровый объект") {
    // name = std::string("Растровый объект");
}

PixelObject::PixelObject(QImage& image, QRect& boundingRect) : BaseDraw("Растровый объект") {

    surface = image.copy(boundingRect);
    this->boundingRect = boundingRect;
}

PixelObject::PixelObject(QImage& image, QPoint& atopLeft, QPoint& abottomRight) : BaseDraw("Растровый объект") {
    this->boundingRect = QRect(atopLeft, abottomRight);
    surface = image.copy(this->boundingRect);
}

void PixelObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}