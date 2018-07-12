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
        //QMessageBox::warning(this, tr("Hi!"), fileName, QMessageBox::Yes);
        if (!fileName.isNull()) {
            QFile file(fileName);
            if (!file.open(QFile::ReadOnly|QFile::Text)) {
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

}
