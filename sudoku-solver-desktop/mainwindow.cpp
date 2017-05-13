#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QTextEdit>
#include <QChar>
#include <array>
#include <QRect>
#include "sudoku.h"
#include "solver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    for (int i = 0; i < 9; ++i) {
        QHBoxLayout* row = new QHBoxLayout(this);
        row->setSpacing(0);
        for (int j = 0; j < 9; ++j) {

            QTextEdit* edit = new QTextEdit(this);
            edit->setTabChangesFocus(true);
            edit->setAlignment(Qt::AlignCenter);
            QFont font = edit->font();
            font.setPointSize(32);
            edit->setFont(font);
            connect(edit, &QTextEdit::textChanged, this, &MainWindow::on_textChanged);
            row->addWidget(edit);

            cells.append(edit);
            if ((j+1) % 3 == 0) {
                QWidget* line = new QWidget(this);
                line->setMinimumWidth(5);
                row->addWidget(line);
            }
        }
        ui->field->addItem(row);
        if ((i+1) % 3 == 0) {
            QWidget* line = new QWidget(this);
            line->setMinimumHeight(5);
            ui->field->addWidget(line);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solveButton_clicked()
{
    std::array<uint8_t, 81> fields;
    for(int i = 0; i < cells.size(); ++i) {
        QTextEdit* cell = cells.at(i);
        QString value = cell->toPlainText();
        int val = value.toInt();
        fields[i] = val;
    }
    Sudoku su{fields};
    Sudoku ret = solve(su);
    for(int i = 0; i < 81; ++i) {
        if (!cells[i]->toPlainText().isEmpty()) {
            cells[i]->setEnabled(false);
        }
        cells[i]->setText(QString::number(ret.field(Index(i / 9, i % 9))));
    }
}

void MainWindow::on_clearButton_clicked()
{
    for(auto& cell : cells) {
        cell->clear();
        cell->setEnabled(true);
    }
}

void MainWindow::on_textChanged() {
    QTextEdit* currentCell = nullptr;
    for (auto& cell : cells) {
        if (cell->hasFocus()) {
            currentCell = cell;
            break;
        }
    }
    if (currentCell == nullptr) {
        return;
    }
    QString tmp = currentCell->toPlainText();
    if (tmp.isEmpty()) {
        return;
    }
    if (tmp.size() > 1) {
        currentCell->setText(tmp.left(1));
    }
    bool ok;
    int letter = tmp.toInt(&ok);
    if (!(ok && letter > 0 && letter < 10)) {
        currentCell->setText("");
    }

}
