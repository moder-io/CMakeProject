#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "../server/server.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void startServer();
    void stopServer();
    void updateLog(const QString& message);
    void browseFolder();

private:
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* browseButton;
    QLineEdit* portInput;
    QLineEdit* folderInput;
    QTextEdit* logView;
    Server* server;
};

#endif // MAINWINDOW_H