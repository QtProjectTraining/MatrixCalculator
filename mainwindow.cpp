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
        MatrixXd mat(m,n);
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                 str = lines[i][j].toStdString();
                 s = str.data();
                 mat(i,j) = atof(s);
                }
             }
             this->mat = mat;
             Matrix_show(this->mat);
    }
}

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
        QMessageBox::warning(this, tr("Error"), tr("打开文件失败"));
        return;
    }
    QTextStream textStream(&file);
    QString str = ui->matrix_show_textedit->toPlainText();
    textStream << str;
    QMessageBox::warning(this, tr("提示"), tr("保存文件成功"));
    file.close();
}

void MainWindow::on_transpose_action_triggered()
{
    Matrix_show(this->mat.transpose());
}


 void MainWindow::Matrix_show(Eigen::MatrixXd Matrix)
 {
     ui->matrix_show_textedit->clear();
     QString disPlayString;
     for (int i=0 ;i<Matrix.cols(); i++) {
         for (int j=0; j<Matrix.rows(); j++) {
             disPlayString.append(QString::number(Matrix(i, j)) + " ");
             if (j == Matrix.rows() - 1) {
                 disPlayString.append("\n");
             }
         }
     }
     ui->matrix_show_textedit->setPlainText(disPlayString);
 }

void MainWindow::on_determinant_action_triggered()
{
    QString tempStr;
    ui->matrix_show_textedit->setText(tempStr.setNum(mat.determinant()));
}

void MainWindow::on_adjoint_action_triggered()
{

            Matrix_show(this->mat.adjoint());
}

void MainWindow::on_inverse_action_triggered()
{
             Matrix_show(this->mat.inverse());
}

void MainWindow::on_matrix_rank_action_triggered()
{
    MatrixXd mat(m,n);

    FullPivLU<MatrixXd> lu(mat);
     std::cout << "By default, the rank of A is found to be " << lu.rank() << std::endl;
    lu.setThreshold(1e-5);
    QString tempStr;
    ui->matrix_show_textedit->setText(tempStr.setNum(lu.rank()));

}
