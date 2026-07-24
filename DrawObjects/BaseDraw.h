//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_BASEDRAW_H
#define SIMPLE_WINDOW_BASEDRAW_H

#include <qimage.h>
#include <QPoint>

class BaseDraw {
public:
    BaseDraw();
    BaseDraw(const std::string& name);
    virtual ~BaseDraw() = default;
    virtual void Draw(QPainter& painter) const = 0;

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] QRect GetBoundingRect() const;

    void SetName(const std::string& name);

protected:
    std::string name;
    QImage surface;
    QRect boundingRect;
};


#endif //SIMPLE_WINDOW_BASEDRAW_H
