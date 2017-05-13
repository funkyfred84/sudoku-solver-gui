#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();
    void on_clearButton_clicked();
    void on_textChanged();
private:
    Ui::MainWindow *ui;
    QVector<QTextEdit*> cells;
};

#endif // MAINWINDOW_H
