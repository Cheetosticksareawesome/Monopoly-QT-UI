#include <QApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include "GameState.h"
#include "UI-Connections.h"
int main(int argc,char** argv) {
 QApplication app(argc,argv); QFontDatabase::addApplicationFont("C:/Windows/Fonts/segoeui.ttf");
 QMainWindow window; Ui::MainWindow ui; ui.setupUi(&window); auto game=SetupGame(4); Connect_UI(game,ui);
 window.show(); window.resize(1120,820); app.processEvents(); window.grab().save("build/compact-ui.png");
 return 0;
}