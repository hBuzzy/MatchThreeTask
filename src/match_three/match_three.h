#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MatchThree;
}
QT_END_NAMESPACE

class MatchThree final : public QMainWindow {
Q_OBJECT
public:
    explicit MatchThree(QWidget *parent = nullptr);
    ~MatchThree() final;
private slots:
    void ShowHelp() const;
private:
    Ui::MatchThree *ui;
};

#endif
