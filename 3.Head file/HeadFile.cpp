# include <iostream>
using namespace std;

/*
 系统的library分为c standard library和c++ standard library。
 如果是c standard library的文件后缀带.h
 如果是c++ standard library的文件则没有后缀
 */

//void Log2(12.const char* message);
/*
 declearation

 declearation的作用就是，告诉linking，Log2一定存在于其他文件的某处， 你去给我找去。找的时候会依据 函数名+signature来找
 如果你没找到，那也会报错，报错的内容是你没有定义该函数。

 因此，只要不是在当前file下定义的内容，你就一定要声明这东西一定存在于这个project的某处，不然你就不能用。

 */

/*
 head的作用（和import相似）

 可是时候问题就来了，如果我们在这个project里面，随时都要用到这个log2的函数，那么难道我每次都要写这句话么？那如果我有
 100个function，难道每次都这们写100句declearation么

 于是就有了head！
 head的作用就是复制粘贴，你写啥他就粘贴啥，就很简单，因此我们可以把100句的declearation都放在head里面，一句
 include，就解决问题了。这时候，所有的declearation就被复制粘贴到此处了。

 这里我们用一句# include log.h就把log.h里全部的内容都复制粘贴过来了

 */
# include "Log2.h"

/*
 #的作用
#表示，所有的内容都是被preprocess的

*pragma once
定义pragma once的作用是防止一个head file在一个translating unit（一个cpp文件） 中复制多次！！！
 pragma once在这里就会体现了， Log.h的include导致Log2.h中的内容在这里被复制了2次
可是由于pragma once的作用，让preprocess的时候，Log2.h中的全部内容，在一个file里只能出现一次的缘故，
Log.h并没有在preprocess的过程中真的被复制过来!!
*/

/*
 include 为何有时候用<>有时候用“”!!!
 <>表示include系统自带头文件
 “”表示include用户自定义头文件（如果该自定义头文件不在当前文件夹中，需要写出路径），有时“”可以替换<>.
 */


void InitLog()
{
    Log2("Initialzing Log");
}

void head_file(){
    cout << "Hello Word!" << endl;
    Log2("this is a Log function");
    InitLog();
}

