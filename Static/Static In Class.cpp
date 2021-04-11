# include <iostream>
# define Print(message)  cout << message << endl
using namespace std;


/*
                        1. static在class或者structure中
 定义：
 当static在类或class内部的时候，就是类变量或类函数！ 即所有以该class实例化的instance，都将会share这个staticvariable
 或者method。

 使用方法：
 1. 类中的全局变量（改一个instance的类变量，所有的都发生了更改）
 2. 不实例化也可以用 但是要用"::"， 而不是“.”。（即： “类::类变量” 或者 “类::类方法” 都是合法的）
 3. ！！！！！static method只能manipulate static variable！！！！！
    我们要记住， static method和static variable 均不属于某一个instance，因此static method没有办法获取instance variable， 他们根本不是一家人，信息也不可以互通。
 4. static 成员变量的初始化一定不能在任何函数内部：
    （1）通常在类外部定义
    （2）字面值常量（constexpr）的常量成员变量可以在类内初始化，初始值必须是字面值常量表达式
     (3)无论成员变量是否在类内初始化，都应该在类外部，不带初始值的，再定义一下（将类内初始化 和 类内没有初始化 两种情况拉齐）
 6、在类内声明，在类外定义的静态成员函数，只能在声明前加static！！！
 综上所述：
 instance是属于类的，但类变量或者类函数却并不属于instance的。因此instance可以share 类函数或者类变量，
 但是类函数无法获取 instance variable。 因此static method中只能有static variable，不可以出现 instance variable。


  *********** static function ********
 编译器在编译一个普通成员函数时，会隐式地增加一个形参 this，并把当前对象的地址赋值给 this，所以普通成员函数只能在创建对象后通过对象来调用，
 因为它需要当前对象的地址。而静态成员函数可以通过类来直接调用，编译器不会为它增加形参 this，它不需要当前对象的地址，所以不管有没有创建对象，
 都可以调用静态成员函数。
普通成员变量占用对象的内存，静态成员函数没有 this 指针，不知道指向哪个对象，无法访问对象的成员变量，也就是说静态成员函数不能访问普通成员变量，
 只能访问静态成员变量。
普通成员函数必须通过对象才能调用，而静态成员函数没有 this 指针，无法在函数体内部访问某个对象，所以不能调用普通成员函数，只能调用静态成员函数。

                                ***  例子 ***
 */
struct Entity{
    int x, y;
    static int z;
    static constexpr int period = 30;
    /*
     * 静态成员独有的使用场合：
        1、（1）静态数据成员可以是不完全类(当声明和定义分离，类已经声明了，但是还没有定义)
           （2）非静态成员 只有指针 或 引用成员可以是不完全类
           类初始化对象，对象 包含 所有非静态成员变量和成员函数，所有的变量都应该是完全类型（只有组成部分完整了，这么对象才完整！）
                        非静态成员变量和函数不属于对象，所以对象初始化时，不要非静态成员是完全类型

        2、静态数据成员可以作为默认实参
            因为在对象初始化时，非静态数据成员才分配内存，一个自身可能都没有分配完内存的成员变量怎么初始化其他成员变量？
            在类存在时，静态成员变量已经存在，所以对象初始化时，已经存在的静态成员变量可以初始化其他非静态成员变量！
     */
    static Entity e1;
    Entity *e2;
    Enttity e3;

    void print(){
        cout << x << ", " << y << ", " << z << endl;
    }




    static void method(){
        cout << z << endl;
    }
};

/*
 在class外面的static和class里面的static不同， 只要调用了该函数，那么e一定是已经被实例化过了，那么对于该函数而言，e一定产生了。
 */
static void print(Entity e){
    cout<< e.x << endl;
};



int Entity :: z; //类变量不属于instance， 因此要先声明，后用。 ::表示作用域的符号。表示z是Entity的z，此做法是为了保证class有相同属性的时候能不混淆。











