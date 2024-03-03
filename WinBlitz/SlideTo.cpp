#include "SlideTo.h"
#include "ui_SlideTo.h"
#include "MainWindow.h"
#include <QRandomGenerator>

SlideTo::SlideTo(QWidget *parent)
        : NotClosable(parent), ui(new Ui::SlideTo) {
    ui->setupUi(this);

    gName = "Slide To";

    targetNumber = QRandomGenerator::global()->bounded(1, 100);
    ui->Info1->setText("Slide to " + QString::number(targetNumber) + "% and release");

    connect(ui->Slider, &QSlider::valueChanged, this, &SlideTo::onSliderValueChanged);
    connect(ui->Slider, &QSlider::sliderReleased, this, &SlideTo::onSliderReleased);
}

SlideTo::~SlideTo() {
    delete ui;
}

void SlideTo::onSliderValueChanged() {
    ui->Percentage->setText(QString::number(ui->Slider->value()) + "%");
}

void SlideTo::onSliderReleased() {
    if (ui->Slider->value() == targetNumber) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
}
