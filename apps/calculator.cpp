#include<bits/stdc++.h>
using namespace std;
const int N=1000;
map<char,int>iden;
double x[N];
int n,nx[N];
string s;
void init(){
	iden['+']=iden['-']=3;
	iden['*']=iden['/']=2;
	for(int i=0;i<=9;i++)iden['0'+i]=1;
	iden['(']=iden[')']=0;
}
void dfs(int l=0){
	int r=0;
	for(r=l+1;s[r]!=')';r=nx[r])if(s[r]=='(')dfs(r);
	for(int id=1,st,i;id<=3;id++) for(i=l+1;i<r;){
		while(iden[s[i]]>id)i=nx[i];
		for(st=i;i<r&&iden[s[i]]<=id;i=nx[i]){
			if(id==1&&iden[s[i]]!=0)x[st]=x[st]*10+s[i]-'0';
			else if(id==2){
				if(s[i]=='*')x[st]*=x[nx[i]];
				if(s[i]=='/')x[st]/=x[nx[i]];
			}else if(id==3){
				if(s[i]=='+')x[st]+=x[nx[i]];
				if(s[i]=='-')x[st]-=x[nx[i]];
			}
		}
		nx[st]=i;
	}
	nx[l]=r+1;
	x[l]=x[l+1];
}
int main(){
	init();
	cin>>s;
	s="("+s+")";
	n=s.length();
	for(int i=0;i<n;i++)nx[i]=i+1;
	dfs();	
	printf("%lf",x[0]);
}