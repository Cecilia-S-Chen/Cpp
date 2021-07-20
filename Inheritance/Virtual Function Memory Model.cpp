#include <iostream>
using namespace std;

/*
 * 参考：https://zhuanlan.zhihu.com/p/41309205
 *
 * 虚函数内存模型：
 * 原理：
 * 上述的模型中，对于派生类对象，它的基类相对于它的偏移量总是确定的，因此动态向下转换并不需要依赖额外的运行时信息。
 * 而虚继承破坏了这一条件。它表示虚基类相对于派生类的偏移量可以依实际类型不同而不同，且仅有一份拷贝，这使得虚基类的偏移量在运行时才可以确定。因此，我们需要对继承了虚基类的类型的虚表进行扩充，使其包含关于虚基类偏移量的信息。

 * 一、单继承内存模型
 * 虚函数表：
 *      多态类型，其所有的虚函数的地址都以一个表格的方式存放在一起，每个函数的偏移量在基类型和导出类型中均相同，这使得虚函数相对于表格首地址的偏移量在可以在编译时确定。
 *  虚函数指针：
 *      虚函数表格的首地址储存在每一个对象之中，称为虚(表)指针(vptr)或者虚函数指针(vfptr)，这个虚指针始终位于对象的起始地址。

struct A
 object                                            A VTable (不完整)
     0 - vptr_A -------------------------------->  +--------------+
     8 - int ax                                    |    A::f0()   |
sizeof(A): 16    align: 8                          +--------------+
                                                   |    A::f1()   |
                                                   +--------------+

struct B
 object
     0 - struct A                                  B VTable (不完整)
     0 -   vptr_A ------------------------------>  +--------------+
     8 -   int ax                                  |    B::f0()   |
    12 - int bx                                    +--------------+
sizeof(A): 16    align: 8                          |    A::f1()   |
                                                   +--------------+
 *
 * 由于B重写了方法f0()，因此它的虚表在同样的位置，将A::f0()覆盖为B::f0()。
 * 当发生f0()函数调用时，对于实际类型为A的对象，其VTable偏移量为offset0的位置为A::f0()， 对于实际类型为B的对象，对应位置为B::f0()，
 * 这样就实现了运行时虚函数函数地址的正确选择。
 *
 *
 * 例如B中新增加了函数f2()，虚函数表变化如下：
 *  struct B
 object
     0 - struct A                                  B VTable (不完整)
     0 -   vptr_A ------------------------------>  +--------------+
     8 -   int ax                                  |    B::f0()   |
    12 - int bx                                    +--------------+
sizeof(A): 16    align: 8                          |    A::f1()   |
                                                   +--------------+
                                                   |    B::f2()   |
                                                   +--------------+

虚表中的每一项都称作一个实体(entity)
 *
 *对于多态类型，除了要在运行时确定虚函数地址外，还需要提供运行时类型信息(Run-Time Type Identification, RTTI)的支持。，g++将它放在虚函数表的前
 *
 *  struct B                                          B VTable (不完整)
 object                                            +--------------+
     0 - struct A                                  |  RTTI for B  |
     0 -   vptr_A ------------------------------>  +--------------+
     8 -   int ax                                  |    B::f0()   |
    12 - int bx                                    +--------------+
sizeof(A): 16    align: 8                          |    A::f1()   |
                                                   +--------------+
                                                   |    B::f2()   |
                                                   +--------------+
 *
 */

struct SingleA
{
    int ax; // 成员变量
    virtual void f0() {}
    virtual void f1() {}
};

struct SingleB : public SingleA
{
    int bx; // 成员变量
    void f0() override {}; // 重写f0
};

/*
 *
 * 二、多继承内存模型
 *
 * 与单链继承不同，由于A和B完全独立，它们的虚函数没有顺序关系，即f0和f1有着相同对虚表起始位置的偏移量，不可以顺序排布。
 * 并且A和B中的成员变量也是无关的，因此基类间也不具有包含关系。这使得A和B在C中必须要处于两个不相交的区域中，同时需要有两个虚指针分别对它们虚函数进行索引：
 *
 *                                                 C Vtable (7 entities)
                                                +--------------------+
struct C                                        | offset_to_top (0)  |
object                                          +--------------------+
    0 - struct A (primary base)                 |     RTTI for C     |
    0 -   vptr_A -----------------------------> +--------------------+
    8 -   int ax                                |       C::f0()      |
   16 - struct B                                +--------------------+
   16 -   vptr_B ----------------------+        |       C::f1()      |
   24 -   int bx                       |        +--------------------+
   28 - int cx                         |        | offset_to_top (-16)|
sizeof(C): 32    align: 8              |        +--------------------+
                                       |        |     RTTI for C     |
                                       +------> +--------------------+
                                                |    Thunk C::f1()   |
                                                +--------------------+

 *  实体offset_to_top表示的就是实际类型起始地址到当前这个形式类型起始地址的偏移量。
 *  为了弄清楚Thunk是什么，我们首先要注意到，如果一个类型B 的引用持有了实际类型为C的变量，这个引用的起始地址在C+16处。当它调用由类型C重写的函数f1()时，如果直接使用this指针调用C::f1()会由于this指针的地址多出16字节的偏移量导致错误。
 *  因此在调用之前，this指针必须要被调整至正确的位置 。这里的Thunk起到的就是这个作用：首先将this 指针调整到正确的位置，即减少16字节偏移量，然后再去调用函数C::f1()。
 */

struct MultiA
{
    MultiA() {this->f0();}
    int ax;
    virtual void f0() {cout << "A" << endl;}
    ~MultiA() {this->f0();}
};

struct MultiB
{
    MultiB() {this->f1();}
    int bx;
    virtual void f1() {cout << "B" << endl;}
    ~MultiB() {this->f1();}
};

struct MultiC : public MultiA, MultiB
{
    MultiC() {this->f0();}
    int cx;
    void f0() override {cout << "c" << endl;}
    void f1() override {cout << "C" <<endl;}
    ~MultiC() {this->f1();}
};

int main() {
    MultiC multiC;
    return 0;
}


