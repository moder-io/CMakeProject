#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), server(nullptr) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    startButton = new QPushButton("Iniciar Servidor", this);
    stopButton = new QPushButton("Detener Servidor", this);
    portInput = new QLineEdit(this);
    portInput->setPlaceholderText("Puerto");

    controlLayout->addWidget(new QLabel("Puerto:"));
    controlLayout->addWidget(portInput);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(stopButton);

    logView = new QTextEdit(this);
    logView->setReadOnly(true);

    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(logView);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startServer);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopServer);

    stopButton->setEnabled(false);

    resize(400, 300);
}

MainWindow::~MainWindow() {
    delete server;
}

void MainWindow::startServer() {
    int port = portInput->text().toInt();
    if (port <= 0 || port > 65535) {
        updateLog("Puerto inválido. Debe estar entre 1 y 65535.");
        return;
    }

    server = new Server(this);
    connect(server, &Server::logMessage, this, &MainWindow::updateLog);

    if (server->start(port)) {
        updateLog("Servidor iniciado en el puerto " + QString::number(port));
        startButton->setEnabled(false);
        stopButton->setEnabled(true);
        portInput->setEnabled(false);
    }
    else {
        updateLog("No se pudo iniciar el servidor en el puerto " + QString::number(port));
        delete server;
        server = nullptr;
    }
}

void MainWindow::stopServer() {
    if (server) {
        server->stop();
        updateLog("Servidor detenido");
        delete server;
        server = nullptr;
    }
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    portInput->setEnabled(true);
}

void MainWindow::updateLog(const QString& message) {
    logView->append(message);
}