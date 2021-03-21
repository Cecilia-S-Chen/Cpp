//#pragma once

//下面这是一个比较古老的方法 效果和pragma once相同
#ifndef _LOG_H //如果没有define _LOG_H，ifndef表示if not define!
#define _LOG_H //那就define一个，否则就不定义

void Log2(const char* message);

struct Playe{};
/*
 如果没有pragma once，当我们同时include Log2.h和Log.h。struct Player将会被复制两次，在build时会出现duplicating error
 */
#endif


