#include "doubleform.h"
#include "ui_doubleform.h"

DoubleForm::DoubleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleForm)
{
    ui->setupUi(this);
}

DoubleForm::~DoubleForm()
{
    delete ui;
}

void DoubleForm::setMat1(Eigen::MatrixXd mat1) {
    this->mat1 = mat1;
}

void DoubleForm::setMat2(Eigen::MatrixXd mat2) {
    this->mat2 = mat2;
}

/*
* 打开文件
*/
QString DoubleForm::open() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("文件"), "", tr("text(*.txt;*.csv)"));
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Read file failed:&1").arg(file.errorString()));
            return NULL;
        }
        return fileName;
    }
}

/*
* Matrix1按钮点击事件
*/
void DoubleForm::on_matrix1_button_clicked()
{
    QString fileName = this->open();
    Eigen::MatrixXd mat1 = MyMatrix::fileToMatrix(fileName);
    this->setMat1(mat1);
    ui->matrix1_lineEdit->setText(fileName);
    this->Matrix_show("", this->mat1, ui->matrix1_textEdit);
}

/*
* Matrix2按钮点击事件
*/
void DoubleForm::on_matrix2_button_clicked()
{
    QString fileName = this->open();
    Eigen::MatrixXd mat2 = MyMatrix::fileToMatrix(fileName);
    this->setMat2(mat2);
    ui->matrix2_lineEdit->setText(fileName);
    this->Matrix_show("", this->mat2, ui->matrix2_textEdit);
}

/*
* 将Main页面的矩阵传给四则计算页面
*/
void DoubleForm::transMatrixFromMain(Eigen::MatrixXd matrix, QString fileName) {
    this->mat1 = matrix;
    ui->matrix1_lineEdit->setText(fileName);
    this->Matrix_show("", this->mat1, ui->matrix1_textEdit);
}

/*
 * 在文本框中显示矩阵
 */
 void DoubleForm::Matrix_show(QString sign, Eigen::MatrixXd Matrix, QTextEdit *edit)
 {
     QString disPlayString;
     for (int i=0 ;i<Matrix.rows(); i++) {
         for (int j=0; j<Matrix.cols(); j++) {
             disPlayString.append(QString::number(Matrix(i, j)) + " ");
             if (j == Matrix.cols() - 1) {
                 disPlayString.append("\n");
             }
         }
     }
     edit->setText(sign + disPlayString);
 }
//矩阵相加
void DoubleForm::on_add_button_clicked()
{
    if((mat1.cols() == mat2.cols())&&(mat2.rows() == mat1.rows()))
      this->Matrix_show("", this->mat1+mat2, ui->matrix_result_textEdit);
    else
      QMessageBox::warning(this, tr("Warning"), tr("Two matrices cannot be added!"));

}
//矩阵相减
void DoubleForm::on_minus_button_clicked()
{
    if((mat1.cols() == mat2.cols())&&(mat2.rows() == mat1.rows()))
         this->Matrix_show("", this->mat1-mat2, ui->matrix_result_textEdit);
    else
         QMessageBox::warning(this, tr("Warning"), tr("Two matrices cannot be subtracted!"));
}
//矩阵相乘
void DoubleForm::on_multiply_button_clicked()
{
    if((mat1.cols() == mat2.rows())&&(mat2.cols() == mat1.rows()))
        this->Matrix_show("", this->mat1*mat2, ui->matrix_result_textEdit);
    else
        QMessageBox::warning(this, tr("Warning"), tr("Two matrices cannot be multiplied!"));
}
//矩阵相除
void DoubleForm::on_division_button_clicked()
{
    if((mat2.cols() == mat2.rows()) && (mat2.determinant()!=0)&& mat2.cols() && mat2.rows())
       this->Matrix_show("", this->mat1*mat2.inverse(), ui->matrix_result_textEdit);
    else
       QMessageBox::warning(this, tr("Warning"), tr("Two matrices cannot be eliminated!"));
}
