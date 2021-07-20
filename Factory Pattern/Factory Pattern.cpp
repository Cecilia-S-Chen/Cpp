#include <iostream>
using namespace std;
/*
 * 参考：https://zhuanlan.zhihu.com/p/83535678
 *
 * 工厂模式：
 * 一、定义：
 *  存在继承关系的类，通过一个工厂类创建对应的子类（派生类）对象。在项目复杂的情况下，可以便于子类对象的创建。
 *
 * 二、工厂模式分类：
 *  简单工厂模式、工厂方法模式、抽象工厂模式
 *
 *  **简单工厂模式**
 *  1、组成：产品类+工厂类（生产产品）
 *      （1）工厂类：工厂模式的核心类，会定义一个用于创建指定的具体实例对象的接口
 *      （2）抽象产品类：是具体产品类的继承的父类或实现的接口
 *      （3）具体产品类：工厂类所创建的对象就是此具体产品实例
 *
 */

class Shoes {
public:
    virtual void Show() = 0;
};

class NikeShoes : public Shoes{
public:
    void Show() {cout << "Nike : Just do it" << endl;};
};

class AddidasShoes : public Shoes{
public:
    void Show() {cout << "Addidasv : Impossible is nothing" << endl;}
};

class LiNingShoes : public Shoes {
public:
    void Show() {cout << "LiNing : Evering thing is possible" << endl;}
};

enum ShoesType {
    Nikes,
    Addidas,
    Lining
};
class ShowFactory {
public:
    /*
     * 栈内存：在编译时能确定内存大小，开辟内存在栈上
     * 堆内存：在函数运行是才能确定的内存大小，开辟内存在堆上
     *
     * 在堆上开辟内存使用new
     * 1、new工作流程：开辟内存，调用构造函数初始化内存
     * 2、new返回：指向该内存首地址的指针
     *
     */
    Shoes *CreateShoes (ShoesType shoesType) {
        switch (shoesType) {
            case Nikes :
                return new NikeShoes();
                break;
            case Addidas:
                return new AddidasShoes();
                break;
            case Lining:
                return new LiNingShoes();
                break;
            default:
                break;

        }
    }

};

int main() {
    ShowFactory factory;
    Shoes *nikeShoes = factory.CreateShoes(Nikes);
    if (nikeShoes == nullptr) {return 0;}
    else {nikeShoes->Show();}

    Shoes *addidasShoes  = factory.CreateShoes(Addidas);
    if(addidasShoes == nullptr) {return 0;}
    else {addidasShoes->Show();}
}
