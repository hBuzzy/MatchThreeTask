#include "match_three.h"

#include "ui_match_three.h"

#include <QMessageBox>

MatchThree::MatchThree(QWidget *parent) : QMainWindow(parent), ui(new Ui::MatchThree) {
    ui->setupUi(this);
    connect(
        ui->newGameButton, &QPushButton::clicked,
        ui->gameField, &GameField::StartNewGame
    );
    connect(
        ui->menuNewGame, &QAction::triggered,
        ui->gameField, &GameField::StartNewGame
    );
    connect(
        ui->gameField, &GameField::NextFigureUpdated,
        ui->nextFigureDisplay, &Table::DrawFigure
    );
    connect(
        ui->gameField, &GameField::ScoreUpdated,
        ui->scoreDisplay, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display)
    );
    connect(
        ui->gameField, &GameField::FigureColorSwitched,
        ui->colorSwitchesDisplay, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display)
    );
    connect(
        ui->gameField, &GameField::GameOver,
        ui->nextFigureDisplay, &Table::ResetCellsColor
    );
    connect(
        ui->gameField, &GameField::GameOver,
        [this](){ ui->scoreDisplay->display(0); }
    );
    connect(
        ui->gameField, &GameField::GameOver,
        [this](){ ui->colorSwitchesDisplay->display(0); }
    );
    connect(
        ui->exitButton, &QPushButton::clicked,
        this, &MatchThree::close
    );
    connect(
        ui->menuExit, &QAction::triggered,
        this, &MatchThree::close
    );
    connect(
        ui->menuAbout, &QAction::triggered,
        this, &MatchThree::ShowHelp
    );
}

MatchThree::~MatchThree() { delete ui; }

void MatchThree::ShowHelp() const {
    QMessageBox::about((QWidget*)this, "How to play",
        "Controls:\n"
        "\t-Move Left: Left Key;\n"
        "\t-Move Right: Right Key;\n"
        "\t-Rotate right: Up Key;\n"
        "\t-Soft drop: Down Key;\n"
        "\t-Switch color: Space Key;\n"
        "\nGame rules:\n"
        "\t- matching three and more cells with same colors causes them to be destroyed"
        " resulting in score award in an amount equal to match length;\n"
        "\t- if you stack blocks too high the game will over;\n"
    );
}
