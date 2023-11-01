#include "widget.h"

#include "ui_widget.h"

widget::widget(QWidget *parent) : QMainWindow(parent), ui(new Ui::widget) {
  ui->setupUi(this);
}

widget::~widget() { delete ui; }
