//
// Created by pikachu on 2020/4/11.
//

#include <iostream>
#include <string>
#include <utility>
#include <exception>
using namespace std;


//customized exception class 'myException'
class myException:public exception
{
public:
    myException(const string &msg) : msg(msg) {}

    const char* what()const throw()//#1
    {
        return msg.c_str();
    }

private:
    std::string msg;
};
void check(int y)
{
    if(y==0) throw myException("y is 0");
}
//entry of the application
int main()
{
    int x=100,y=0;
    try
    {
        throw "???";
    }
    catch(std::exception& me)
    {
        cout<<me.what();
    } catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}