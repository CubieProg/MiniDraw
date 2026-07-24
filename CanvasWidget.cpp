#include <iostream>
#include <QMouseEvent>

#include "CanvasWidget.h"

#include <QInputDialog>
#include <QLineEdit>

#include "ColorPicker.h"
#include "DrawObjects/LineObject/LineObject.h"

#include "DrawObjects/PixelObject/PixelObject.h"
#include "DrawTools/TextTool/TextTool.h"
#include "DrawTools/SelectTool/SelectTool.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent),
    renderSurface(1920, 1080, QImage::Format_ARGB32_Premultiplied),
    preRenderSurface(1920, 1080, QImage::Format_ARGB32_Premultiplied)
{
    renderSurface.fill(Qt::white);
    preRenderSurface.fill(Qt::transparent);
}

void CanvasWidget::init(
    const shared_ptr<DrawObjectsPool> _objectsPool,
    const shared_ptr<ToolsContainer> _toolsContainer
) {
    objectsPool = _objectsPool;
    toolsContainer = _toolsContainer;

    toolsContainer->SetActiveTool(ToolType::Pencil);

    toolsContainer->init(paintWidth, currentColor, &preRenderSurface);
}



void CanvasWidget::setBounds(const QPoint& mousePoint) {
    minDrawCoords.setX(mousePoint.x() - paintWidth);
    minDrawCoords.setY(mousePoint.y() - paintWidth);

    maxDrawCoords.setX(mousePoint.x() + paintWidth);
    maxDrawCoords.setY(mousePoint.y() + paintWidth);
}

void CanvasWidget::updateBounds(const QPoint& mousePoint) {
    if (mousePoint.x() - paintWidth < minDrawCoords.x()) minDrawCoords.setX(mousePoint.x() - paintWidth);
    if (mousePoint.y() - paintWidth < minDrawCoords.y()) minDrawCoords.setY(mousePoint.y() - paintWidth);

    if (mousePoint.x() + paintWidth > maxDrawCoords.x()) maxDrawCoords.setX(mousePoint.x() + paintWidth);
    if (mousePoint.y() + paintWidth > maxDrawCoords.y()) maxDrawCoords.setY(mousePoint.y() + paintWidth);
}

tuple<bool, QString> CanvasWidget::TextInputWindow() {
    bool ok;
    QString text = QInputDialog::getText(
        this,
        "",
        "Введите текст",
        QLineEdit::Normal,
        "",
        &ok
    );

    return make_tuple(ok, text);
}



void CanvasWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(0, 0, renderSurface);

    auto state = toolsContainer->GetActiveTool()->GetState();
    if (state == ToolState::ACTIVE) painter.drawImage(0, 0, preRenderSurface);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    auto message = toolsContainer->GetActiveTool()->OnPress(event);
    auto activeTool = toolsContainer->GetActiveTool();

    if (message == ToolMessage::ENTER){
        if (activeTool->GetToolType() == ToolType::TextTool) {
            auto text_tool_ptr = std::static_pointer_cast<TextTool>(activeTool);

            auto res = TextInputWindow();

            message = text_tool_ptr->ProcessModalResponse(get<0>(res), get<1>(res));
        }

        if (activeTool->GetToolType() == ToolType::SelectTool) {
            objectsPool->Select(event->pos());

            // Если выбрана выделялка и был выбран объект, то ловим его.
            if (objectsPool->GetSelectedObject() != nullptr) {
                auto object_pos = objectsPool->GetSelectedObject()->GetPosition();
                auto select_tool_ptr = std::static_pointer_cast<SelectTool>(activeTool);
                select_tool_ptr->SetCatchDelta(object_pos);
            }

            // Перерисовываем под гизмосы
            QPainter painter(&renderSurface);
            painter.setRenderHint(QPainter::Antialiasing);
            renderSurface.fill(Qt::white);
            objectsPool->Draw(painter);
        }

        setBounds(event->pos());
        update();
    }

    if (message == ToolMessage::CONTINUE) {
        updateBounds(event->pos());
        update();
    }

    if (message == ToolMessage::QUIT) {

        if (activeTool->GetToolType() == ToolType::SelectTool) {
            objectsPool->Deselect();

            // Перерисовываем под гизмосы
            QPainter painter(&renderSurface);
            painter.setRenderHint(QPainter::Antialiasing);
            renderSurface.fill(Qt::white);
            objectsPool->Draw(painter);
        }

        commitNewObject();
        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    auto message = toolsContainer->GetActiveTool()->OnRelease(event);

    if (message == ToolMessage::QUIT) {
        commitNewObject();
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    auto activeTool = toolsContainer->GetActiveTool();
    auto state = activeTool->GetState();

    activeTool->OnMove(event);

    if (state == ToolState::ACTIVE) {


        if (activeTool->GetToolType() == ToolType::SelectTool) {
            // Если выбрана выделялка то двигаем объект
            QPainter painter(&renderSurface);
            painter.setRenderHint(QPainter::Antialiasing);
            preRenderSurface.fill(Qt::transparent);
            renderSurface.fill(Qt::white);

            auto select_tool_ptr = std::static_pointer_cast<SelectTool>(activeTool);

            objectsPool->UpdateSelectedObject(event->pos() - select_tool_ptr->GetCatchDelta());
            objectsPool->Draw(painter);
            update();
        }

        updateBounds(event->pos());
        update();
    };
}



void CanvasWidget::commitNewObject() {
    QPainter painter(&renderSurface);
    painter.setRenderHint(QPainter::Antialiasing);

    auto new_object = toolsContainer->GetActiveTool()->ProduceDrawObject(preRenderSurface, minDrawCoords, maxDrawCoords);

    if (new_object == nullptr) {return;}
    objectsPool->AddItem(new_object);

    emit DrawObjectAdded(new_object);

    preRenderSurface.fill(Qt::transparent);
    renderSurface.fill(Qt::white);
    objectsPool->Draw(painter);

    update();
}