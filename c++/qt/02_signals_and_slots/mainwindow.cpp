#include <iostream>
#include "mainwindow.h"
#include <QTimer>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::value_changed, &MainWindow::print_value);
    connect(this, &MainWindow::value_changed, &MainWindow::update_label);
    connect(this,
            &MainWindow::value_changed,
            [](int val) {
                std::cout << "Printing from lambda: " << val << std::endl;
            }
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::value(int new_value) {
    emit value_changed(new_value);
    std::swap(m_value, new_value);
    return new_value;
}

void MainWindow::print_value(int val) {
   std::cout << "Printing from " << __FUNCTION__ << ": " << val << std::endl;
}

void MainWindow::update_label(int val) {
    ui->label->setText(std::to_string(val).c_str());
    ui->label->update();
}

void MainWindow::on_pushButton_clicked()
{
   this->value(ui->lineEdit->text().toInt());
}
