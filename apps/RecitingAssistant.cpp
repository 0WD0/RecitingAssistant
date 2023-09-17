#include<iostream>
#include<cstdio>
#include<bitset>
#include<windows.h>
#include<vector>
#include<map>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
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
map<string,int>en,pun,cir;
map<string,vector<int>>kanji;
const int ne=7,np=9;
string ed[ne]={"”","。","？","！","）","；","："};
string punctuation[np]={"《","》","（","“","，","、","‘","’","·"};
string ord[55]={"⓪","①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩","⑪","⑫","⑬","⑭","⑮","⑯","⑰","⑱","⑲","⑳","㉑","㉒","㉓","㉔","㉕","㉖","㉗","㉘","㉙","㉚","㉛","㉜","㉝","㉞","㉟","㊱","㊲","㊳","㊴","㊵","㊶","㊷","㊸","㊹","㊺","㊻","㊼","㊽","㊾","㊿"};
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
string z;
void tran(){
	int i,j; s.clear();
	for(i=0,j=0;cc[i];j++){
		if((string)""+cc[i]+cc[i+1]=="·")s.emplace_back("·"),i+=2;
		else{
			z=(string)""+cc[i]+cc[i+1]+cc[i+2];
			// if(!cir.count(z))
			s.emplace_back(z),i+=3;
		}
	}
	len=j;
}
void print(vector<string>&v){
	for(auto x:v)cout<<x;
	cout<<endl;
}
void init(){
	for(int i=0;i<ne;i++)en[ed[i]]=pun[ed[i]]=1;
	for(int i=0;i<np;i++)pun[punctuation[i]]=1;
	for(int i=0;i<=50;i++)cir[ord[i]]=1;
}
void processing_text(){
	freopen("../IO/text.txt","r",stdin);
	init();
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
bitset<30>down;
bitset<30>pre;
void check(char c){
	if(!KEY_DOWN(c))down[c-'A']=0;
	else down[c-'A']=1;
}
char keys[4]={'H','J','K','L'};
int po,ind;
void show(){
	for(auto x:nd[g[po][ind]].s)cout<<x;
}
void display(){
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
    system("cls");
	show();
}
void keyboard_monitor(){
	po=0;ind=0;
    system("cls");
	printf("ROOT");
	while(1){
	    pre=down;
		for(auto c:keys)check(c);
	    if(down.to_ulong()>pre.to_ulong())display();
		Sleep(20);
    }
}

int main(){
	processing_text();
	keyboard_monitor();
}