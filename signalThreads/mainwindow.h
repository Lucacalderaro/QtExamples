#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <threadsmanagement.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ThreadsManagement *management;
};

#endif // MAINWINDOW_H
