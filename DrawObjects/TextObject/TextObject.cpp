//
// Created by spp16 on 21.07.2026.
//

#include "TextObject.h"

#include <qpainter.h>
#include <qpen.h>
#include <qstring.h>


TextObject::TextObject() : BaseDraw("Text object") {

};

TextObject::TextObject(QPen _pen, std::string _text, QPoint _pos) : BaseDraw("Text object") {
    text = _text;
    pen = _pen;
    pos = _pos;

    // const QRect mock_rect(QPoint(0, 0), QPoint(100, 100));
    // QImage mock_surface(mock_rect.size(), QImage::Format_ARGB32_Premultiplied);
    // QPainter mock_painter(&mock_surface);
    // mock_painter.setFont(QFont("Arial", pen.width()));
    // mock_painter.setPen(pen);
    //
    // boundingRect = mock_painter
    //     .boundingRect(
    //         mock_rect,
    //         Qt::TextWordWrap,
    //         QString::fromStdString(text));




    auto font_name = "Arial";

    QFont font(font_name, pen.width());
    QFontMetrics fm(font);
    int width = fm.horizontalAdvance(QString::fromStdString(text));
    int height = fm.height();
    int ascent = fm.ascent();
    int descent = fm.descent();


    boundingRect = QRect(pos.x(), pos.y(), width + pos.x()+2, height + pos.y()+1);

    surface = QImage(this->boundingRect.size(), QImage::Format_ARGB32_Premultiplied);
    surface.fill(Qt::transparent);

    QPainter painter(&surface);

    painter.setFont(QFont(font_name, pen.width()));
    painter.setPen(pen);

    painter.drawText(QPoint(1, ascent), QString::fromStdString(text));
}

void TextObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}