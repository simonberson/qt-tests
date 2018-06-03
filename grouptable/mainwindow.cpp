#include "mainwindow.h"

#include <QTableView>
#include <QHBoxLayout>
#include "table_model.h"
#include "table_group_model.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget * poCentral = new QWidget(this);
    QVBoxLayout * poVLayoutTables = new QVBoxLayout;
    poCentral->setLayout(poVLayoutTables);

    poVLayoutTables->addWidget(InitInputWidget());
    poVLayoutTables->addWidget(InitTableWidget());

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

    m_poTableModel->DropTable(oTableData);

}

QWidget *MainWindow::InitInputWidget()
{
    // Inputs widgets
    QHBoxLayout * poHLayoutInput = new QHBoxLayout;
    QLabel * poInputLabel = new QLabel("Add to table: ", this);
    QLineEdit * poItemName = new QLineEdit(this);
    QSpinBox * poItemValue = new QSpinBox(this);
    QPushButton * poAddBtn = new QPushButton("Add", this);
    QPushButton * poClearBtn = new QPushButton("Clear", this);
    poHLayoutInput->addWidget(poInputLabel);
    poHLayoutInput->addWidget(poItemName);
    poHLayoutInput->addWidget(poItemValue);
    poHLayoutInput->addWidget(poAddBtn);
    poHLayoutInput->addWidget(poClearBtn );

    // register actions
    connect(poAddBtn, &QPushButton::clicked,
            [=]()
    {
        m_poTableModel->AddItem(STABLE_ITEM(poItemName->text(),
                                            poItemValue->value()));

        m_poTableGroupModel->sort(0);
    });

    connect(poClearBtn, &QPushButton::clicked,
            [=]()
    {
        m_poTableModel->Clear();
        m_poTableGroupModel->Clear();
    });

    QWidget * poInWidget = new QWidget(this);
    poInWidget->setLayout(poHLayoutInput);

    return poInWidget;
}

QWidget *MainWindow::InitTableWidget()
{
    QHBoxLayout * poHTableLayout = new QHBoxLayout;

    // Table Model
    m_poTableModel.reset(new TableModel);

    // Table view
    QTableView * poTable = new QTableView(this);
    m_poSortModel.reset(new QSortFilterProxyModel(this));
    m_poSortModel->setSourceModel(m_poTableModel.data());

    poTable->setModel(m_poSortModel.data());
    m_poSortModel->sort(0);
    poTable->setSortingEnabled(true);

    // Group table view
    QTableView * poGroupTable = new QTableView(this);

    m_poTableGroupModel.reset(new TableGroupModel(this));
    m_poTableGroupModel->setSourceModel(m_poTableModel.data());
    m_poTableGroupModel->setDynamicSortFilter(false); // update diractly on data change

    poGroupTable->setModel(m_poTableGroupModel.data());

    // Layout horizontal tables
    poHTableLayout->addWidget(poTable);
    poHTableLayout->addWidget(poGroupTable);

    QWidget * poTablesWidget = new QWidget(this);
    poTablesWidget->setLayout(poHTableLayout);

    return poTablesWidget;
}
