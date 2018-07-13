#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<Eigen>
#include "csv.h"
using namespace Eigen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
* 打开文件
*/
void MainWindow::on_open_action_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("文件"), "", tr("text(*.txt;*.csv)"));
    this->openFileName = fileName;
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Read file failed:&1").arg(file.errorString()));
            return;
        }
        CSVParser csvp(QString(","));
        QList<QStringList> lines;
        std::string str;
        const char* s = new char();
        lines = csvp.read(fileName);
        m = lines.size();
        n = lines[0].size();

        MatrixXd mat(m, n);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                str = lines[i][j].toStdString();
                s = str.data();
                mat(i,j) = atof(s);
            }
        }
        this->mat = mat;
        Matrix_show(this->ORIGIN, this->mat);
        this->matrixAttribute();
    }
}

/*
* 另存为
*/
void MainWindow::on_save_as_action_triggered()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,
                       tr("Open file"), this->openFileName, tr("Text File(*.txt;*.csv)"));
    if (fileName.trimmed() == "") {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("打开文件失败"), QMessageBox::Ok);
        return;
    }
    QTextStream textStream(&file);
    QString str = ui->matrix_show_textedit->toPlainText();
    textStream << str;
    QMessageBox::warning(this, tr("提示"), tr("保存文件成功"));
    file.close();
}
/*
* 获取矩阵属性
*/
void MainWindow::matrixAttribute()
{
    if (m == n)
        ui->is_phalanx_label->setText(PHALANX);
    else
        ui->is_phalanx_label->setText(NOT+PHALANX);
    k = 0;
    notDiagonalMatrix = 0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
        {
            if (mat(i,j) == mat(j,i))
                k++;
            if ((i != j) && (mat(i,j) != 0))
                notDiagonalMatrix = 1;
        }
    }
    if (k == m*n)
        ui->is_symmetric_label->setText(SYMMETRIC);
    else
        ui->is_symmetric_label->setText(NOT+SYMMETRIC);
    if (notDiagonalMatrix)
    {
        ui->is_diagonal_label->setText(NOT+DIAGONAL);
        for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            {
                if (mat(i,j) == 0)
                    zero++;
            }
        if ((m*n - zero) / m*n <= 0.05)
             ui->is_sparse_label->setText(SPARSE);
        else
            ui->is_sparse_label->setText(NOT+SPARSE);
    }
    else
    {
          ui->is_diagonal_label->setText(DIAGONAL);
          ui->is_sparse_label->setText(NOT+SPARSE);
    }
}

/*
* 转置
*/
void MainWindow::on_transpose_action_triggered()
{
    if(!this->matrix_is_exist()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please open a file first!"));
        return;
    }
    this->Matrix_show(this->TRANSPOSE, this->mat.transpose());
}

/*
 * 在文本框中显示矩阵
 */
 void MainWindow::Matrix_show(QString sign, Eigen::MatrixXd Matrix)
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
     ui->matrix_show_textedit->append(sign + disPlayString);
 }

/*
* 行列式的值
*/
void MainWindow::on_determinant_action_triggered()
{
    if(!this->matrix_is_exist()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please open a file first!"));
        return;
    }
    QString tempStr;
    ui->matrix_show_textedit->append(this->DETERMINANT + tempStr.setNum(mat.determinant()));
}

/*
* 伴随阵
*/
void MainWindow::on_adjoint_action_triggered()
{

    if(!this->matrix_is_exist()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please open a file first!"));
        return;
    }
    Matrix_show(this->ADJOINT, this->mat.adjoint());
}

/*
 * 逆阵
 */
void MainWindow::on_inverse_action_triggered()
{
    if(!this->matrix_is_exist()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please open a file first!"));
        return;
    }
    if(mat.determinant()==0) {
        QMessageBox::warning(this, tr("Warning"), tr("No inverse!"));
        return;
    }
    Matrix_show(this->INVERSE, this->mat.inverse());
}

/*
 * 矩阵的秩
 */
void MainWindow::on_matrix_rank_action_triggered()
{
    if(!this->matrix_is_exist()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please open a file first!"));
        return;
    }
    MatrixXd mat(m,n);

    FullPivLU<MatrixXd> lu(mat);
    std::cout << "By default, the rank of A is found to be " << lu.rank() << std::endl;
    lu.setThreshold(1e-5);
    QString tempStr;
    ui->matrix_show_textedit->append(this->RANK + tempStr.setNum(lu.rank()));
}

/*
 * 判断是否有要处理的矩阵
 * */
 bool MainWindow::matrix_is_exist() {
     if (!this->mat.cols() || !this->mat.rows()) {
         return false;
     }
     return true;
 }

/*
* 矩阵四则运算
*/
void MainWindow::on_double_calculate_action_triggered()
{
    // 设置后面的页面为不可点击
    this->doubleForm.setWindowModality(Qt::ApplicationModal);
    this->doubleForm.show();
}
