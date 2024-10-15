#include "server.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QDateTime>
#include <QRegularExpression>


Server::Server(QObject* parent) : QObject(parent), tcpServer(new QTcpServer(this)) {
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
}

Server::~Server() {
    stop();
}

bool Server::start(int port, const QString& rootPath) {
    rootDir = QDir(rootPath);
    if (!rootDir.exists()) {
        emit logMessage("Error: Root directory does not exist.");
        return false;
    }

    if (!tcpServer->listen(QHostAddress::Any, port)) {
        emit logMessage("Error: Could not start server.");
        return false;
    }

    emit logMessage(QString("Server started on port %1").arg(port));
    return true;
}

void Server::stop() {
    if (tcpServer->isListening()) {
        tcpServer->close();
        emit logMessage("Server stopped.");
    }
}

void Server::newConnection() {
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void Server::readClient() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket == nullptr) return;

    QTextStream in(socket);
    QString request = in.readLine();

    QStringList tokens = request.split(QRegularExpression("[ \r\n][ \r\n]*"));
    if (tokens[0] == "GET") {
        QString fileName = tokens[1];
        if (fileName == "/")
            fileName = "/index.html";

        serveFile(socket, fileName);
    }

    socket->close();
    if (socket->state() == QTcpSocket::UnconnectedState)
        socket->deleteLater();
}

void Server::serveFile(QTcpSocket* socket, const QString& fileName) {
    QString filePath = rootDir.filePath(fileName.mid(1)); // Remove leading '/'
    QFile file(filePath);

    if (!file.exists()) {
        // Serve 404
        QString response = "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>\n";
        socket->write(response.toUtf8());
        emit logMessage(QString("404 Not Found: %1").arg(fileName));
    }
    else if (file.open(QIODevice::ReadOnly)) {
        // Serve file content
        QByteArray content = file.readAll();
        QString response = QString("HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %1\r\n\r\n").arg(content.size());
        socket->write(response.toUtf8());
        socket->write(content);
        emit logMessage(QString("Served: %1").arg(fileName));
    }
    else {
        // Serve 403 Forbidden
        QString response = "HTTP/1.1 403 Forbidden\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<html><body><h1>403 Forbidden</h1></body></html>\n";
        socket->write(response.toUtf8());
        emit logMessage(QString("403 Forbidden: %1").arg(fileName));
    }
}