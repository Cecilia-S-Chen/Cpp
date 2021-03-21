#include <iostream>
#include <cassert>
#include <string>
using namespace std;

int main() {
    /*
     * 调试：
     * assert：
     * 定义：预处理宏，检查"不能发生"的条件
     * 表达式：assert（expression）
     *      如果expression为true，则assert不做处理；如果为false，则assert终止程序并且输出信息
     * NDEBUG：
     *
     * 自定义输出错误信息：
     * 1、__FILE__
     * 2、__LINE__
     * 3、__TIME__
     * 4、__DATE__
     * 5、__func__:输出当前调试的函数的名字
     *
     */
    string word;
    size_t threshold = 7;
    cout << "Input a word : " << endl;
    cin >> word;

    assert(word.size() > threshold); // 要求所有输入的单词都大于阈值7

    if (word.size() < threshold) {
        cerr << "Error : " << __FILE_NAME__
             << " : in function " << __func__
             << " at line " << __LINE__
             << " Compile on " << __DATE__
             << " at " << __TIME__ <<endl;

    }

}
