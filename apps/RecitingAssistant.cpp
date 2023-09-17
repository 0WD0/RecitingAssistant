#include<iostream>
#include<cstdio>
#include<bitset>
#include<windows.h>
#include<vector>
#include<map>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的 
using namespace std;

//文本处理
const int N=100005;
char cc[N];
vector<string>s;
template <typename T>
vector<T> &operator +(vector<T> &v1,vector<T> &v2){
	v1.insert(v1.end(),v2.begin(),v2.end());	
	return v1;
}
int len;
map<string,int>en,pun;
map<string,vector<int>>kanji;
const int ne=7,np=9;
string ed[ne]={"”","。","？","！","）","；","："};
string punctuation[np]={"《","》","（","“","，","、","‘","’","·"};
struct NODE{
	vector<string>s;
	int L,R,fa,c,od;
}nd[N];
vector<int>g[N];
int t,lv[6];
#define p lv[1]
#define d lv[2]
#define ju lv[3]
#define xj lv[4]
#define dz lv[5]
void mlv(int i){
	++t;nd[t].od=g[lv[i-1]].size();
	g[lv[i-1]].push_back(t);
	nd[t].L=lv[i],nd[lv[i]].R=t;nd[t].fa=lv[i-1];
	lv[i]=t;nd[t].c=i;
}
void clean(){
	int a=0,j=0;
	for(;cc[j];j++,a++){
		while(cc[j]&&(cc[j]==' '||cc[j]<='z'&&cc[j]>='a'||cc[j]=='#'||cc[j]=='@'||cc[j]>='0'&&cc[j]<='9'))j++;
		cc[a]=cc[j];
	}
	for(;a<=j;a++)cc[a]=0;
}
void tran(){
	int i,j; s.clear();
	for(i=0,j=0;cc[i];j++){
		if((string)""+cc[i]+cc[i+1]=="·")s.emplace_back("·"),i+=2;
		else s.emplace_back((string)""+cc[i]+cc[i+1]+cc[i+2]),i+=3;
	}
	len=j;
}
void print(vector<string>&v){
	for(auto x:v)cout<<x;
	cout<<endl;
}
void processing_text(){
	freopen("../IO/text.txt","r",stdin);
	for(int i=0;i<ne;i++)en[ed[i]]=pun[ed[i]]=1;
	for(int i=0;i<np;i++)pun[punctuation[i]]=1;
	int n=60;
	while(n--){
		for(;gets(cc),!cc[0];cc[0]=0);
		clean();tran();
		mlv(1); nd[t].s=s;
		for(;gets(cc),cc[0];cc[0]=0){
			clean();tran();
			mlv(2); nd[p].s.emplace_back("\n");nd[p].s=nd[p].s+s; nd[d].s=s;
			for(int i=0;i<len;i++){
				if(i==0||!en.count(s[i])&&en.count(s[i-1]))mlv(3),mlv(4);
				else if(i==0||s[i-1]=="，")mlv(4);
				nd[xj].s.emplace_back(s[i]);
				nd[ju].s.emplace_back(s[i]);
				mlv(5);nd[dz].s.emplace_back(s[i]);
				if(pun.count(s[i]))kanji[s[i]].push_back(xj);
			}
		}
	}
}

//按键交互
bitset<30>down;//记录当前键盘按下状态
bitset<30>pre;//记录前一时刻键盘按下状态
void check(char c){//检测某个按键是否按下，按下就改变一下变量
	if(!KEY_DOWN(c))down[c-'A']=0;
	else down[c-'A']=1;
}
char keys[4]={'H','J','K','L'};
int po,ind;
void show(){
	for(auto x:nd[g[po][ind]].s)cout<<x;
}
void display(){
    system("cls");
	if(down[7]&&nd[po].c!=0){//H
		ind=nd[po].od;
		po=nd[po].fa;
	}
	if(down[11]&&nd[po].c!=4){//L
		po=g[po][ind];
		ind=0;
	}
	if(down[9]){//J
		if(ind<g[po].size()-1)ind++;
		else po=nd[nd[g[po][ind]].R].fa,ind=0;
	}
	if(down[10]){//K
		if(ind)ind--;
		else po=nd[nd[g[po][ind]].L].fa,ind=g[po].size()-1;
	}
	show();
}
void keyboard_monitor(){
	po=0;ind=0;
    system("cls");
	printf("ROOT");
	while(1){
	    pre=down;
		for(auto c:keys)check(c);
	    if(down!=pre)display();
		Sleep(20);
    }
}

int main(){
	processing_text();
	keyboard_monitor();
}