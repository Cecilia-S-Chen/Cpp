#include <iostream>
using namespace std;

// ---------------------------值传递与引用传递：-----------------------------------------------
void reset(int *ip) {
    *ip = 0;
    ip = 0;
    cout << "new ip is : " << ip << endl;
}

void print (int (&Rarray) [10]) {
    for (auto elem : Rarray) {
        cout << elem << endl;
    }
}

int main() {
    /*
     * 一、值传递与引用传递：
     * 值传递例子：将i的地址值传递进函数reset中
     */
    int i = 42;
    cout << "old ip is :" << &i << endl;
    reset(&i);
    cout << "old ip is :" << &i << endl; // ip不变，ip对应的值变化
    cout << "i = " << i <<endl;

    /* 形参和实参：
     * 1、初始化时实参个数必须和形参相同
     * 2、如果形参有默认实参，则初始化时可以省略对应的实参
     * 3、函数的某个形参有默认实参，之后的所有形参都必须有默认实参！！！
     * 4、默认实参，在函数声明中指定；
     * const形参和实参
     * 1、普通 const 和 非const 形参：
     *      传入的实参可以是const，可以是非const。值传递不保留顶层const
     * 2、指针或引用形参：
     *      值传递保留了底层const。
     *      只能用 const 或 非const 初始化 const 指针或引用 形参（保证指向同一块内存的新对象不会对不能更改的内存进行修改）
     *      不能用 const 初始化 非const 指针或引用 形参 （不能保证指向同一块内存的新对象不会对不能更改的内存进行修改）
     */

    int k[10] = {0,1,2,3,4,5,6,7,8,9};
    print(k);

    /*
     * 返回值：
     * 一、返回数组指针
     *      （1）定义：数组不能拷贝，不能返回数组，只能返回数组的指针或引用
     *      （2）表达式：type （*fucntion（parameter_list））[dimension]
     *           尾置返回类型：auto function(parameter_list) -> type(*)[dimension]
     */



    /*
     * 内联函数：
     * 1、定义：在 编译时 ，在函数调用点，将函数内容黏贴替换函数名
     * 2、与include的区别：
     *      include是在 编译前 ，将include的文件黏贴在相应位置
     */


}


