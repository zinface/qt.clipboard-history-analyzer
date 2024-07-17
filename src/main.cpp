
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>

#include <screenutil.h>
#include <version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("剪贴板历史分析器 - " PROJECT_VERSION);

    MainWindow wm;
    wm.show();

    ScreenUtil::moveCenterForCursor(wm);

    return a.exec();
}
