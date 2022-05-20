/**
 * @file application.cpp
 * @author Silmean
 * @date 17/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "MainWindow.h"

// Les trucs de QT
#include <moc_MainWindow.cpp>
#include <ui/ui_MainWindow.h>

namespace dg::ui {

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->statusbar->showMessage("Starting", 3);
}

MainWindow::~MainWindow() {
    delete ui;
}

}// namespace dg::ui
