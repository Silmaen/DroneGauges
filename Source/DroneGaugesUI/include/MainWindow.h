/**
 * @file application.h
 * @author Silmean
 * @date 16/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once

#include <QMainWindow>

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
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructeur.
     * @param parent Le widget Parent.
     */
    explicit MainWindow(QWidget* parent = nullptr);
    /**
     * @brief Destructeur.
     */
    ~MainWindow() override;
private:
    /// Lien vers la page UI.
    Ui::MainWindow* ui;
};

}// namespace dg::ui
