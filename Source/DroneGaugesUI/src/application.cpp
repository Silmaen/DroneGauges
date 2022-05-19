/**
 * @file application.cpp
 * @author damien.lachouette 
 * @date 17/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "application.h"

using namespace std::filesystem;

namespace dg::ui {
Application::Application(int argc, char** argv):
    QApplication(argc, argv) {

    // defines a dummy button
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
}

Application::~Application() {
}

}
