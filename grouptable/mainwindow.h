#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TableModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QScopedPointer<TableModel> m_poTableModel;

    void FillTable();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
