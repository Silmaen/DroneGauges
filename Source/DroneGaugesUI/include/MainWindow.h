/**
 * @file application.h
 * @author Silmean
 * @date 16/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

/**
 * @brief User interface library
 */
namespace dg::ui {

/**
 * @brief Classe définissant les opérations de la page principale
 */
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructeur.
     * @param parent Le widget Parent.
     */
    explicit MainWindow(QWidget* parent= nullptr);
    /**
     * @brief Destructeur.
     */
    ~MainWindow() override;
public slots:
    /**
     * @brief Action on the connect button
     */
    void ConnectPushed();
    /**
     * @brief Action on the send button
     */
    void SendPushed();
    /**
     * @brief Action each timer tick.
     */
    void timerTick();

private:
    /// Lien vers la page UI.
    Ui::MainWindow* ui;
    /// The timer
    std::shared_ptr<QTimer> timer;
};

}// namespace dg::ui
