#include <iostream>
using namespace std;

int main() {
    const double pi = 3.14;
    double d = 2.123;
    double d2 = 3.123;
    int i = 3;
    /*
     * 指针分为两个部分：指向的地址（地址），被指的东西（地址里存的东西）
     * 12.const * ptr_name 表示被指的东西不能变，指向的地址可以变
     * *12.const ptr_name 表示指向的地址不能变，被指的东西可以变
     */
    const double *ptr = &pi;
    ptr = &d;

    double *const piptr = &d;
    *piptr = d2;

    const int ci = 1;
    auto e =  &ci;
    const int *ptr_e = &ci;

    /*
     * 顶层const和底层const
     * tips：
     *      1、可以用 常量 or 非常量 初始化 常量；不能用 常量 初始化 非常量  eg. int &i = 42 //不正确，因为42是常量，i是非常量引用
     *      2、函数重载的区别不能是顶层const的有无。
     *          eg. Record lookup(Phone*)
     *              Record lookup(Phone* const)
     *                 区别在于指针是否是const，有无顶层const，不能作为函数overload的依据
     *      3、函数重载的依据可以是底层const的有无。
     *          eg. Record lookup(Phone*)
     *              Record lookup(const Phone*)
     *                 区别在于指针指向的对象是否是const，有无底层const，作为函数overload的依据
     */
}

