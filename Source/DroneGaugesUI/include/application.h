/**
 * @file application.h
 * @author damien.lachouette 
 * @date 16/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once

#include <QApplication>
#include <QPushButton>
#include <filesystem>

/**
 * @brief User interface library
 */
namespace dg::ui {
class Application: public QApplication {
public:
    /**
     * @brief Constructor
     * @param argc Number of command line parameters
     * @param argv List of Command line parameters
     */
    Application(int argc, char** argv);
    /**
     * @brief Destructor
     */
    ~Application() override;
    /**
     * @brief Get the root path of the application
     * @return The root path of the application
     */
    std::filesystem::path getRootPath() const {return rootPath;}
private:
    /// The path to the application
    std::filesystem::path rootPath;
};

}// namespace dg::ui
