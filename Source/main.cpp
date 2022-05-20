
#include <QApplication>
#include <QCommandLineParser>
#include <filesystem>
#include "MainWindow.h"

using namespace dg::ui;
using namespace std::filesystem;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // retrieve the root path of the application
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);
    path rootPath= absolute(path(argv[0])).parent_path();

    MainWindow window;
    window.show();
    return app.exec();
}
