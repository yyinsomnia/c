/**
 *char *m = "hello";
 * "hello"保存在静态数据区，该数据不能修改.
 * 由指针m指向. 不能通过指针m来修改静态数据区的值.

 * char w[] = "hello";
 * hello"保存在栈空间数组里. 数组名为w, 函数名为数组的首地址.
 * 可以通过w[i]='a', 或*(w+i)='a'的形式来修改数组内容.
 */
#include <stdio.h>

void foo(char *s)
{
	*s = 'w';
    printf("%s\n", s);
}

int main()
{
    void foo(char *);
    char s[]  = "houyunyang";
    printf("%s\n", s); 
    return 0;  
}