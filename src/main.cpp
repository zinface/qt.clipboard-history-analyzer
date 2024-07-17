
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>

#include <screenutil.h>
#include <version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("基本 QT 程序框架 - " PROJECT_VERSION);
    
    MainWindow wm;
    wm.show();
   
    ScreenUtil::moveCenterForCursor(wm);

    return a.exec();
}
