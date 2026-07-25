//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_LINER_H
#define MINIDRAW_LINER_H
#include "../BaseTool.h"
#include "../../DrawObjects/LineObject/LineObject.h"


class Liner : public BaseTool {
public:
    Liner();
    ~Liner() = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;

private:
    vector<QPoint> points;
};


#endif //MINIDRAW_LINER_H
