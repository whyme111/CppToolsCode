#include "classb.h"
#include "QDebug"

void classB::echo()
{
    qDebug()<<"classB::echo";
}

classB::classB(QObject *parent)
    : QObject{parent}
{

}
