#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QTextStream"
#include "qfile.h"
#include "qfiledialog.h"
#include "csvtablemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_load_clicked()
{
    const QString fileName =
            QFileDialog::getOpenFileName(this, tr("Choose a data file"), "", "*.csv");
    if (fileName.isEmpty())
        return;
    if(model)
    {
        delete model;
        model =nullptr;
    }
    model = new CSVTableModel(fileName,',', true, ui->tableView);
    ui->tableView->setModel(model);
}

void MainWindow::on_btn_saveas_clicked()
{
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a data file"), "", "*.csv");
    if (fileName.isEmpty())
        return;
    if(model)
        model->save(fileName);

}

