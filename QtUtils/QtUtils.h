//
// Created by spp16 on 24.07.2026.
//

#ifndef MINIDRAW_QTUTILS_H
#define MINIDRAW_QTUTILS_H
#include <QRect>


namespace utils {
    void UpdateRect(QRect& rect, const QPoint& pos) {
        int width = rect.width();
        int height = rect.height();

        rect.setX(pos.x());
        rect.setY(pos.y());
        rect.setWidth(width);
        rect.setHeight(height);
    };
}

#endif //MINIDRAW_QTUTILS_H
