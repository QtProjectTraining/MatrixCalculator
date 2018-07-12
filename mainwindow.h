#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <Eigen>
#include <iostream>
#include "csv.h"
#include <sstream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Matrix_show(Eigen::MatrixXd Matrix);
private slots:
    void on_open_action_triggered();

    void on_save_as_action_triggered();

    void on_transpose_action_triggered();

private:
    Ui::MainWindow *ui;
    QString openFileName;
    Eigen::MatrixXd mat;
    int m;
    int n;
};

#endif // MAINWINDOW_H
