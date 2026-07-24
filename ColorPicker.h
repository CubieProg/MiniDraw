//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_COLORPICKER_H
#define SIMPLE_WINDOW_COLORPICKER_H

#include <QWidget>
#include <QPainter>

class ColorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    QColor getCurrentColor() const { return currentColor; }

signals:
    void colorChanged(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QColor currentColor = Qt::gray;

    const int widgetSize = 20;
};


#endif //SIMPLE_WINDOW_COLORPICKER_H
