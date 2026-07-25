//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_BASEDRAW_H
#define MINIDRAW_BASEDRAW_H

#include <qimage.h>
#include <QPoint>
#include <vector>
#include <memory>

#include "../Gizmos/BaseGizmo.h"

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

    void SetName(const string& _name){this->name = _name;};

    void SetPos(const QPoint& pos);

protected:
    string name;
    QImage surface;
    QRect boundingRect;

    vector<shared_ptr<BaseGizmo>> gizmos;
};


#endif //MINIDRAW_BASEDRAW_H
