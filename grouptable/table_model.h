#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H


#include <QAbstractTableModel>
#include <QVector>
#include "table_def.h"

class TableModel : public QAbstractTableModel
{


    // getters.
    int GetValue(int iRow) const;
    const QString GetName(int iRow) const;
    const STABLE_ITEM& GetTableItem(int iRow) const;

    const QVariant GetData(int iRow, int iColumn) const;

    // Table data.
    TableData m_oTableData;

    static const QStringList s_oHeaderTitles;

public:
    TableModel(QObject *poParent = Q_NULLPTR);

    // Table data
    void DropTable(const TableData& oTableData);

    void AddItem(const STABLE_ITEM & sTableItem);

    void Clear();

    // Abstact item model functions.
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    // Returns an appropriate value for the requested section, orientation and role
    QVariant headerData ( int section,Qt::Orientation orientation, int role) const;
};

#endif // TABLE_MODEL_H
