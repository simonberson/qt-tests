#include "table_group_model.h"

TableGroupModel::TableGroupModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void TableGroupModel::Clear()
{
    m_oData.clear();
}

QVariant TableGroupModel::GetData(int iRow) const
{
    return m_oData.at(iRow).iValue;
}

QString TableGroupModel::GetName(int iRow) const
{
    return m_oData.at(iRow).oName;
}

bool TableGroupModel::AddItem(const QString &oName, int iValue) const
{

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

    // New item
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

        if (index.column() == 0)
            return GetName(index.row());

        if (index.column() == 1)
            return GetData(index.row());

        break;
    default:
        break;
    }

    return sourceModel()->data(index,role);
}

