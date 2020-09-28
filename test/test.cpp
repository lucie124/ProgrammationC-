//
//  test.cpp
//  3IF1020
//
//  Created by 葛钊琦 on 2020/9/28.
//

#include "test.hpp"
#include <iostream>
// #include <unistd.h>
using namespace std ;

//常量
#define d 12 //宏常量 
const int c = 15; //const修饰的变量在main里面定义才有效

/*
数据类型：
    整型：
        int 变量名 = 变量; 
        short (2) / int (4) / long (8) / longlong (16) 
        sizeof() 查看占用内存空间
    浮点型：
        float (4) / double (8)
    字符型：
        char 变量名 = 'a';
        一个字符，单引号。  
        `(数据类型)变量`：强制转换类型 
    转义字符：
        以\开始，\n 换行，\t 水平制表符，\\ 反斜杠
    字符串：
        char 变量名[] = "字符串值"; //c风格
        or
        #include <string>
        string 变量名 = "变量值";   //c++风格
    布尔类型：
        bool 名 = true/false;
        0 - False，1 - True
数据的的输入：
    cin >> variable;
条件语句：
    if(conditions){execution}
    if(condition){execution}elif(condition){execution}else{execution}
三目运算符：
    表达式1 ? 表达式2 : 表达式3
    若1真则执行2 否则3 
switch
    switch(expression){case...defult...}
循环：
    while(condition){} ---先判断再执行
    do{}while() ---先执行再判断
    for(起始表达式;条件表达式;末尾循环体){}
或 || ; 与 &&
跳转语句：
    break; ---退出循环
    continue; ---跳过当前循环，执行下一次
    goto FLAG; ---跳转到标记位置

数组：
    一维数组：
        数据类型 数组名[数组长度]； || 数据类型 数组名[] = {值1, 值2, ...}
    二维数组：
        数据类型 数组名[行数][列数]； || 数据类型 数组名[行数][列数] = {{值1, 值2}, {值3, 值4}};
         
*/

int main()
{
    
    short a = 9;
    short c = 97;
    // int c = 2;
    std::cout << "Hello world!~\n" ;
    // std::cout << "a=\n";
    printf("a = %d \n", a);
    cout << "常量" << d << endl;
    cout << "short内存空间 = " << sizeof(short) << endl;
    // cout << "请输入整数" << endl;
    // cin >> c;
    cout << c << endl;
    int arr[5]={1, 2, 3 , 4, 5};
    cout << (long)arr << endl;
    cout << (long)&arr[0] << endl;

    // pause();


    return 0;
}

