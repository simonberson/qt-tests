#ifndef TABLE_GROUP_MODEL_H
#define TABLE_GROUP_MODEL_H


#include <QAbstractProxyModel>
#include <QSortFilterProxyModel>
#include "table_def.h"

// Proxy model for doing groupBy
class TableGroupModel : public QSortFilterProxyModel
{
    Q_OBJECT

private:
    mutable TableData m_oData;

    QVariant GetData(int iRow) const;
    QString GetName(int iRow) const;

    bool AddItem(const QString & oName, int iValue) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    QVariant data(const QModelIndex &index, int role) const override;

public:

    TableGroupModel(QObject *parent = NULL) ;
    ~TableGroupModel() {}

};

#endif // TABLE_GROUP_MODEL_H
