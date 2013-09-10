#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include "Videotron.hpp"

#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);

    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    new Videotron(&app);

    // Enter the application main event loop.
    return Application::exec();
}
