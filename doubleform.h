#ifndef DOUBLEFORM_H
#define DOUBLEFORM_H

#include <QWidget>

namespace Ui {
class DoubleForm;
}

class DoubleForm : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleForm(QWidget *parent = 0);
    ~DoubleForm();

private:
    Ui::DoubleForm *ui;
};

#endif // DOUBLEFORM_H
