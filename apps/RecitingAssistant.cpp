#include<bits/stdc++.h>
using namespace std;
const int N=10004;
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
	int L,R,fa;
}nd[N];
vector<int>g[N];
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
void clean(){
	int a=0,j=0;
	for(;cc[j];j++,a++){
		while(cc[j]&&(cc[j]==' '||cc[j]<='z'&&cc[j]>='a'||cc[j]=='#'||cc[j]=='@'||cc[j]>='0'&&cc[j]<='9'))j++;
		cc[a]=cc[j];
	}
	for(;a<=j;a++)cc[a]=0;
}
void tran(){
	len=strlen(cc)/3;s.clear();
	for(int i=0;i<len;i++)s.emplace_back((string)""+cc[i*3]+cc[i*3+1]+cc[i*3+2]);
}
void print(vector<string>&v){
	for(auto x:v)cout<<x;
	cout<<endl;
}
void test(){
	for(int x:g[5]) print(nd[x].s);
}
int main(){
	for(int i=0;i<ne;i++)en[ed[i]]=pun[ed[i]]=1;
	for(int i=0;i<np;i++)pun[punctuation[i]]=1;
	int n=1;
	while(n--){
		for(;gets(cc),!cc[0];cc[0]=0);
		clean();tran();
		mlv(1); nd[t].s=s;
		// print(s);	
		for(;gets(cc),cc[0];cc[0]=0){
			clean();tran();
			mlv(2); nd[p].s=nd[p].s+s; nd[d].s=s;
			// print(s);	
			for(int i=0;i<len;i++){
				if(i==0||!en.count(s[i])&&en.count(s[i-1]))mlv(3),mlv(4);
				else if(i==0||s[i-1]=="，")mlv(4);
				nd[xj].s.emplace_back(s[i]);
				nd[ju].s.emplace_back(s[i]);
				if(pun.count(s[i]))kanji[s[i]].push_back(xj);
			}
		}
	}
	test();
}