#include "mymatrix.h"

MyMatrix::MyMatrix()
{

}

/*
* 文件转成矩阵对象
*/
Eigen::MatrixXd MyMatrix::fileToMatrix(QString fileName) {
    CSVParser csvp(QString(","));
    QList<QStringList> lines;
    std::string str;
    const char* s = new char();
    lines = csvp.read(fileName);
    int row = lines.size();
    int col = lines[0].size();

    Eigen::MatrixXd mat(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            str = lines[i][j].toStdString();
            s = str.data();
            mat(i,j) = atof(s);
        }
    }
    return mat;
}
