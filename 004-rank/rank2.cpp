
#include <bits/stdc++.h>
using namespace std;
using I=int;
using V=vector<I>;
I n,i,m;
bool comp(P a,P b){
return a.first.size() > b.first.size() ? true : a.first.size() == b.first.size() ? a.first > b.first : false;}
main(){
ifstream F=ifstream("rank.inp");
ofstream O=ofstream("rank.out");
struct P{
    V c;
    I x,z;
};
vector <P>d;
V v{-1};
for(F>>n;n&&F>>i;v.push_back(i))if(i<0){
sort(v.begin(),v.end());
d.push_back({v,++m});
v.clear();}
stable_sort(&d[0],&d[0]+n);
for(i=0;i<m-1;++i)O<<d[i].x<<'\n';
O<<d[m-1].x;
F.close();
O.close();}
