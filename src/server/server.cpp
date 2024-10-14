#include "server.h"
#include <QTcpSocket>

Server::Server(QObject* parent) : QObject(parent), tcpServer(new QTcpServer(this)) {
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
}

Server::~Server() {
    stop();
}

bool Server::start(int port) {
    if (tcpServer->listen(QHostAddress::Any, port)) {
        emit logMessage("Servidor escuchando en el puerto " + QString::number(port));
        return true;
    }
    else {
        emit logMessage("No se pudo iniciar el servidor: " + tcpServer->errorString());
        return false;
    }
}

void Server::stop() {
    if (tcpServer->isListening()) {
        tcpServer->close();
        emit logMessage("Servidor detenido");
    }
}

void Server::newConnection() {
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, [this, clientSocket]() {
        QByteArray data = clientSocket->readAll();
        emit logMessage("Datos recibidos: " + QString(data));
        clientSocket->write("Mensaje recibido por el servidor");
        });
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    emit logMessage("Nueva conexión establecida");
}