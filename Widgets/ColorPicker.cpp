//
// Created by spp16 on 21.07.2026.
//

#include <iostream>
#include "ColorPicker.h"
#include <QMouseEvent>
#include <QColorDialog>

ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent) {
    setCursor(Qt::PointingHandCursor);
}

void ColorPicker::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(2, 2,
        widgetSize, widgetSize,
        currentColor
    );
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {

        QColor newColor = QColorDialog::getColor(currentColor, this, "Выберите цвет");

        if (newColor.isValid()) {
            currentColor = newColor;

            emit colorChanged(currentColor);
            update();
        }
    }
}