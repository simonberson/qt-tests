#include "table_group_model.h"

TableGroupModel::TableGroupModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void TableGroupModel::Clear()
{
    m_oData.clear();
}

QVariant TableGroupModel::GetData(int iRow, int iColumn) const
{
    switch (iColumn) {
    case 0: // Name column
        return m_oData.at(iRow).oName;
    case 1: // Value column
        return m_oData.at(iRow).iValue;
    default:
        break;
    }
    return QVariant();
}

bool TableGroupModel::AddItem(const QString &oName, int iValue) const
{
    // search for the item.
    auto oIt = std::find_if(m_oData.begin(), m_oData.end(),
                            [oName](const STABLE_ITEM & sTableItem){
        return (sTableItem.oName == oName);
    });

    // Item found ?
    if (oIt != m_oData.end())
    {
        // update values.
        (*oIt).iValue += iValue;

        // filter this row.
        return false;
    }

    // Append new item
    m_oData.append(STABLE_ITEM(oName, iValue));

    // accept this row
    return true;
}

bool TableGroupModel::filterAcceptsRow(int iSourceRow, const QModelIndex &oSourceParent) const
{
    QModelIndex oIndex=
            sourceModel()->index(iSourceRow, 0, oSourceParent);

    QString oValueName =
            sourceModel()->data(oIndex).toString();

    oIndex=
            sourceModel()->index(iSourceRow, 1, oSourceParent);

    int iValue =
            sourceModel()->data(oIndex).toInt();

    // append data
    return AddItem(oValueName, iValue);

}

QVariant TableGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return GetData(index.row(), index.column());
    default:
        break;
    }

    return sourceModel()->data(index,role);
}

