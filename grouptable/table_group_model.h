#ifndef TABLE_GROUP_MODEL_H
#define TABLE_GROUP_MODEL_H


#include <QAbstractProxyModel>
#include <QSortFilterProxyModel>
#include "table_def.h"

// Proxy model for doing group and count
class TableGroupModel : public QSortFilterProxyModel
{
    Q_OBJECT

private:
    mutable TableData m_oData;

    QVariant GetData(int iRow, int iColumn) const;
    bool AddItem(const QString & oName, int iValue) const;

protected:
    bool filterAcceptsRow(int iSourceRow, const QModelIndex &oSourceParent) const;
    QVariant data(const QModelIndex &oIndex, int role) const override;

public:

    TableGroupModel(QObject *parent = NULL) ;

    void Clear();

};

#endif // TABLE_GROUP_MODEL_H
