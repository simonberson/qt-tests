#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TableModel;
class TableGroupModel;
class QSortFilterProxyModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QScopedPointer<TableModel> m_poTableModel;
    QScopedPointer<TableGroupModel> m_poTableGroupModel;
    QScopedPointer<QSortFilterProxyModel> m_poSortFilterModel;
    QScopedPointer<QSortFilterProxyModel> m_poSortFilterGroupModel;
    void FillTable();

    QWidget * InitInputWidget();
    QWidget * InitTableWidget();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
