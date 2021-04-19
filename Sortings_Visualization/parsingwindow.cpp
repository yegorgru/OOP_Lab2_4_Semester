#include "parsingwindow.h"
#include "ui_parsingwindow.h"
#include <QString>
#include "parser.h"
ParsingWindow::ParsingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingWindow)
{
    ui->setupUi(this);
}

ParsingWindow::~ParsingWindow()
{
    delete ui;
}

void ParsingWindow::on_pushButton_clicked()
{
    QString input = ui->inputLine->text();
     queue<char> gen;
     parser f;
 gen = f.to_revpol(input);
 double res  = f.calc(gen);
 ui->theorComplexity->setText( QString::number(res) );
}
