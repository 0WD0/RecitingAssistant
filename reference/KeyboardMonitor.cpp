#include<iostream>
#include<bitset>
#include<windows.h>
 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的 
 
using namespace std;
 
void color(int a){//改变输出的颜色，比system("color x")快得多
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
 
bitset<30>down;//记录当前键盘按下状态
bitset<30>pre;//记录前一时刻键盘按下状态
 
void check(char c){//检测某个按键是否按下，按下就改变一下变量
	if(!KEY_DOWN(c))down[c-'A']=0;
	else down[c-'A']=1;
}
 
void print_letter(char c){
    if(!down[c-'A'])color(7);
	else color(112);
	printf("  %c  ",c);
	color(7);
}
 
void print(){
    system("cls");//清屏
	print_letter('Q');print_letter('W');print_letter('E');print_letter('R');print_letter('T');print_letter('Y');print_letter('U');print_letter('I');print_letter('O');print_letter('P');
    printf("\n\n ");
    print_letter('A');print_letter('S');print_letter('D');print_letter('F');print_letter('G');print_letter('H');print_letter('J');print_letter('K');print_letter('L');
    printf("\n\n  ");
    print_letter('Z');print_letter('X');print_letter('C');print_letter('V');print_letter('B');print_letter('N');print_letter('M');
}
 
int main(){
    print();
    while(1){
        pre=down;
        for(int i=0; i<26; i++){
            check(char('A'+i));
        }
        if(down!=pre)print();//检测到按键状态变化再打印
        
        Sleep(20);//循环时间间隔，防止太占内存 
    }
 
    return 0;
}
