#ifndef NUMBER_MATRIX_FORM_H
#define NUMBER_MATRIX_FORM_H

#include <QWidget>
#include <Eigen>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include "mymatrix.h"

namespace Ui {
class Number_Matrix_Form;
}

class Number_Matrix_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Number_Matrix_Form(QWidget *parent = 0);
    QString open();
    void setMat(Eigen::MatrixXd);
    void transMatrixFromMain(Eigen::MatrixXd, QString);
    void Matrix_show(QString sign, Eigen::MatrixXd Matrix, QTextEdit*);
    ~Number_Matrix_Form();

private slots:
    void on_matrix1_button_clicked();

private:
    Ui::Number_Matrix_Form *ui;
    Eigen::MatrixXd matrix;
};

#endif // NUMBER_MATRIX_FORM_H
