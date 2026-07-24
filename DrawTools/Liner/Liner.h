//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_LINER_H
#define SIMPLE_WINDOW_LINER_H
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


#endif //SIMPLE_WINDOW_LINER_H
