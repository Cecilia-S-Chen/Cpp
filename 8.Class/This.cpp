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

/*
 * inline：
 * 1、定义：
 *      对于规模较小的函数，在 定义前 加上inline，表示将该函数定义复制在该函数的各个调用点处。
 * 2、tips：
 *  （1）定义 在类内部的函数 自动内联
 *  （2）声明 在类内部的函数 不是内联！！除非在类外部定义该函数前，加上 inline
 *  （3）在函数的 定义前 加上inline，函数为内联函数
 */
inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    /*
     * this
     *  1、定义：表示把 对象 当成整体访问，this为指向该对象的指针
     * return *this的成员函数：
     * 1、定义：表示返回调用当前函数的对象。类中的成员函数，this指的是该类实例化的对象（因为只有该类才会调用自己的成员函数）
     * 2、tips:
     *  （1）return *this：表示返回调用成员函数的当前对象的引用
     *  （2）如果成员函数指针是const，return *this返回的是对象的常量引用！！！（返回的引用将无法修改）
     *      若成员函数是const，为避免无法修改返回对象的引用，通常重载const成员函数，使其变为非成员函数。（有无底层const可以作为函数overload的依据）
     *      在调用该函数时，根据对象是否是const，决定调用常量成员函数还是非常量成员函数
     *  */
    return *this;
}
inline Screen& Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}
inline Screen& Screen::move(int a, int b)
{
    height += a;
    width += b;
    return *this;
}

inline  Screen& Screen::display()
{
    cout << "unconst Screen" << contents << endl;
    return *this;
}
inline const Screen& Screen::display() const
{
    cout << "const Screen" << contents << endl;
    return *this;
}

int main ()
{
    Screen myScreen(5,3 ,' ');
    const Screen blank(5,3,' ');
    /*
     * 因为Move返回的是myScreen的引用，所以相当于在myScreen上移动光标后，修改myScreen光标对应的位置的内容
     * 如果返回的不是引用，则set修改的是myScreen的副本，不是myScreen本身
     */
    myScreen.move(4,0).set('#').display(); // 非常量对象调用非常量display
    blank.display(); // 调用常量display // 常量对象调用常量display
}