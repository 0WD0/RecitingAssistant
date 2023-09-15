#include<bits/stdc++.h>
using namespace std;
const int N=100005;
char s[N];
map<char,int>en,pun;
map<char,vector<int>>kanji;
char ed[8]={'”','。','？','！','）','；','：'};
struct wchar{
	char s[3];
}ws[N];
struct NODE{
	string s;
	int L,R,fa;
}nd[N];
vector<int,int>g[N];
int t;//cur
int lv[5];
#define p lv[1]
#define d lv[2]
#define ju lv[3]
#define xj lv[4]
void mlv(int i){
	++t;
	g[lv[i-1]].push_back(t);
	nd[t].L=lv[i],nd[lv[i]].R=t;nd[t].fa=lv[i];
	lv[i]=t;
}
void test(){
	for(int x:g[0]){
		cout<<nd[x].s<<endl;
	}
}
void get(){
}
int main(){
	for(int i=0;i<8;i++)en[ed[i]]=1;
	pun=en; pun['“']=pun['（']=pun['，']=1;
	int n=1;
	while(n--){
		while(gets(s),s[0]=='\0');
		mlv(1); nd[t].s=s;
		while(gets(s),s[0]){
			int a=0,j=0;
			for(;s[j];j++,a++){
				while(s[j]&&(s[j]==' '||s[j]<='z'&&s[j]>='a'))j++;
				s[a]=s[j];
			}
			for(;a<=j;a++)s[a]=0;
			mlv(2); nd[p].s+=s; nd[d].s=s;
			for(int i=0;s[i];i++){
				if(i==0||!en.count(s[i])&&en.count(s[i-1]))mlv(3);
				if(i==0||s[i-1]=='，')mlv(4);
				nd[xj].s+=s[i];
				nd[ju].s+=s[i];
				if(pun.count(s[i]))kanji[s[i]].push_back(xj);
			}
		}
	}
}