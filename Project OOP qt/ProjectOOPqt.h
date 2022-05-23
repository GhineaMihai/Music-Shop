#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjectOOPqt.h"

class ProjectOOPqt : public QMainWindow
{
    Q_OBJECT

public:
    ProjectOOPqt(QWidget *parent = Q_NULLPTR);

private:
    Ui::ProjectOOPqtClass ui;
};
