#ifndef SINGLETON_H
#define SINGLETON_H

#include <new>

template <typename T>
class Singleton {
public:
    //外部获取单例的接口
    static T& getInstance()
    {
        static T instance;   //函数静态变量可以实现延时构造。
        return instance;
    }
    virtual ~Singleton(){};
    //禁止拷贝
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    //构造和析构函数私有化
    Singleton() = default;

};

#endif // SINGLETON_H


