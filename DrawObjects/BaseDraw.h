//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_BASEDRAW_H
#define SIMPLE_WINDOW_BASEDRAW_H

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

    [[nodiscard]] string GetName() const;
    [[nodiscard]] QRect GetBoundingRect() const;

    void SetName(const string& name);

protected:
    string name;
    QImage surface;
    QRect boundingRect;

    vector<shared_ptr<BaseGizmo>> gizmos;
};


#endif //SIMPLE_WINDOW_BASEDRAW_H
