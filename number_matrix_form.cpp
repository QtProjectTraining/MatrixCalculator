#include "number_matrix_form.h"
#include "ui_number_matrix_form.h"

Number_Matrix_Form::Number_Matrix_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Number_Matrix_Form)
{
    ui->setupUi(this);
}

Number_Matrix_Form::~Number_Matrix_Form()
{
    delete ui;
}

void Number_Matrix_Form::setMat(Eigen::MatrixXd matrix) {
    this->matrix = matrix;
}

void Number_Matrix_Form::transMatrixFromMain(Eigen::MatrixXd matrix, QString fileName) {
    this->matrix = matrix;
    ui->matrix1_lineEdit->setText(fileName);
    this->Matrix_show("", this->matrix, ui->matrix1_textEdit);
}

/*
* 打开文件
*/
QString Number_Matrix_Form::open() {
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
    return NULL;
}

/*
 * 在文本框中显示矩阵
 */
 void Number_Matrix_Form::Matrix_show(QString sign, Eigen::MatrixXd Matrix, QTextEdit *edit)
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

void Number_Matrix_Form::on_matrix1_button_clicked()
{
    QString fileName = this->open();
    Eigen::MatrixXd mat = MyMatrix::fileToMatrix(fileName);
    this->setMat(mat);
    ui->matrix1_lineEdit->setText(fileName);
    this->Matrix_show("", this->matrix, ui->matrix1_textEdit);
}
