#include "mainwindow.h"

#include <QTableView>
#include <QHBoxLayout>
#include "table_model.h"
#include "table_group_model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget * poCentral = new QWidget(this);
    QHBoxLayout * poVLayoutTables = new QHBoxLayout;
    poCentral->setLayout(poVLayoutTables);

    // Table Model
    m_poTableModel.reset(new TableModel);

    // Table view
    QTableView * poTable = new QTableView(this);
    poTable->setModel(m_poTableModel.data());

    // Group table view
    QTableView * poGroupTable = new QTableView(this);

    TableGroupModel * poTableGroupModel = new TableGroupModel(this);
    poTableGroupModel->setSourceModel(m_poTableModel.data());

    poGroupTable->setModel(poTableGroupModel);

    // Layout horizontal tables
    poVLayoutTables->addWidget(poTable);
    poVLayoutTables->addWidget(poGroupTable);

    this->setCentralWidget(poCentral);

    // Fill table with data.
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
