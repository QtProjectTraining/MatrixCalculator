#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <Eigen>
#include <QString>
#include "csv.h"
#include <iostream>

class MyMatrix
{
public:
    MyMatrix();
    static Eigen::MatrixXd fileToMatrix(QString);
    void Matrix_show(Eigen::MatrixXd);
};

#endif // MYMATRIX_H
