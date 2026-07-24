//
// Created by spp16 on 20.07.2026.
//

#include "MainWindow.h"

#include <iostream>
#include <qdialog.h>
#include <QInputDialog>

#include "CanvasWidget.h"
#include "ColorPicker.h"
#include "DrawObjects/DrawObjectsPool.h"


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
        ui->treeWidget->addTopLevelItem(item);
    });

    //
    // bool ok;
    // QString text = QInputDialog::getText(
    //     this,
    //     "Заголовок",
    //     "Введите значение:",
    //     QLineEdit::Normal,
    //     "",
    //     &ok
    // );
    //
    // if (ok && !text.isEmpty()) {
    //     // пользователь ввёл текст и нажал ОК
    // } else {
    //     // отмена или пустой ввод
    // }

}

MainWindow::~MainWindow()
{
    delete ui;
}
