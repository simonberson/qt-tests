#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TableModel;
class TableGroupModel;
class QSortFilterProxyModel;
#include <QTimer>
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QScopedPointer<TableModel> m_poTableModel;
    QScopedPointer<TableGroupModel> m_poTableGroupModel;
    QScopedPointer<QSortFilterProxyModel> m_poSortFilterModel;
    void FillTable();

    QWidget * InitInputWidget();
    QWidget * InitTableWidget();

    QTimer * m_poTimer;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
