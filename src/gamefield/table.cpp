#include "table.h"

#include <QKeyEvent>
#include <QPainter>

Table::Table(QWidget *parent) : QWidget{parent} {
    setFocusPolicy(Qt::StrongFocus);
    connect(
        this, &Table::InitialisationStarted,
        this,  &Table::SetCells, Qt::QueuedConnection
    );
    emit InitialisationStarted();
}

uint Table::GetRowsNumber() const { return rowsCount_; }

void Table::SetRowsNumber(uint rowsCount) {
    if (rowsCount_ == rowsCount) return;
    rowsCount_ = rowsCount;
    emit RowsNumberChanged();
}

uint Table::GetColumnsNumber() const { return columnsCount_; }

void Table::SetColumnsNumber(uint columnsCount) {
    if (columnsCount_ == columnsCount) return;
    columnsCount_ = columnsCount;
    emit ColumnsNumberChanged();
}

void Table::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    DrawCells(&painter);
}

void Table::SetCells() {
    cellsColors_.resize(rowsCount_);
    for (auto& cell : cellsColors_) {
        cell.resize(columnsCount_);
        cell.fill(kCellDefaultColor);
    }
    setFixedSize(GetSize());
}

void Table::ResetCellsColor() {
    for (auto& cell : cellsColors_)
        cell.fill(kCellDefaultColor);
}

QSize Table::GetSize() const {
    return QSize(columnsCount_, rowsCount_) * kCellSize;
}

void Table::DrawCells(QPainter* painter) {
    for (auto&& [i, row] : std::ranges::views::enumerate(cellsColors_)) {
        for (auto&& [j, color] : std::ranges::views::enumerate(row)) {
            painter->setBrush(color);
            painter->drawRect(
                j * kCellSize, i * kCellSize,
                (j + 1) * kCellSize, (i + 1) * kCellSize
            );
        }
    }
}

void Table::DrawFigure(const Figure& figure) {
    ResetCellsColor();
    auto colors = figure.GetColors();
    for (auto&& cell : figure.GetGeometry())
        cellsColors_[cell[0]][cell[1]] = colors[cell[2]];
    repaint();
}
