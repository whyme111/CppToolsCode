#ifndef CLASSA_H
#define CLASSA_H

#include "singleton.h"

class classA:public Singleton<classA>
{
    friend class Singleton<classA>;

public:
    void echo();

private:
    classA();
};

#endif // CLASSA_H
