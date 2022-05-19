
#include "application.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // retrieve the root path of the application
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);
    std::filesystem::path rootPath= absolute(std::filesystem::path(argv[0])).parent_path();

    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
