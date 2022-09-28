#pragma once

#include <QtWidgets/QWidget>
#include "ui_bubbles.h"

class BubblesUI : public QWidget
{
    Q_OBJECT

public:

    // New widget without parent
    BubblesUI(QWidget *parent = nullptr);
    ~BubblesUI();

private:

    // Define ui class
    Ui::BubblesClass ui;
};
