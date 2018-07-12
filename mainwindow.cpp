#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QMessageBox::warning(this, tr("Hi!"), fileName, QMessageBox::Yes);
    if (!fileName.isNull()) {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Read file failed:&1").arg(file.errorString()));
            return;
        }
        QString disPlayString;
        QTextStream in(&file);
        QString line = in.readLine();
        disPlayString.append(line + "\n");
        while(!line.isNull()) {
            line = in.readLine();
            disPlayString.append(line + "\n");
        }
        ui->matrix_show_textedit->clear();
        ui->matrix_show_textedit->setPlainText(disPlayString);
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





