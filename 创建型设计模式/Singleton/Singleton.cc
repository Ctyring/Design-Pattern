// 单例模式几种实现方式
// 通过静态成员变量实现单例
// 懒汉式
// 原理：通过局部静态成员实现单例类，函数的局部静态变量生命周期随着进程结束而结束。
// 延迟加载，线程不安全
#include <iostream>
#include <memory>
#include <mutex>
using namespace std;
class Singleton1
{
    // 1. 将构造函数和析构函数私有化
    Singleton1() {}
    ~Singleton1() {}
    Singleton1(const Singleton1&) = delete;
    Singleton1& operator=(const Singleton1&) = delete;
public:
    static Singleton1* GetInstance()
    {
        static Singleton1 instance;
        return &instance;
    }
};

// 通过静态成员变量指针方式
// 懒汉式
// 原理还是利用静态变量的生命周期，使用的时候再加载，节约内存
// 不加锁线程不安全并且不好把握内存释放时间，容易内存泄漏
class Singleton2
{
    Singleton2() {}
    ~Singleton2() {}
    Singleton2(const Singleton2&) = delete;
    Singleton2& operator=(const Singleton2&) = delete;
public:
    static Singleton2* GetInstance()
    {
        if(instance == nullptr)
        {
            instance = new Singleton2();
        }
        return instance;
    }
private:
    static Singleton2* instance;
};

// 智能指针
// 懒汉式
// 解决内存泄漏问题，但是不是线程安全的
class Singleton3
{
    Singleton3() {}
    Singleton3(const Singleton3&) = delete;
    Singleton3& operator=(const Singleton3&) = delete;
public:
    ~Singleton3() {}
    static Singleton3* GetInstance()
    {
        static std::shared_ptr<Singleton3> instance(new Singleton3);
        return instance.get();
    }
};

// 饿汉式
// 原理：在类加载的时候就创建好对象，不管你用不用，先创建好了再说
// 线程安全，但是浪费内存
class Singleton4
{
    Singleton4(const Singleton4&) = delete;
    Singleton4& operator=(const Singleton4&) = delete;
public:
    Singleton4() {
    }
    ~Singleton4() {}
    static std::shared_ptr<Singleton4> GetInstance()
    {     
        return instance;
    }
private:
    static std::shared_ptr<Singleton4> instance;
};
std::shared_ptr<Singleton4> Singleton4::instance = std::make_shared<Singleton4>();

// 双重检查锁
// 懒汉式
class Singleton5
{
    Singleton5(const Singleton5&) = delete;
    Singleton5& operator=(const Singleton5&) = delete;
public:
    Singleton5() {
    }
    ~Singleton5() {}
    static std::shared_ptr<Singleton5> GetInstance()
    {
        if(instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(instance == nullptr)
            {
                instance = std::make_shared<Singleton5>();
            }
        }
        return instance;
    }
private:
    static std::shared_ptr<Singleton5> instance;
    static std::mutex mtx;
};
std::shared_ptr<Singleton5> Singleton5::instance = nullptr;
// 测试
int main()
{
    std::shared_ptr<Singleton5> s1 = Singleton5::GetInstance();
    std::shared_ptr<Singleton5> s2 = Singleton5::GetInstance();
    cout << s1 << endl;
    cout << s2 << endl;
    return 0;
}