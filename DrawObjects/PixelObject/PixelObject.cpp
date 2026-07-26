#include <QPainter>
#include <QBuffer>

#include "PixelObject.h"

#include <iostream>
#include <ostream>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "../BaseDraw.h"

#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/RectGizmo.h"

// PixelObject::PixelObject() : BaseDraw("Pixel object") {
//     // name = std::string("Растровый объект");
//     std::cout << "PixelObject base constructor" << std::endl;
//     type = DrawObjectType::PIXEL_OBJECT;
// }

PixelObject::PixelObject(QImage& image, QRect& boundingRect) : BaseDraw("Pixel object") {
    type = DrawObjectType::PIXEL_OBJECT;

    surface = image.copy(boundingRect);
    this->boundingRect = boundingRect;

    gizmos.push_back(make_shared<RectGizmo>(boundingRect));

    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topRight()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomRight()));
}

PixelObject::PixelObject(QImage& image, QPoint& atopLeft, QPoint& abottomRight) : BaseDraw("Pixel object") {
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

rapidjson::Value PixelObject::JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value temp(rapidjson::kObjectType);
    temp.AddMember("Type", "PixelObject", allocator);
    // temp.AddMember("data", "some data", allocator);

    // auto bounds = JSONBoundingRepr(allocator); // Какая-то странная херь не работает именно на PixelObject-е
    // rapidjson::Value* position = get<0>(bounds);
    // rapidjson::Value* size = get<1>(bounds);

    // Вставляем костыли и тихо радуемся
    // -----------------------------------------------------------------
    rapidjson::Value posArray(rapidjson::kArrayType);
    posArray.PushBack(boundingRect.x(), allocator);
    posArray.PushBack(boundingRect.y(), allocator);

    rapidjson::Value sizeArray(rapidjson::kArrayType);
    sizeArray.PushBack(boundingRect.width(), allocator);
    sizeArray.PushBack(boundingRect.height(), allocator);

    temp.AddMember("Position", posArray, allocator);
    temp.AddMember("Size", sizeArray, allocator);
    // -----------------------------------------------------------------

    // Сохраняем картинку
    // -----------------------------------------------------------------
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::ReadWrite);
    surface.save(&buffer, "PNG");

    QString str = QString::fromUtf8(byteArray);
    auto data_as_string = str.toStdString();
    auto json_text_value = rapidjson::Value(data_as_string.c_str(), data_as_string.size(), allocator);
    temp.AddMember("Data", json_text_value, allocator);
    // -----------------------------------------------------------------

    return temp;
};