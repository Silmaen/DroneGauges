
#include <QApplication>
#include <QCommandLineParser>
#include <filesystem>
#include "MainWindow.h"
#include <QFile>

using namespace dg::ui;
using namespace std::filesystem;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(DroneGauges);
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
