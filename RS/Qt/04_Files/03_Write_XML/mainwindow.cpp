#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QXmlStreamWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ConfirmButton_clicked()
{

}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = ui->fileNameEdit->text();
    QString firstName = ui->firstNameEdit->text();
    QString lastName = ui->lastNameEdit->text();
    QString bornDate = ui->ageDate->text();

    QFile outFile(fileName);

    if (!outFile.open(QIODevice::WriteOnly)) {
        ui->infoDisplay->append("Opening file for writing failed");
        return;
    }

    QXmlStreamWriter xml(&outFile);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
        xml.writeStartElement("user");
            xml.writeTextElement("firstname", firstName);
            xml.writeTextElement("lastname", lastName);
            xml.writeTextElement("date_of_birth", bornDate);
        xml.writeEndElement();
    xml.writeEndDocument();

    outFile.close();

    ui->infoDisplay->append(QString("User %1 successfully writen to file %2.")
                            .arg(firstName + " " + lastName, fileName));
}
