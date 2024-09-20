#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    try
    {

    }catch( const std::exception& e )
    {

    }
    return a.exec();
}
