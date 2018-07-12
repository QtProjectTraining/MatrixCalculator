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
    void Matrix_show(QString, Eigen::MatrixXd Matrix);
    bool matrix_is_exist();
    const QString ORIGIN = tr("原矩阵\n ");
    const QString RANK = tr("矩阵的秩\n");
    const QString DETERMINANT = tr("行列式的值\n");
    const QString TRANSPOSE = tr("转置\n");
    const QString INVERSE = tr("方阵的逆阵\n");
    const QString ADJOINT = tr("伴随阵\n");

private slots:
    void on_open_action_triggered();

    void on_save_as_action_triggered();

    void on_transpose_action_triggered();

    void on_determinant_action_triggered();

    void on_adjoint_action_triggered();

    void on_inverse_action_triggered();

    void on_matrix_rank_action_triggered();

private:
    Ui::MainWindow *ui;
    QString openFileName;
    Eigen::MatrixXd mat;
    int m;
    int n;
};

#endif // MAINWINDOW_H
