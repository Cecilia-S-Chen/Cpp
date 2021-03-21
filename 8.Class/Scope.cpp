#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
    /*
     * tips：
     *  （1）定义类型别名为了向用户隐藏实现细节（用string类型存储数据）
     *  （2）类型别名必须 先定义后使用 ，这与成员变量可以先使用后定义有所不同
     */
    typedef string :: size_type pos; // 也可以用 using pos = string :: size_type 来定义类型的别名
    Screen (pos h, pos w, char c) {
        height = h;
        width = w;
        c = ' ';
    }
    Screen& set(char);
    Screen& set(pos, pos, char); // 声明，不需要写函数名，只要声明函数类型即可
    Screen& move(int a,int b);
    Screen& display();
    const Screen& display() const;

private:
    pos cursor = 0; // 光标的位置
    pos height = 0, width = 0; // 表示屏幕的高，宽
    string contents;
};

class Window_mgr{
public:
    // ScreenIndex表示窗口的编号类型
    using ScreenIndex = vector<Screen> :: size_type;
    // 向窗口添加一个Screen，返回它的编号
    ScreenIndex addScreen(const Screen&);

private:
    vector<Screen> screens{Screen(24, 80, ' ')};
};
/*
 * 函数的作用域有函数名前的类名规定,Window_mgr::addScreen
 * 返回类型的作用域由返回类型前的类名规定,Window_mgr::ScreenIndex
 * 函数的作用域和返回类型所属的作用域可以不同！！！
 */
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

/*
 * 名字查找：
 *      1、在 该名字出现之前 的当前作用域查找定义
 *      2、如果找不到，向上的外层查到
 * 类的作用域：
 *      1、编译所有成员声明，所有声明中的内容（返回类型，传入参数），必须在声明前就定义好
 *      2、类全部可见后编译函数体，所以函数体中使用的成员变量可以在函数后边出现！！（如果是类外的函数，则函数体内的变量要在使用前就定义好！）
 */
typedef double Money;
int temp = 0;
class Account {
public:
    Money balance()
    {
        return bal;
    }

private:
    /*对 类作用域 而言：
     *  如果成员使用外层作用域的名字，且该名字代表一种类型，类之后就不能重新定义该名字了！
     *对 普通作用域而言：
     *  内层作用域可以重新定义外层作用域的名字，即使该名字在内层作用域中已经使用过了
     *  例如：在函数中定义函数外定义过的变量
     *
     */
    // typedef int Money; // 错误！因为之前在函数外已经定义了Money，balance 函数也会使用之前定义好的Money，此处再定义Money属于重复定义的错误，只是编译器没有相关报错
    Money bal; // balance中可以先使用了bal，之后才定义，这与类先编译声明，后编译函数体的规定有关

};

void changeTemp()
{
    int result = temp +1;
    cout << result << endl;
    int temp = 5; //
    cout << temp <<endl;
}

int main ()
{
    changeTemp();
}