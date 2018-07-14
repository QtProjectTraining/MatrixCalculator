#ifndef DOUBLEFORM_H
#define DOUBLEFORM_H

#include <QWidget>
#include <Eigen>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include "mymatrix.h"

namespace Ui {
class DoubleForm;
}

class DoubleForm : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleForm(QWidget *parent = 0);
    ~DoubleForm();
    void setMat1(Eigen::MatrixXd);
    void setMat2(Eigen::MatrixXd);
    QString open();
    void transMatrixFromMain(Eigen::MatrixXd, QString);
    void Matrix_show(QString sign, Eigen::MatrixXd Matrix, QTextEdit*);
private slots:
    void on_matrix1_button_clicked();

    void on_matrix2_button_clicked();

private:
    Ui::DoubleForm *ui;
    Eigen::MatrixXd mat1;
    Eigen::MatrixXd mat2;
};

#endif // DOUBLEFORM_H