/*
 ————————————————————————————————————————————————————————————————————————————————————————

                       2. static在class外部 （静态全局变量）

其功能为，将 *变量* 或者 *function* 对当前cpp文件的私有化。让其他cpp file无法获取到该文件中的static变量和函数。
而不用static的变量，外部file却可以通过一些方法（extern type name;）获取这个file下的变量。因此就要求变量定义不得重复了

 使用方法总结
 对于static在class外部的情况，使用原则为：对于variable和function， 能用static，就用static
 即*只要不是非要被其他cpp文件调用，就要用static，无论是函数还是变量。

                               *** 例子 ***
 */
int num = 7;
/*
 全局变量可以与static变量重名。
 这里我在其他文件里面就定义了一个名叫num的变量，虽然不在一个文件下，但是仍然是全局变量。可是如果我在前面加一个static，就让作用范围变成了文件内部，就不冲突了。
 */


//如何使用其他cpp file中定义的全局变量（注意：function不需要extern来linking）：
extern int num2;
/*
 获取其他cpp file的全局变量。
 extern的作用是把其他file中的非static变量给直接引入过来。
 这个工作原理就是， linking会自动的去在外部file中寻找定义过的int，然后拿过来
 */

// 这个方法同样也适用于function，即 static void function(){}则表示的是该function实际上只在当前cpp中有效。
void function_test(){}









/*
 ————————————————————————————————————————————————————————————————————————————————————————

                               3. local static
 静态变量定义于函数之内，静态局部变量具有局部作用域。它 ***只被初始化一次***， 自从第一次被初始化  ***直到程序运行结束***
 都一直存在，它和全局变量的区别在于全局变量对所有的函数都是可见的，而静态局部变量只对定义自己的函数体始终可见。

 这里就又回到scope的概念了，scope是linking建立了，指的是能被linking连接起来的的区域为一个scope。
 而在一个scope里面，我们不可以有两个相同的定义变量，否则linking就很疑惑，我应该怎么连接。
 而static的用法就是改变scope，或者叫linking的作用范围。


静态局部变量   function() { static int num }
关键点就三个
1. 只初始化一次。
2. 一直存在到程序结束
3. 只在local内可以看到。
*/




void static_local_var(){
    static int i = 5;   //这里i并不会被重置，因为i一直存在，但是只有函数内部才能看到而已
    i++;
    cout << i << endl;
}


int gVar = 0; //全局变量

void global_var(){
    gVar++;   //函数内也可见
    cout << gVar << endl;
}



/*
 ————————————————————————————————————————————————————————————————————————————————————————

                        ！！！！！因此什么是static？！！！！！！！！

static指的是相对于不加static而言的变量而言是 相对静止的，不消失，不出格的。
对于class之外的static而言，是对应全局变量的静态的 *不出格*，指的是变量会*静静地*躺在当前cpp file中，不会跑到别的cpp file中。
对于class内部的static而言，是对instance variable而言的的 *相对静止的*，指的是只要类出现了，类变量就会一直静静在那里，
    并被所有instance共享。不会随着instance的出现或者消亡而消失。
对于local static而言（在function 或者for循环中的），static是对local variable而言的 *不消失的*， local variable
    在scope结束就消失了，但是static local 并不会消失，他还在内存中，当你再次进入到local的时候， 他还是原来的那个变量。
    但却只初始化一次。
*/


// —————————————————————————————— test ————————————————————————————————————————————
void static_test(){
    Print(num2);
    Entity e1 = {3,4};
    Entity e2 = {6,7};
    e2.z = 100000;
    e1.print();
    e2.print();

    //直接使用类来赋值，效果是一样的。
    Entity::z = 0;
    e1.print();

    //测试local var
    for (int i = 0; i < 5; i++){
        static_local_var();
    }


    //global var test
    for(int i =0; i < 5; i++){
        global_var();      //任何函数都可见

    }
}
