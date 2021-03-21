#include <iostream>
#include <vector>
using namespace std;

/*
 * 一、初始化：
 * 1、（1）初始化长度；（2）初始化元素内容；（3）初始化长度和内容（长度可以多于内容个数，多的部分默认初始化）
 * 2、不允许用auto初始化数组
 * 3、初始化内容不允许为引用
 * 4、字符数组结尾有"\0"
 * 5、与vector不同，不允许拷贝和赋值！！！
 * 二、声明：
 *      注意括号的使用
 */

int* parray[10]; // 包含10个整型指针的数组
int (*Parray) [10];//指向包含10个整数数组的指针
int (&Rarray) [10] = *Parray; //引用包含10个数的数组
// int& rarray [10]; 包含10个整型引用的数组。因为数组的内容是对象，引用不是对象，所以包含引用的数组是错的！


