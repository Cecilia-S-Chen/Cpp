

/*
 c++文件编译过程：
 我们编写出多个cpp文件->多个cpp文件compile成多个object file（将c++转化成机器语言）->之后再把obj file通过link合并成一个exe
 ----------------------------------------------------------------------------------------------
 *详细讲解 compile

 1. compile与head之间的关系

 在compile中， head文件是不会被compile的， 只有cppfile会被编译， 而head文件是通过 include被粘贴在cppfile的相应位置之后，
 成为了cpp file中的一部分，而cpp file被编译的时候，这时候被粘贴过来的 head文件也就相应的被编译了。 这就是head file与compile
 之间的关系。

 2. compile与cpp的关系

 compile的过程中，每个cpp文件之间是被互相独立的编译的。互相之间没有任何影响和互动。而在windows中，这些cpp file在被编译之后，
 会成为.obj文件。cpp与obj之间是一一对应的关系。

 因此compile 的目的就是相互独立的 把一堆cpp变成另一堆obj文件。



 ** compile中的pre-process **
 pre-process 主要指的是

1.#include: 针对头文件的复制粘贴与
    include <head_file>: 在这里，include的作用是将 head_file.h的头文件， 直接 *粘贴* 在当前文本的。*当前位置*即可。

2.#define A B
    用A来代替B，这就是一个简单的文本替换问题而已。例如 #define Integer int, 既 编译的时候，编译器会执行
        1） 查找 Integer
        2） 替换全部Integer为int。

3. #if  与 # endif

         #if 条件

         正常写代码就行了

         #endif

     则当条件成立的时候，中间的代码会被编译，否则就不会被编译

4. constant
  对于有些constant的变量， preprocess的过程中，会将constant直接带入到相应的变量中。从而减少复杂度。
------------------------------------------------------------------------------------------------

*link 作用

*linking是在compile之后，要把各个file之间的关系联系起来，比如当前file是有用到其他file的函数或者变量，这是，linking出现把他们联结起来，
一连接起来，就会发现问题了。比如你在当前文件里声明说有个函数叫LOG。结果linking去别的file里一找，发现并没有，这就叫linking error

*我们可以知道，Link 的作用和工作原理了,
 Link在你声明的时候，会产生一个link，而这个link里面的内容，如果没有被执行，那就根本不会接触到。如果一但执行了，那么当前函数，就会通过一个link，接入到log函数的文件中去，这时候，如果发现没有这个文件，那就会产生link error

 * linking和include的区别
include是单纯的复制粘贴，并在preprocessing的时候完成的，而linking并没有复制粘贴，只是编译在一起，从而可以互相调用

 由于include的这个复制粘贴的特性，和linking 通过signature和name唯一确定linking对象的特性，
 千万不要在head里面定义非static的function，然很容易在include的时候，重复定义了某个对象。

 如何在head file中定义一个function：
 1. head file中定义static function.
 2. head file中只有declaration（声明）, defination只在某个cpp文件中出现了一次。因此也不会有重复定义的问题了
 -----------------------------------------------------------------------------------------------

 * 声明的作用
 声明的作用主要分成两个部分来实现：compile和linker

 1. 声明对于compiler的作用： 给compiler一个已经在其他文件中被定义好了的承诺。
    compiler在编译的时候，必须保证让每个变量或者函数都被定义过，但是因为有些函数和定义的位置并不在当前的文件中，
 而cpp的编译又是相互独立的。因此compile就会感到迷茫，并报错，认为当前变量没有被定义过。
    而声明只是给出一个函数或者变量的signature.没有body， 而这么做的意义可以告诉compiler， 当前这个文件中， 对应这个signature的函数，我已经定义过了，你放心用。至于这个函数是否真的被定义过，定义的是否恰当，compiler其实是不关心的。 compiler会无条件的相信声明的
 因此定义和声明是一个函数可以被使用的两个关键步骤， 定义，是把函数的全部定义出来，其包括 signature + name + body
 ，而声明是在对外（compiler和linker）宣称，这个函数我已经在别的cpp文件中定义过了。你只管用即可。 且只包含 signature + name，
 没有body。

    ie：
        定义：
        void Print(12.const char* message){
            cout<< message <<endl;
         }

        声明：
        void Print(12.const char* message);

 2. 声明对于linker的作用：

 声明的作用主要是通知linking，你要去别的file里面去找这个东西，找到了，我们再来用。
 linking只在compile之后完成的， compile的时候只关心每个独立的文件是否有问题。 至于这个文件和其他文件的*互动*是否正确，他并不知道，因为compile的过程是在每个文件之间独立运行的。

 而linking是在compile之后，要把各个file之间的关系联系起来，比如当前file是有用到其他file的函数或者变量，这是， linking出现，把他们联结起来，一连接起来，就会发现问题了。比如你在当前文件里声明说有个函数叫LOG 结果linking去别的file里一找，发现并没有，这就叫linking error

*/


#include<iostream>
#define INTEGER int //表示用前面的内容INTEGER代替后边的内容int，定义之后我们可以使用INTEGER 或者int
#if 1 //用于将if 和 endif之间的内容做判定后在决定是否对其进行编译，如果if 1表示这之间进行编译， if 0 表示这之间不进行编译。这段就等于删除了。
INTEGER Multiply(int a,int b) {
    INTEGER result = a * b;
    return result;
}
#endif

/*
* static的作用
* 这里，如果我们不再test前面加上static，即使我们用不到test，那么编译也会出错，因为编译器认为，你的test也有可能被别的file调用
* 即使你在main里没有，因此，这时候，编译器要求你的test也必须是合法的。
*
* 但是我们一旦加了static， 就说明， test只存在于当前file中，其他file将不会再使用这个test，那么test就不会被编译，因为这个文件中test没有被用到，编译器压根都没碰到test。
*
* same name same signature
* 如果发生有两个function有完全相同的name和signature，无论body是否一样，调用这个function也会发生linking error，那是因为linking是由name + signature共同决定的， 如果两者相同，就会产生相同的signature，这就会导致linking error
*
*这个情况经常发生在include的head的时候，如果一个head中有function，我们include这个head，就相当于把这个function复制了一遍，多次include这个head file，就相当于有多个相同的function，那么就会出现上述link error。
* 针对head file的link error解决方法：
   1.我们可以采用static的方式把函数的作用域限制在一个file 内
   2.可以采用在function名前加inline。inline表示用function的body替换call function的地方。相当于把function变成一段代码直接执行。避免了call多个相同的function的link error

* same name different signature
* 再有就是，调用一个function，declaration function 和被调用的function， 只要是signature不完全相同， 你就会发现一个linking error。
* 这是因为每个signature对应唯一一个linking， int Log 和 void Log是不同的linking， 而void Log(int nums) 和 void Log( char A)也并不是一个linking，那么自然就也会发生linking error的问题了。
*/
    void trush(int num);
    static void test(){
        trush(1);
    }

/*
*Input是一个declaration，声明了一个function
*Log是一个definition，定义了一个function
*/
    void Input(const char*input);
    INTEGER Multiply(int a,int b);

    void Log(const char*message)
    {
        std::cout<<message<<std::endl;
    }
