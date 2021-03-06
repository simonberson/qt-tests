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
    m_poTableGroupModel->DoInvalidateFilter();

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
    });

    connect(poClearBtn, &QPushButton::clicked,
            [=]()
    {
        m_poTableModel->Clear();
        m_poTableGroupModel->Clear();
    });


    // Filter widgets
    QHBoxLayout * poHLayoutFilter = new QHBoxLayout;
    QLabel * poFilterLabel = new QLabel("Filter: ", this);
    QLineEdit * poFilterValue = new QLineEdit(this);
    QPushButton * poFilterBtn = new QPushButton("Filter", this);

    poHLayoutFilter->addWidget(poFilterLabel);
    poHLayoutFilter->addWidget(poFilterValue);
    poHLayoutFilter->addWidget(poFilterBtn);

    // register filter action.
    connect(poFilterBtn, &QPushButton::clicked,
            [=]()
    {

        // Filter table model
        m_poSortFilterModel->setFilterFixedString(poFilterValue->text());
        m_poSortFilterModel->setFilterKeyColumn(-1); // filter all columns

        // clear

        m_poTableGroupModel->DoInvalidateFilter();

    });

    QWidget * poInWidget = new QWidget(this);
    QVBoxLayout * poVLayout = new QVBoxLayout;
    poVLayout->addLayout(poHLayoutInput);
    poVLayout->addLayout(poHLayoutFilter);

    poInWidget->setLayout(poVLayout);

    return poInWidget;
}
#include <iostream>
QWidget *MainWindow::InitTableWidget()
{
    QHBoxLayout * poHTableLayout = new QHBoxLayout;

    // Table view
    QTableView * poTable = new QTableView(this);

    // Table Model
    m_poTableModel.reset(new TableModel);
    m_poSortFilterModel.reset(new QSortFilterProxyModel(this));
    m_poSortFilterModel->setSourceModel(m_poTableModel.data());

    poTable->setModel(m_poSortFilterModel.data());
    poTable->setSortingEnabled(true);


    // Group table view
    QTableView * poGroupTable = new QTableView(this);

    m_poTableGroupModel.reset(new TableGroupModel(this));
    m_poTableGroupModel->setSourceModel(m_poSortFilterModel.data());
    m_poTableGroupModel->setDynamicSortFilter(false); // update directly on data change

    poGroupTable->setModel(m_poTableGroupModel.data());
    poGroupTable->setSortingEnabled(true);

    // Layout horizontal tables
    poHTableLayout->addWidget(poTable);
    poHTableLayout->addWidget(poGroupTable);

    QWidget * poTablesWidget = new QWidget(this);
    poTablesWidget->setLayout(poHTableLayout);

    m_poTimer = new QTimer(this);

    connect(m_poTimer, &QTimer::timeout,
            [this]()
    {

        QAbstractItemModel * poModel = m_poTableGroupModel.data();
        int rows = poModel->rowCount();
        for (int i = 0; i < rows; ++i) {
            QModelIndex oCurIndex = poModel->index(i,0);
            QString oName = poModel->data(oCurIndex).toString();

            oCurIndex = poModel->index(i,1);
            QString oValue = poModel->data(oCurIndex).toString();

            std::cout<<"row = "<<i<<", name = "
                    << oName.toStdString()
                    <<", value = "<< oValue.toStdString()
                    <<std::endl;
        }

        std::cout<<"total rows = "<<rows<<std::endl;



    });

    m_poTimer->start(5000);

    return poTablesWidget;
}
