#include "Client_App.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Client_App w;
    w.show();
    return a.exec();
    


}
