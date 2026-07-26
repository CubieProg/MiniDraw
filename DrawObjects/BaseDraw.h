//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_BASEDRAW_H
#define MINIDRAW_BASEDRAW_H

#include <qimage.h>
#include <QPoint>
#include <vector>
#include <memory>
#include <qpen.h>

#include "../Gizmos/BaseGizmo.h"
#include "rapidjson/document.h"

enum class DrawObjectType {
    PIXEL_OBJECT,
    LINE_OBJECT,
    CIRCLE_OBJECT,
    RECT_OBJECT,
    ARROW_OBJECT,
    TEXT_OBJECT
};

using namespace std;

class BaseDraw {
public:
    BaseDraw();
    BaseDraw(const string& name);
    virtual ~BaseDraw() = default;
    virtual void Draw(QPainter& painter) const = 0;
    void DrawGizmos(QPainter& painter) const;

    [[nodiscard]] string GetName() const {return name;};
    [[nodiscard]] QRect GetBoundingRect() const {return boundingRect;};
    [[nodiscard]] QPoint GetPosition() const;
    [[nodiscard]] DrawObjectType GetType() const {return type;};

    void SetName(const string& _name){this->name = _name;};
    void SetPos(const QPoint& pos);

    virtual rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const = 0;

protected:
    QPen pen;

    DrawObjectType type;

    string name;
    QImage surface;
    QRect boundingRect;

    vector<shared_ptr<BaseGizmo>> gizmos;


    rapidjson::Value JSONPenRepr(rapidjson::MemoryPoolAllocator<> allocator) const;
    std::tuple<rapidjson::Value*, rapidjson::Value*> JSONBoundingRepr(rapidjson::MemoryPoolAllocator<> allocator) const;
};


#endif //MINIDRAW_BASEDRAW_H
