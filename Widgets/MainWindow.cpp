//
// Created by spp16 on 20.07.2026.
//

#include "MainWindow.h"

#include <iostream>
#include <qdialog.h>
#include <QInputDialog>

#include "CanvasWidget.h"
#include "ColorPicker.h"
#include "../DrawObjects/DrawObjectsPool.h"



// class MyData {
// public:
//     MyData(int value) : m_value(value) {}
//     int value() const { return m_value; }
// private:
//     int m_value;
// };
//
// // В функции, которая создаёт shared_ptr и передаёт её в setData
// void setItemData(QTreeWidgetItem* item, int column, std::shared_ptr<MyData> data) {
//     if (data) {
//         // Создаём QSharedPointer внутри QVariant
//         QSharedPointer<MyData> shared_data = std::move(data);
//         // Теперь можно получить сырой указатель на объект и передать в setData
//         item->setData(column, Qt::UserRole, QVariant::fromValue(shared_data));
//     } else {
//         // Обрабатываем случай, когда передача nullptr
//         item->setData(column, Qt::UserRole, QVariant());
//     }
// }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectsPool = make_shared<DrawObjectsPool>();
    toolsContainer = make_shared<ToolsContainer>();

    auto *colorPicker = qobject_cast<ColorPicker*>(ui->colorPicker);
    auto *canvas = qobject_cast<CanvasWidget*>(ui->drawing_area);

    ui->widthLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));

    canvas->init(objectsPool, toolsContainer);


    connect(colorPicker, &ColorPicker::colorChanged, this, [canvas](const QColor &color) {
        canvas->setColor(color);
    });

    connect(ui->widthLineEdit, &QLineEdit::editingFinished, this, [this, canvas]() {
        canvas->setWidth(ui->widthLineEdit->text().toInt());
    });

    //                          Выбор инструмента
    // ------------------------------------------------------------------------------------------------------

    connect(ui->bn_select_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::SelectTool);
    });

    connect(ui->bn_pencil_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::Pencil);
    });

    connect(ui->bn_liner, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::Liner);
    });

    connect(ui->bn_circle_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::CircleTool);
    });

    connect(ui->bn_rect_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::RectTool);
    });

    connect(ui->bn_arrow_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::ArrowTool);
    });

    connect(ui->bn_text_tool, &QPushButton::clicked, this, [this]() {
        toolsContainer->SetActiveTool(ToolType::TextTool);
    });

    // ------------------------------------------------------------------------------------------------------


    connect(canvas, &CanvasWidget::DrawObjectAdded, this, [this](std::shared_ptr<BaseDraw> obj) {
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList{QString::fromStdString(obj->GetName())});

        item->setData(POINTER_DATA_COLUMN, Qt::UserRole, QVariant::fromValue(obj));
        ui->treeWidget->addTopLevelItem(item);
    });

    connect(
        ui->treeWidget,
        &QTreeWidget::itemClicked,
        this,
        [this, canvas](QTreeWidgetItem *item, int column) {
            auto pointer = item->data(POINTER_DATA_COLUMN, Qt::UserRole).value<std::shared_ptr<BaseDraw>>();
            this->objectsPool->TrySelectObject(pointer);
            canvas->ForceRerender();
        });
}

MainWindow::~MainWindow()
{
    delete ui;
}
