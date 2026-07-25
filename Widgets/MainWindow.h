//
// Created by spp16 on 20.07.2026.
//

#ifndef MINIDRAW_MAINWINDOW_H
#define MINIDRAW_MAINWINDOW_H

#include "../ToolBar.h"
#include "../DrawTools/ToolsContainer.h"


#include "ui_mainwindow.h"

using namespace std;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const int POINTER_DATA_COLUMN = 0;

    Ui::MainWindow *ui;
    ToolBar *m_leftToolbar;

    shared_ptr<ToolsContainer> toolsContainer;
    shared_ptr<DrawObjectsPool> objectsPool;
};

#endif //MINIDRAW_MAINWINDOW_H
