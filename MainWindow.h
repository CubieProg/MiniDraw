//
// Created by spp16 on 20.07.2026.
//

#ifndef SIMPLE_WINDOW_MAINWINDOW_H
#define SIMPLE_WINDOW_MAINWINDOW_H


#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include "ToolBar.h"
#include "DrawTools/ToolsContainer.h"


#include "ui_mainwindow.h"

using namespace std;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // QPushButton* button;//("Нажми меня");
private:
    Ui::MainWindow *ui;
    ToolBar *m_leftToolbar;

    shared_ptr<ToolsContainer> toolsContainer;
    shared_ptr<DrawObjectsPool> objectsPool;
};

#endif //SIMPLE_WINDOW_MAINWINDOW_H
