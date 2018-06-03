#include "table_model.h"


const QStringList TableModel::s_oHeaderTitles = QStringList() << "Name" << "Value";

TableModel::TableModel(QObject *poParent)
    : QAbstractTableModel(poParent)
{

}

void TableModel::UpdateData(const TableData &oTableData)
{
    beginResetModel();
    m_oTableData =
            oTableData;
    endResetModel();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_oTableData.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return DEF_TABLE_COLUMN_COUNT;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_oTableData.size() || index.row() < 0)
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        return GetData(index.row(), index.column());
    default:
        return QVariant();
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Header data ?
    if ( (orientation != Qt::Horizontal)
         || (section >= DEF_TABLE_COLUMN_COUNT))
        // Not valid header title
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        // Header title

        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Value";
        default:
            break;
        }

        break;

    default:
        return QVariant();
        break;
    }


    return QVariant();
}

int TableModel::GetValue(int iRow) const
{
    return m_oTableData.at(iRow).iValue;
}

const QString TableModel::GetName(int iRow) const
{
    return m_oTableData.at(iRow).oName;
}

const STABLE_ITEM &TableModel::GetTableItem(int iRow) const
{
    return m_oTableData.at(iRow);
}

const QVariant TableModel::GetData(int iRow, int iColumn) const
{
    switch (iColumn) {
    case 0:
        return GetName(iRow);
    case 1:
        return GetValue(iRow);
    default:
        break;
    }

    return QVariant();
}
