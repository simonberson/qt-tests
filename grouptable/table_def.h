#ifndef TABLE_DEF_H
#define TABLE_DEF_H


#define DEF_TABLE_COLUMN_COUNT  2
#include <QVector>

typedef struct _TableItem_
{
    _TableItem_()
    {

    }

    _TableItem_(const QString& _oName, int _iValue)
    {
        this->iValue = _iValue;
        this->oName = _oName;
    }

    int iValue;
    QString oName;

}STABLE_ITEM;

typedef  QVector<STABLE_ITEM> TableData;


#endif // TABLE_DEF_H
