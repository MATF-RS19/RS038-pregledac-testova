#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <iostream>
#include <cstdlib>
#include "handler.hpp"

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



void MainWindow::on_pushButton_clicked()
{
    ui->result_text->setText("");
    QString file_name = QFileDialog::getOpenFileName (this, tr("Open File"), "/home/renetaki/Desktop/Skener/", tr("Images (*.png *.xpm *.jpg)"), 0, QFileDialog::DontUseNativeDialog);

    if(file_name.isEmpty()){
        std::cout << "Ne postoji slika.\n";
        exit(EXIT_FAILURE);
    }

    std::string converted_string = file_name.toUtf8().constData();

    std::vector<bool> results = process_result(converted_string);

    int progress = 0;
    int brojac = 1;
    for(auto result : results){
        progress += result;\
        brojac++;

        if(result){
            ui->result_text->insertPlainText("Tacno resenje!\n");
        }
        else {
            ui->result_text->insertPlainText("Netacno resenje!\n");
        }
    }

    progress = progress * 100 / results.size();

    QPixmap pic("/home/renetaki/Desktop/Projekti/build-Scanner-Desktop_Qt_5_6_3_GCC_64bit-Debug/final.jpg");

    ui->label_output->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->label_output->setPixmap(pic.scaled(360,450, Qt::KeepAspectRatio));

   // ui->progressBar->text("Vas ucinak je:");
    ui->progressBar->setValue(progress);

    return ;
}

