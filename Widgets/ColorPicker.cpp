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


        auto dialog = new QColorDialog();

        QPalette pal = dialog->palette();
        pal.setColor(QPalette::Window, Qt::white);                 // фон окна
        pal.setColor(QPalette::WindowText, Qt::black);              // текст
        pal.setColor(QPalette::Base, Qt::white);                    // фон полей ввода
        pal.setColor(QPalette::Text, Qt::black);                    // текст в полях
        pal.setColor(QPalette::Button, QColor(240, 240, 240));       // кнопки
        pal.setColor(QPalette::ButtonText, Qt::black);              // текст кнопок

        dialog->setPalette(pal);

        // QColor newColor = QColorDialog::getColor(currentColor, this, "Выберите цвет");
        QColor newColor = dialog->getColor();

        if (newColor.isValid()) {
            currentColor = newColor;

            emit colorChanged(currentColor);
            update();
        }
    }
}