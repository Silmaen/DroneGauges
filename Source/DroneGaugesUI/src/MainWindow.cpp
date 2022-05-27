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
    ui(new Ui::MainWindow),
    timer{std::make_shared<QTimer>(this)} {
    ui->setupUi(this);
    ui->statusbar->showMessage("Starting", 3);
    connect(timer.get(), &QTimer::timeout, this, QOverload<>::of(&MainWindow::timerTick));
    timer->setInterval(100);// 100 ms -> 10Hz
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ConnectPushed() {
}

void MainWindow::SendPushed() {
}

void MainWindow::timerTick() {
}

}// namespace dg::ui
