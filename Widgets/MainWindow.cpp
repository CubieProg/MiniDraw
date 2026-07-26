//
// Created by spp16 on 20.07.2026.
//

#include "MainWindow.h"

#include <QFileDialog>
#include <QString>
#include <iostream>
#include <qdialog.h>
#include <QInputDialog>

#include "CanvasWidget.h"
#include "ColorPicker.h"
#include "../DrawObjects/DrawObjectsPool.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include <iostream>
#include <rapidjson/istreamwrapper.h>

#include "../DrawObjects/PixelObject/PixelObject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    objectsPool = make_shared<DrawObjectsPool>();
    toolsContainer = make_shared<ToolsContainer>();

    auto *colorPicker = qobject_cast<ColorPicker*>(ui->colorPicker);
    canvas = qobject_cast<CanvasWidget*>(ui->drawing_area);

    ui->widthLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));

    canvas->init(objectsPool, toolsContainer);


    connect(colorPicker, &ColorPicker::colorChanged, this, [this](const QColor &color) {
        canvas->setColor(color);
    });

    connect(ui->widthLineEdit, &QLineEdit::editingFinished, this, [this]() {
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

    //                          Кнопки сохранения/открытия
    // ------------------------------------------------------------------------------------------------------
    connect(ui->bn_save, &QPushButton::clicked, this, [this]() {
        if (fileName == nullptr) { SaveAs(); return; }



    });

    connect(ui->bn_save_as, &QPushButton::clicked, this, [this]() {
        auto file_path = SaveAs();

        if (fileName == nullptr) {
            fileName = make_shared<string>(file_path);
        } else {
            *fileName = file_path;
        }

        bool res = SaveFile();
    });

    connect(ui->bn_open, &QPushButton::clicked, this, [this]() {
        OpenFile();
    });
    // ------------------------------------------------------------------------------------------------------

    //                          Реакция на добавление объекта
    // ------------------------------------------------------------------------------------------------------
    connect(canvas, &CanvasWidget::DrawObjectAdded, this, [this](shared_ptr<BaseDraw> obj) {
        // auto item = new QTreeWidgetItem(QStringList{QString::fromStdString(obj->GetName())});
        //
        // item->setData(POINTER_DATA_COLUMN, Qt::UserRole, QVariant::fromValue(obj));
        // ui->treeWidget->addTopLevelItem(item);
        AddTreeWidgetItem(obj);
    });

    connect(
        ui->treeWidget,
        &QTreeWidget::itemClicked,
        this,
        [this](QTreeWidgetItem *item, int column) {
            auto pointer = item->data(POINTER_DATA_COLUMN, Qt::UserRole).value<std::shared_ptr<BaseDraw>>();
            objectsPool->TrySelectObject(pointer);
            canvas->ForceRerender();
        });
    // ------------------------------------------------------------------------------------------------------


    //                          Заполняем алиасы
    // ------------------------------------------------------------------------------------------------------
    saveFormatAliases.insert({
        {"png", SaveFormat::PNG},
        {"mdrw", SaveFormat::MDRW}
    });
    // ------------------------------------------------------------------------------------------------------


    // objectsPool->LoadMDRW(nullptr);

    OpenMDRW("C:/Users/spp16/CLionProjects/MiniDraw/TestImages/testPixelObj.mdrw");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ClearTreeWidget() {
    ui->treeWidget->clear();
};

void MainWindow::AddTreeWidgetItem(shared_ptr<BaseDraw> obj) {
    auto item = new QTreeWidgetItem(QStringList{QString::fromStdString(obj->GetName())});

    item->setData(POINTER_DATA_COLUMN, Qt::UserRole, QVariant::fromValue(obj));
    ui->treeWidget->addTopLevelItem(item);
};


string MainWindow::SaveAs() {
    QString saveFileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        QDir::currentPath(),
        "MiniDraw format (*.mdrw);;PNG image (*.png)"
    );

    return saveFileName.toStdString();
}

bool MainWindow::SavePNG() const {
    if (fileName == nullptr) { return false; }

    return canvas->GetImage().save(QString::fromStdString(*fileName), "PNG", 100);
}

bool MainWindow::SaveMDRW() const {
    auto doc = objectsPool->GenerateJSON();


    // Convert Document to a JSON string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    // Write the JSON string to a file
    std::ofstream ofs(*fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing!" << std::endl;
        return false;
    }

    ofs << buffer.GetString();
    ofs.close();
}

bool MainWindow::SaveFile() const {
    if (fileName == nullptr) { return false; }

    // Ищем формат файла
    // -------------------------------------------------------
    char point_delimiter = '.';
    std::istringstream iss(*fileName);
    string format;
    while (std::getline(iss, format, point_delimiter)) { }
    // -------------------------------------------------------

    // Сравниваем формат в алиасе
    // -------------------------------------------------------
    auto it = saveFormatAliases.find(format);

    if (it == saveFormatAliases.end()) {
        return false;
    }
    // -------------------------------------------------------

    auto saveFormat = saveFormatAliases.at(format);

    switch (saveFormat) {
        case SaveFormat::PNG:
            return SavePNG();
            break;
        case SaveFormat::MDRW:
            return SaveMDRW();
            break;
    }

    return true;
}




string MainWindow::OpenFile() {
    QString openFileName = QFileDialog::getOpenFileName(
        this, // родительский виджет
        "Открыть файл", // заголовок окна
        QDir::currentPath(),
        "Images (*.png *.mdrw)"
    );

    if (openFileName.isEmpty()) {
        std::cout << "Error" << std::endl;
        return nullptr;
    }

    auto filePath = openFileName.toStdString();

    // Ищем формат файла
    // -------------------------------------------------------
    char point_delimiter = '.';
    std::istringstream iss(filePath);
    string format;
    while (std::getline(iss, format, point_delimiter)) { }
    // -------------------------------------------------------

    // Сравниваем формат в алиасе
    // -------------------------------------------------------
    auto it = saveFormatAliases.find(format);

    if (it == saveFormatAliases.end()) {
        return nullptr;
    }
    // -------------------------------------------------------

    auto openFormat = saveFormatAliases.at(format);


    switch (openFormat) {
        case SaveFormat::PNG:
            OpenPNG(filePath);
            break;

        case SaveFormat::MDRW:
            OpenMDRW(filePath);
            break;
    }

    return filePath;
}



void MainWindow::OpenPNG(const string& filePath) {
    // if (filePath == nullptr) { return; }
    QImage load_image(QString::fromStdString(filePath));
    objectsPool->Clear();
    ClearTreeWidget();

    auto imageRect = load_image.rect();
    auto imageDrawObject = make_shared<PixelObject>(load_image, imageRect);
    objectsPool->AddItem(imageDrawObject);
    AddTreeWidgetItem(imageDrawObject);

    canvas->ForceRerender();
};

void MainWindow::OpenMDRW(const string& filePath) {
    // if (fileName == nullptr) { return; }
    objectsPool->Clear();
    ClearTreeWidget();

    std::ifstream ifs(filePath); //"C:/Users/spp16/CLionProjects/MiniDraw/TestImages/test_json.json"
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    if (doc.HasParseError()) {
        std::cerr << "Parse error: " << doc.GetParseError() << std::endl;
        canvas->ForceRerender();
        return;
    }

    objectsPool->LoadMDRW(doc);

    // AddTreeWidgetItem(imageDrawObject);
    canvas->ForceRerender();
};