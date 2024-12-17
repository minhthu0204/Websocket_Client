#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QObject>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>


class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);

signals:
    void closed();
private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
private:
    QWebSocket m_webSocket;
    bool m_debug;


};

#endif // ECHOCLIENT_H
