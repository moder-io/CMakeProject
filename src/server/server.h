#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);
    ~Server();

    bool start(int port);
    void stop();

signals:
    void logMessage(const QString& message);

private slots:
    void newConnection();

private:
    QTcpServer* tcpServer;
};

#endif // SERVER_H