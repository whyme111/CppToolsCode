#ifndef CLASSB_H
#define CLASSB_H

#include <QObject>
#include "singleton.h"

class classB : public QObject ,public Singleton<classB>
{
    friend class Singleton<classB>;
    Q_OBJECT
public:
    void echo();

private:
     explicit classB(QObject *parent = nullptr);

};

#endif // CLASSB_H
