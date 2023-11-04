#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QTimer>

#include "table.h"
#include "figure/figure_generator.hpp"

class GameField final : public Table {
Q_OBJECT
public:
    explicit GameField(QWidget *parent = nullptr, int colorSwitchLimit = 3);
signals:
    void NextFigureUpdated(const Figure&);
    void ScoreUpdated(int);
    void FigureColorSwitched(int);
    void GameOver();
public slots:
    void StartNewGame();
private slots:
    void DrawFigure(const Figure&) final;
protected:
    void keyPressEvent(QKeyEvent *event) final;
private:
    [[nodiscard]] bool IsOutOfBounds(const Figure&, int dx = 0, int dy = 0);
    void RedrawFigure(bool, auto&&);
    void EraseFigure(const Figure&);
    void NextFigure();
    void FigureDrop();
    void StopGame();
    uint CountScore() noexcept;
private:
    FigureGenerator<> figureGenerator_;
    Figure currentFigure_, nextFigure_;
    int dx_ = 0, dy_ = 0;
    uint score_ = 0;
    QTimer timer_;
    const uint colorSwitchLimit_ = 3;
    uint colorSwitches_ = 0;
};

#endif