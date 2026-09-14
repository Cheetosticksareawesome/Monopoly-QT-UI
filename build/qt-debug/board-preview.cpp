#include <QApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include "board-preview-ui.h"
int main(int argc,char** argv) {
 QApplication app(argc,argv);
 QFontDatabase::addApplicationFont("C:/Windows/Fonts/segoeui.ttf"); QMainWindow window;
 Ui::MainWindow ui;
 ui.setupUi(&window);
 window.show();
 app.processEvents();
 window.resize(960, 700); app.processEvents(); window.grab().save("build/qt-debug/board-small.png"); const QSize small = ui.boardWidget->size(); window.resize(1440, 960); app.processEvents(); window.grab().save("build/qt-debug/board-large.png"); return ui.boardWidget->width() > small.width() && ui.boardWidget->height() > small.height() ? 0 : 1;
}


