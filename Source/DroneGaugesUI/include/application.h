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

namespace dg {
	class Application : public QApplication {
	public:
		Application(int argc, char **argv) : QApplication(argc, argv) {
			QPushButton button("Hello world!", nullptr);
			button.resize(200, 100);
			button.show();
		}
		~Application() override = default;
	};
}// namespace dg
