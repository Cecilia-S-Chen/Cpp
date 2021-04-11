

/*
对于data type，我们唯一在意的并不是名称，我们在意的不过就是所占内存的大小而已。
与python不同，c++没有很多的规则必须要遵守，c相对来说还是比较直接的对内存进行操作的。因此即使出现的array的超出范围，也没有关系
这一方面是c的弊端，因为这让编程要在意的东西很多，因为规则不是很多，编译器并不会报错。
但是这也是优点，这意味着c语言的使用更加的灵活多变。

例如我们不用在乎变量是char还是int，随便用，只是解释方式不同而已，对应的内存中的二进制是相同的。
 e.g. char='A',print结果是A；char=65，print结果还是A；char=63,print结果还是是 ？。我们得到一个data，然后再根据指定类型将data转化成相应的结果！


1 Byte = 8 bits

*整型数据
int     4 Byte    只能存下正负 2billion的值 2^31 其中一位用来表示正负号。
unsigned int   没有正负号， 可以存 2 ^ 32个数， 如果是负数，就会得到补码。
char    1 Byte
short   2 Byte
long    4 Byte  一般是4个 compiler不同可能不同
long long  8 Byte

*小数数据类型
float   4 Byte
double  8 Byte

bool  1 Byte   虽然1（true）和0（false）只占1bite，但是因为地址只能索引到Byte级别，所以分配给boolean 1Byte

*/
#include <iostream>
void variable() {
    int variable=8;
    std::cout<<variable<<std::endl;

    char v2=65;
    std::cout<<v2<<std::endl;

    float v3=5.5f;//区别float和double的关键是在数值之后是否有f!
    std::cout<<v3<<std::endl;

    double v4=5.5;
    std::cout<<v4<<std::endl;

    bool v5="A";
    std::cout<<v5<<std::endl;//对于boolean变量，只有0和false代表“false”，print结果是0。其余(数字/char)都表示“true”。print结果是1

    // sizeof 函数可以查看内存空间
    std::cout << sizeof(v4) <<std::endl;
    std::cout << sizeof(v5) <<std::endl;

}

