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
