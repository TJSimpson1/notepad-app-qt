#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString()); //Clears textEdit widget
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName); //Object for reading and writing files
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: ", file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file); //Interface for reading text
    QString text = in.readAll();
    ui->textEdit->setText(text); //Inserts text into text widget
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: ", file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file); //Interface for writing text
    QString text = ui->textEdit->toPlainText(); //Copy text from text widget
    out << text; //Output text to file
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer; //Allows us to interact with any printer on our network
    printer.setPrinterName("Printer Name"); //Can use actual printer name if known
    QPrintDialog pDialog(&printer, this); //Allow us to select actual printer we want to use
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer); //Sends text from textEdit to printer
}

