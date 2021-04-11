#include <iostream>
#include <string>
using namespace std;

/*
 * 函数指针：
 * （1）表达式：return_type (*function_pointer_name) {type1, type2}
 *            1、函数指针定义的是一种类型的函数，它可以看作一个变量
 *            2、函数指针类型不能通过定义结构体实现，函数指针类型只能声明。
 *            3、相同类型，不同实现的函数可以赋给函数指针变量，由函数指针变量进行传递
 * （2）注意点：return_type *function_pointer_name {type1, type2}
 *          加括号表示，返回类型是return_type,不加括号表示返回类型是指向return_type的指针！
 *
 *  2、核心：函数指针表示一类函数，将函数指针指向某个具体函数时，可以通过函数指针调用该函数
 *          函数指针->类
 *          某个函数->对象
 *  3、应用：注册函数，函数回掉，观察者模式
 *          将函数指针作为para list（传入参数类型），可以传入同一类型不同的函数
 */

bool lengthCompare (const string &str1, const string &str2) {
    if (str1.size() > str2.size()) {
        cout << str1 << " is longer" << endl;
    } else {
        cout << str2 << " is longer " <<endl;
    }
}

bool (*lengthComparePointer) (const string &, const string &);




int Add(int lhs, int rhs) {
    return lhs + rhs;
}

int Multiplex(int lhs, int rhs) {
    return lhs * rhs;
}

void Mulnipulate(int lhs, int rhs, int(*munipFunc)(int, int) ) {
    cout << munipFunc(lhs, rhs) << endl;
}




int main () {
    // ---------------------------------函数指针-----------------------------------------------
    // l1,l2,l3等价
    bool l1 = lengthCompare("Cecilia", "Allen"); // input是const string，所以实参可以是字面值
    lengthComparePointer = lengthCompare;
    lengthComparePointer = &lengthCompare; //与上面定义等价

    // 由函数指针实现函数作为变量传递
    Mulnipulate(3, 4, Add);
    Mulnipulate(3, 4, Multiplex);

    /*
     * 重载函数的指针：
     *  使用已有函数定义重载函数指针时，必须保证已有函数和重载函数指针是精确匹配
     */
    bool (*pf) (const string &str1, const string &str2) = lengthCompare;

}