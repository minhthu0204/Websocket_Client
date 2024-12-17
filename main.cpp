#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "echoclient.h"

int main(int argc, char *argv[])
{
    using namespace Qt::Literals::StringLiterals;
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(
        QStringList{ u"d"_s, u"debug"_s },
        QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);

    // Set default hostname to 192.168.1.100
    QCommandLineOption hostnameOption(
        QStringList{ u"n"_s, u"hostname"_s },
        QCoreApplication::translate("main", "Hostname [default: 192.168.1.100]."), "hostname",
        "192.168.1.100"); // Default hostname
    parser.addOption(hostnameOption);

    // Set default port to 3335
    QCommandLineOption portOption(
        QStringList{ u"p"_s, u"port"_s },
        QCoreApplication::translate("main", "Port [default: 3335]."), "port",
        "3335"); // Default port
    parser.addOption(portOption);

    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    // Parse and validate port value
    bool ok = true;
    int port = parser.value(portOption).toInt(&ok);
    if (!ok || port < 1 || port > 65535) {
        qWarning("Port invalid, must be a number between 1 and 65535\n%s",
                 qPrintable(parser.helpText()));
        return 1;
    }

    // Set WebSocket server URL
    QUrl url;
    url.setScheme(u"ws"_s);
    url.setHost(parser.value(hostnameOption));
    url.setPort(port);

    EchoClient client(url, debug);
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
