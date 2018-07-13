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
QString MainWindow::open() {
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
* 保存文件
*/
bool MainWindow::save(const QString &fileName, QString content){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("无法写入文件 %1：/n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << content;
    QApplication::restoreOverrideCursor();
    return true;
}

bool MainWindow::save_as(QString content) {
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,
                       tr("另存为 "), this->openFileName, tr("Text File(*.txt;*.csv)"));
    if (fileName.trimmed() == "") {
        return false;
    }
    return this->save(fileName, content);
}


/*
* 主页面打开文件按钮点击事件
*/
void MainWindow::on_open_action_triggered()
{
    QString fileName = this->open();
    if (fileName == NULL)
        return;
    this->openFileName = fileName;
    this->mat = this->fileToMatrix(fileName);
    this->m = this->mat.rows();
    this->n = this->mat.cols();
    Matrix_show(this->ORIGIN, this->mat);
    this->matrixAttribute();
}

/*
* 文件转成矩阵对象
*/
Eigen::MatrixXd MainWindow::fileToMatrix(QString fileName) {
    CSVParser csvp(QString(","));
    QList<QStringList> lines;
    std::string str;
    const char* s = new char();
    lines = csvp.read(fileName);
    int row = lines.size();
    int col = lines[0].size();

    MatrixXd mat(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            str = lines[i][j].toStdString();
            s = str.data();
            mat(i,j) = atof(s);
        }
    }
    return mat;
}

/*
* 主页另存为按钮点击事件
*/
void MainWindow::on_save_as_action_triggered()
{
    this->save_as(ui->matrix_show_textedit->toPlainText());
}

/*
* 获取矩阵属性
*/
void MainWindow::matrixAttribute()
{
    //PHALANX
    if (m == n)
        ui->is_phalanx_label->setText(PHALANX);
    else
        ui->is_phalanx_label->setText(NOT+PHALANX);

    //SYMMETRIC
    k = 0;
    if (m == n)
    {
      for (i = 0; i < m; i++)
      {
        for (j = 0; j < n; j++)
        {
            if (mat(i,j) == mat(j,i))
                k++;
        }
      }
      if (k == m*n)
          ui->is_symmetric_label->setText(SYMMETRIC);
      else
          ui->is_symmetric_label->setText(NOT+SYMMETRIC);
    }
    else
        ui->is_symmetric_label->setText(NOT+SYMMETRIC);

    //DiagonalMatrix
    notDiagonalMatrix = 0;
    if (m == n)
    {
      for (i = 0; i < m; i++)
      {
        for (j = 0; j < n; j++)
        {
            if ((i != j) && (mat(i,j) != 0))
                notDiagonalMatrix = 1;
        }
      }
      if (notDiagonalMatrix)
      {
        ui->is_diagonal_label->setText(NOT+DIAGONAL);
      }
      else
      {
        ui->is_diagonal_label->setText(DIAGONAL);
      }
    }
    else
        ui->is_diagonal_label->setText(NOT+DIAGONAL);
    //SPARSE
    if (!notDiagonalMatrix)
    {
        zero=0.0;
        for (i = 0; i < m; i++)
        {
          for (j = 0; j < n; j++)
            {
                if (mat(i,j) == 0)
                {
                    zero++;
                }
            }
        }

        if ((double)((m*n - zero)/(m*n)) <= 0.05)
             ui->is_sparse_label->setText(SPARSE);
        else
            ui->is_sparse_label->setText(NOT+SPARSE);
    }
    else
    {
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
    if(m!=n)
    {
        QMessageBox::warning(this, tr("Warning"), tr("No Determinant!"));
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
    if(m!=n)
    {
        QMessageBox::warning(this, tr("Warning"), tr("No adjoint!"));
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
    if(m!=n)
    {
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
    FullPivLU<MatrixXd> lu(mat);
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
