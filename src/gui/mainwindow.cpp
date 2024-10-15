#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), server(new Server(this)) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* portLayout = new QHBoxLayout();
    portInput = new QLineEdit(this);
    portInput->setPlaceholderText("Port");
    portLayout->addWidget(new QLabel("Port:"));
    portLayout->addWidget(portInput);

    QHBoxLayout* folderLayout = new QHBoxLayout();
    folderInput = new QLineEdit(this);
    folderInput->setPlaceholderText("Server root folder");
    browseButton = new QPushButton("Browse", this);
    folderLayout->addWidget(new QLabel("Folder:"));
    folderLayout->addWidget(folderInput);
    folderLayout->addWidget(browseButton);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    startButton = new QPushButton("Start Server", this);
    stopButton = new QPushButton("Stop Server", this);
    stopButton->setEnabled(false);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);

    logView = new QTextEdit(this);
    logView->setReadOnly(true);

    mainLayout->addLayout(portLayout);
    mainLayout->addLayout(folderLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(logView);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startServer);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopServer);
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::browseFolder);
    connect(server, &Server::logMessage, this, &MainWindow::updateLog);

    setWindowTitle("HTTP Server");
    resize(400, 300);
}

MainWindow::~MainWindow() {
    delete server;
}

void MainWindow::startServer() {
    int port = portInput->text().toInt();
    QString rootPath = folderInput->text();

    if (port <= 0 || port > 65535) {
        QMessageBox::warning(this, "Invalid Port", "Please enter a valid port number (1-65535).");
        return;
    }

    if (rootPath.isEmpty()) {
        QMessageBox::warning(this, "Invalid Path", "Please select a server root folder.");
        return;
    }

    if (server->start(port, rootPath)) {
        startButton->setEnabled(false);
        stopButton->setEnabled(true);
        portInput->setEnabled(false);
        folderInput->setEnabled(false);
        browseButton->setEnabled(false);
    }
}

void MainWindow::stopServer() {
    server->stop();
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    portInput->setEnabled(true);
    folderInput->setEnabled(true);
    browseButton->setEnabled(true);
}

void MainWindow::updateLog(const QString& message) {
    logView->append(message);
}

void MainWindow::browseFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Server Root Folder",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        folderInput->setText(dir);
    }
}