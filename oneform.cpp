#include "oneform.h"
#include "ui_oneform.h"

OneForm::OneForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneForm)
{
    ui->setupUi(this);
}

OneForm::~OneForm()
{
    delete ui;
}
