#include "mainwindow.h"

#include <QTableView>
#include <QHBoxLayout>
#include "table_model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QTableView * poTable = new QTableView(this);

    m_poTableModel.reset(new TableModel);
    poTable->setModel(m_poTableModel.data());
    this->setCentralWidget(poTable);

    FillTable();
}

MainWindow::~MainWindow()
{
}

void MainWindow::FillTable()
{
    TableData oTableData;
    oTableData.append(STABLE_ITEM("a",1));
    oTableData.append(STABLE_ITEM("a",2));
    oTableData.append(STABLE_ITEM("b",3));
    oTableData.append(STABLE_ITEM("c",4));
    oTableData.append(STABLE_ITEM("c",5));
    oTableData.append(STABLE_ITEM("a",7));



    m_poTableModel->UpdateData(oTableData);

}
