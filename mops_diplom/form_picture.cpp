#include "form_picture.h"
#include "ui_form_picture.h"

Form_Picture::Form_Picture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Picture)
{
    ui->setupUi(this);
    flag_ok = false;
}

Form_Picture::~Form_Picture()
{
    delete ui;
}

QString Form_Picture::Get_WayFile()
{
    return WayFile;
}

void Form_Picture::on_pushButton_clicked()
{
    if(ui->label_2->text().size() == 0 && ui->textEdit->toPlainText().size() != 0)
    {
        QMessageBox::information(this, "Информация", "Графический файл для картины не выбран.\nНеобходимо выбрать графический файл.");
    }
    if(ui->textEdit->toPlainText().size() == 0 && ui->label_2->text().size() != 0)
    {
        QMessageBox::information(this, "Информация", "Описание картины не заполнено.\nНеобходимо заполнить описание картины.");
    }    
    if(ui->label_2->text().size() != 0 && ui->textEdit->toPlainText().size() != 0)
    {
        ui->label_2->clear();
        flag_ok = true;
        this->close();
    }
}

void Form_Picture::on_pushButton_2_clicked()
{
    flag_ok = false;
    ui->label_2->clear();
    this->close();
}

void Form_Picture::on_pushButton_3_clicked()
{
    WayFile = QFileDialog::getOpenFileName(0,"Выбор файла для картины","","*.jpeg *.png *gif");
    ui->label_2->setText(WayFile);
   // QPixmap pp(WayFile);
    QImage ppp(WayFile);
    qDebug() << ppp.height() << ppp.width();
}


