#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QFile>
#include <QDir>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);
    ~Server();

    bool start(int port, const QString& rootPath);
    void stop();

signals:
    void logMessage(const QString& message);

private slots:
    void newConnection();
    void readClient();

private:
    QTcpServer* tcpServer;
    QDir rootDir;

    void serveFile(QTcpSocket* socket, const QString& fileName);
};

#endif // SERVER_H