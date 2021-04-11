
//--------------------------------overload---------------------------------------------------
void overloadExample() {
    cout << "zero para" << endl;
}
void overloadExample(int paraOne) {
    cout << " para one is : " << paraOne << endl;
}
void overloadExample(int paraOne, int paraTwo) {
    cout << "para One is : " << paraOne << "para Two is : " << paraTwo << endl;
}
void overloadExample(double paraOne, double paraTwo = 3.14) {
    cout << "para One is : " << paraOne << "para Two is : " << paraTwo << endl;
}

/*
 * overload：
 * （1）定义：函数名相同，形参的个数或类型不同
 * （2）不能判定为overload：
 *      1、返回值不同
 *      2、parameter list只有形参名不同
 *      3、parameter list只有 顶层const 有无不同
 *      4、形参类型可以相互转化！
 * 函数匹配：
 *  1、确定候选函数集合：
 *      （1）与被调用函数重名
 *      （2）在其声明调用点可见
 *  2、确定可行函数：
 *      （1）形参数量与本次调用的实参数量一致
 *      （2）形参类型与实参类型一致，或者可以类型转化
 *  3、寻找最佳匹配：
 *      最佳匹配的函数所有形参匹配度 >= 其他可行函数的形参匹配度
 *      如果可行函数分不出优劣，则编译器会报告二义性调用
 *  tips：
 *  编译器逻辑：先查找后匹配。先查找，即确定候选函数集合。后匹配，集合内所有函数都匹配不上，就会直接报错。不会再去外层查找。
 */
overloadExample(5.6);
overloadExample(5);
// overloadExample(5.6,3); 没有办法从可行函数中选出最佳匹配，编译器报告二义性调用！