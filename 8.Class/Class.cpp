#include <iostream>
#include <string>
using namespace std;
#define LOG(x) cout<<x<<endl;

/*
           class
class不过就是把一些data和一些function（通常这些function用来manipulate这些data）绑定在一起而已。从而方便用户的使用而已。没有什么功能是class所独有的，不可以用其他非class的方式来实现的。
类内容包括：  （1）成员变量；
            （2）成员函数：必须在类中声明，可以在类外定义


类：（1）定义；（2）声明
    1、类的声明和定义可以分开，类似于函数的声明和定义
    2、如果声明在定义之前，则声明之后，定义之前，这个类是不完全类型
        不完全类型适用范围：
        （1）用于定义指向该类型的指针或引用，例如：类中包含指向它自身的引用和指针
        （2）在其他声明中，作为不完全类型的参数或者返回类型
        不完全类型不适用范围：
        （1）只有类被定义后，才能创建对象
        （2）只有类定义后，才能访问其成员变量
        （3）一个类的  成员类型  ，不能是自己，此时类没有被定义完，属于不完全类

 */

class Player
{
public:
    /* 访问说明符：
     *  1、包括public，private
     *  2、作用范围：从访问说明符到下一个访问说明符之间。或者到类的结尾
     * public:
         1、定义：
            （1）访问说明符。要使用以下属性，必须声明public。
            （2）public之后定义了类的接口
         2、对class而言，如果不声明，默认private。
    * private：
     *  1、定义：
     *      （1）private的成员只能被类的成员函数访问。private封装了类的实现细节。
     *      （2）private之后定义了类的实现
     *  2、对struct而言，如果不声明，默认是public。
     */
    int x,y;
    int speed;

    void Move(int a,int b)
    {
        x+=a;
        y+=b;
    }

    void Count () const  // 即使成员函数加const，表示函数中的成员变量不可变，mutable的成员变量仍可变
    {
        itemNum++;
    }

private:
    /*
     * 可变数据成员：
     *  （1）目的：使类的某个数据成员可修改，即使在const的成员函数中
     *  （2）方法：成员变量前加mutable
     */
    mutable int itemNum;
};

void Move(Player& player,int a,int b)
/*
 我们可以将class中的function提出，成员函数仍可以对成员变量操作
 1、需要在传参中传入object Player
 2、在成员变量前加上类名，直接对成员变量操作。例如： Player ：：Move
 */
{
    player.x+=a;
    player.y+=b;
}



void class_test()
{
    Player player1;//实例化一个object（Player），得到instance（player1）
    player1.x=5;
    player1.y=5;
    cout<<"x before inside move:"<<player1.x<<"y before inside moeve:"<<player1.y<<endl;
    player1.Move(-1, -1);
    cout<<"x after inside move:"<<player1.x<<"y after inside move:"<<player1.y<<endl;


    Move(player1,100,100);
    cout<<"x after outside move:"<<player1.x<<"y after outside move:"<<player1.y<<endl;

}



//----------------------------------------------------------------------------------------------------------------------
class Log
{
public:
    const int kLogLevelError=0;
    const int kLogLevelWarn=1;
    const int kLogLevelInfo=2;
private:
    int m_level=kLogLevelInfo;
public:
    void SetLevel(int level)
    {
        m_level=level;
    }
    void Error(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelError)
            cout<<"[Error:]"<<message<<endl;
    }

    void Warn(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelWarn)
            cout<<"[Warning:]"<<message<<endl;
    }

    void Info(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelInfo)
            cout<<"[Info:]"<<message<<endl;
    }

};

void LogTest()
{
    Log log1;
    log1.SetLevel(log1.kLogLevelInfo);
    log1.Info("Hello World!");
    cin.get();
}