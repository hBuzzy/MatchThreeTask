#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include "figure/figure_generator.hpp"

class Table : public QWidget {
Q_OBJECT
    Q_PROPERTY(uint rowsNumber READ GetRowsNumber WRITE SetRowsNumber
                   NOTIFY RowsNumberChanged FINAL)
    Q_PROPERTY(uint columnsNumber READ GetColumnsNumber WRITE SetColumnsNumber
                   NOTIFY ColumnsNumberChanged FINAL)
public:
    explicit Table(QWidget *parent = nullptr);
signals:
    void RowsNumberChanged();
    void ColumnsNumberChanged();
    void InitialisationStarted();
public slots:
    virtual void DrawFigure(const Figure&);
    void ResetCellsColor();
protected slots:
    void SetCells();
public:
    [[nodiscard]] uint GetColumnsNumber() const;
    [[maybe_unused]] void SetColumnsNumber(uint columnsCount);
    [[nodiscard]] uint GetRowsNumber() const;
    [[maybe_unused]] void SetRowsNumber(uint rowsCount);
protected:
    void paintEvent(QPaintEvent *event) final;
    void DrawCells(QPainter *painter);
    [[nodiscard]] QSize GetSize() const;
protected:
    static constexpr uint kCellSize = 20;
    static constexpr QColor kCellDefaultColor = QColor(150, 150, 150);
    QVector<QVector<QColor>> cellsColors_;
    uint rowsCount_ = 0;
    uint columnsCount_ = 0;
};

#endif