#include <iostream>
using namespace std;

class Log
{
public:
    const int kLogLevelError=0;
    const int kLogLevelWarn=1;
    const int kLogLevelInfo=2;
private:
    int m_level = kLogLevelInfo;
public:
    void SetLevel(int level)
    {
        m_level=level;
    }
    void Error(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelError)
            cout<<"[Error:]"<<message<<endl;
    }

    void Warn(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelWarn)
            cout<<"[Warning:]"<<message<<endl;
    }

    void Info(const char*message) //表示把message的地址传入function，function直接对message本身操作，而不是对message的copy操作
    {
        if(m_level>=kLogLevelInfo)
            cout<<"[Info:]"<<message<<endl;
    }

};

void LogTest()
{
    Log log1;
    log1.SetLevel(log1.kLogLevelInfo);
    log1.Info("Hello World!");
    cin.get();
}