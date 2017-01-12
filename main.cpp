#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    MainWindow w;
    w.show();
    
    return a.exec();
}

// todo
// 坐标需要统一, 转换的地方要统一
// 语言设置
