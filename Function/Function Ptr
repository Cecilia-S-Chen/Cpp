#include <iostream>
using namespace std;

/*
 * 函数指针：
 * 1、定义：本质是变量，是指向函数内存首地址的指针
 *          所以不能像定义函数一样定义它，只能声明函数指针变量，然后把定义好的函数名赋值给它
 * 2、存在意义：使函数可以像变量一样传递处理，用于工厂函数，回调函数，函数数组等
 * 3、函数指针与函数名的异同点：
 * （1）相同点：都指向函数内存的首地址
 * （2）不同点：对函数指针取&，得到的是指针 变量的地址
 *             对函数名取&，得到的是函数内存首地址
 */

// 基础函数指针
void (*basic) ();
// 普通入参和返回值的函数指针
void (*normal) (int i, double d);
// 普通返回值，入参有函数指针
void (*input_fptr) (int i, int (*normal)(int i,double d));
// 普通入参，返回值为函数指针
void (* ((*retrun_fptr) (int i, double d))) ();
// 入参为函数指针，返回值也为函数指针
void (* ((*return_input_fptr) (int i, void (*basic) ()))) ();

// 基本函数
void basic_name()
{
    cout << "basic function" << endl;
}
// 普通函数
void normal_name(int i, double d)
{
    cout << "normal input function" << endl;
}
// 入参为函数指针的函数
void input_fptr_name(int i, void (*normal) (int i, double d))
{
    cout << "input fptr function" << endl;
}

int main()
{
    basic = basic_name;
    normal = normal_name;
    input_fptr_name(5, normal);

}

