#include <QPainter>
#include <QBuffer>

#include "PixelObject.h"

#include <iostream>
#include <rapidjson/stringbuffer.h>

#include "../BaseDraw.h"

#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/RectGizmo.h"

PixelObject::PixelObject() : BaseDraw("Pixel object") {

}

PixelObject::PixelObject(QImage& image, QRect& boundingRect, bool load) : BaseDraw("Pixel object") {
    type = DrawObjectType::PIXEL_OBJECT;

    if (load) {
        QRect copyRect = QRect(0, 0, boundingRect.width(), boundingRect.height());
        surface = image.copy(copyRect);
    } else {
        surface = image.copy(boundingRect);
    }

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
    buffer.close();


    QByteArray base64Data = byteArray.toBase64(QByteArray::Base64Encoding);

    auto json_text_value = rapidjson::Value(base64Data.constData(), base64Data.size(), allocator);
    temp.AddMember("Data", json_text_value, allocator);
    // -----------------------------------------------------------------

    return temp;
};

shared_ptr<PixelObject> PixelObject::FromJSON(const rapidjson::Value& json) {
    if (!json.HasMember("Data")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }

    if (!json.HasMember("Position") || json["Position"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("Size") || json["Size"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }


    QRect boundingRect = QRect(
        json["Position"][0].GetDouble(),
        json["Position"][1].GetDouble(),
        json["Size"][0].GetDouble(),
        json["Size"][1].GetDouble()
    );

    QByteArray base64Data(
        json["Data"].GetString(),
        json["Data"].GetStringLength()
    );

    auto rawImage = QByteArray::fromBase64Encoding(
        base64Data,
        QByteArray::Base64Option::OmitTrailingEquals
    );
    QImage img = QImage::fromData(rawImage.decoded);

    return make_shared<PixelObject>(img, boundingRect, true);
}