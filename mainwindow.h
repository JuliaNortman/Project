#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//protected:
    Ui::MainWindow *ui;
private slots:
    void on_quitButton_clicked();
};

#endif // MAINWINDOW_H
