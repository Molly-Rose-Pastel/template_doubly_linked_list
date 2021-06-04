#include <QCoreApplication>

#include "UnitTest.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UnitTest unitTest;

    unitTest.test_append();

    return a.exec();
}

