#include "halamanperpus.h"
#include "ui_halamanperpus.h"

halamanperpus::halamanperpus(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::halamanperpus)
{
    ui->setupUi(this);
}

halamanperpus::~halamanperpus()
{
    delete ui;
}
