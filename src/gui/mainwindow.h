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

private:
    QPushButton* startButton;
    QPushButton* stopButton;
    QLineEdit* portInput;
    QTextEdit* logView;
    Server* server;
};

#endif // MAINWINDOW_H