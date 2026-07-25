//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_CANVASWIDGET_H
#define MINIDRAW_CANVASWIDGET_H

#include <QWidget>
#include <QPainter>

#include "../DrawObjects/DrawObjectsPool.h"
#include "../DrawTools/ToolsContainer.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    // void setObjectsPool(const std::shared_ptr<DrawObjectsPool> objectsPool);

    void init(
        const shared_ptr<DrawObjectsPool> objectsPool,
        const shared_ptr<ToolsContainer> toolsContainer
    );


    void setColor(const QColor &color) {
        toolsContainer->SetPaintColor(color);
        currentColor = color;
    }
    void setWidth(float width) {
        toolsContainer->SetPaintWidth(width);
        this->paintWidth = width;
    }

    void ForceRerender();

signals:
    void DrawObjectAdded(shared_ptr<BaseDraw> obj);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


private:
    void updateBounds(const QPoint& mousePoint);
    void setBounds(const QPoint& mousePoint);
    void commitNewObject();

    tuple<bool, QString> TextInputWindow();

    shared_ptr<ToolsContainer> toolsContainer;
    shared_ptr<DrawObjectsPool> objectsPool;

    QImage renderSurface;
    QImage preRenderSurface;

    QColor currentColor = Qt::gray;

    bool drawing = false;

    QPoint cursorPos;

    QPoint lastPoint;
    QPoint startPoint;

    float paintWidth = 12;

    QPoint minDrawCoords;
    QPoint maxDrawCoords;
};

#endif //MINIDRAW_CANVASWIDGET_H
