#include "form_wall.h"
#include "ui_form_wall.h"

Form_wall::Form_wall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_wall)
{
    ui->setupUi(this);
    flag_ok = false;
}

Form_wall::~Form_wall()
{
    delete ui;
}

QColor Form_wall::Get_color()
{
    return color;
}

void Form_wall::on_pushButton_clicked()
{
    QColorDialog *Color_dialog = new QColorDialog(this);
    color = Color_dialog->getColor();
    QPalette p = ui->graphicsView->palette();
    p.setColor(ui->graphicsView->backgroundRole(), color);
    ui->graphicsView->setPalette(p);

}


void Form_wall::on_pushButton_2_clicked()
{
    if(ui->doubleSpinBox->value() != 0)
    {
        flag_ok = true;
        this->close();
    }
    else
    {
         QMessageBox::information(this, "Информация", "Высота стены не может принимать значение 0.\nЗадайте значение отличное от 0.");
    }

}

void Form_wall::on_pushButton_3_clicked()
{
    flag_ok = false;
    color = Qt::black;
    this->close();
}
