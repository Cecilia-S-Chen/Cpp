#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
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
    Screen& rollBack();

private:
    pos cursor = 0; // 光标的位置
    pos height = 0, width = 0; // 表示屏幕的高，宽
    string contents;
};


Screen& Screen::set(char c)
{
    contents[cursor] = c;
    /* code 内存 保存成员变量
     * ｜val1｜obj1
     * |val2|
     * |....|
     * |val1|obj2
     * |val2|
     * |....|
     *
     * 代码内存 保存成员函数，不同的成员变量共用这一段代码内存的成员函数！！！
     * |void print() {using val1}|
     * this可以帮助确定print中val1指的是哪个对象中的val1
     *
     * this
     *  1、定义：表示把 对象 当成整体访问，this为指向该对象的指针
     *  2、目的：因为不同对象使用同一段代码内存，为了区别当前函数中的成员变量属于哪个对象，所以规定了this指向当前调用这个函数的对象，
     *      成员变量为this所指的对象对应的成员变量
     * return *this的成员函数：
     * 1、定义：表示返回调用当前函数的 对象(this指针解引用) 。类中的成员函数，this指的是该类实例化的对象（因为只有该类才会调用自己的成员函数）
     * 2、tips:
     *  （1）return *this：表示返回调用成员函数的当前对象的引用
     *  （2）如果成员函数指针是const，return *this返回的是对象的常量引用！！！（返回的引用将无法修改）
     *      若成员函数是const，为避免无法修改返回对象的引用，通常重载const成员函数，使其变为非成员函数。（有无底层const可以作为函数overload的依据）
     *      在调用该函数时，根据对象是否是const，决定调用常量成员函数还是非常量成员函数
     *  */
    return *this;
}


inline const Screen& Screen::display() const
{
    cout << "const Screen" << contents << endl;
    return *this;
}

inline Screen& Screen::rollBack() {
    cout << "Screen roll back" << endl;
    cursor = height = width = 0;
    contents = " ";
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