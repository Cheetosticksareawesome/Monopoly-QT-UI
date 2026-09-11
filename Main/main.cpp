
#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "ui_MainUI.h"

int main(int argc, char *argv[])
{
    QApplication app{argc, argv};

    QMainWindow window{};

    Ui::MainWindow ui{};

    ui.setupUi(&window);

    auto onButtonClicked = [&ui]()
    {
        ui.label->setText("Clicked!");
    };
    QObject::connect(ui.pushButton, &QPushButton::clicked, &window, onButtonClicked);

    window.show();

    return app.exec();
}
