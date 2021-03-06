#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef pair<int, P > PP;

#define MAX_N 2005

vector<int> G[MAX_N];
int t[MAX_N][MAX_N];

int N,K,S;
int x[MAX_N],y[MAX_N],z[MAX_N];
/*
bool incheck(int id,int px,int py,int pz){
  if(x[id]<=px && px<x[id]+S)
    if(y[id]<=py && py<y[id]+S)
      if(z[id]<=pz && pz<z[id]+S)
        return true;
  return false;
}
*/
int calc(int a,int b){
  assert(a!=b);
  int ax=x[a],ay=y[a],az=z[a];
  int bx=x[b],by=y[b],bz=z[b];

  int XY = max(0, min(ax+S,bx+S)-max(ax,bx) )* max(0, min(ay+S,by+S)-max(ay,by) );
  XY=S*S*2-XY;

  int YZ = max(0, min(ay+S,by+S)-max(ay,by) )* max(0, min(az+S,bz+S)-max(az,bz) );
  YZ=S*S*2-YZ;

  int ZX = max(0, min(az+S,bz+S)-max(az,bz) )* max(0, min(ax+S,bx+S)-max(ax,bx) );
  ZX=S*S*2-ZX;

  return S*S*12-XY*2-YZ*2-ZX*2;
}

bool isIntersect(int a,int b){
  if(x[b]+S<=x[a] || x[a]+S<=x[b])return false;
  if(y[b]+S<=y[a] || y[a]+S<=y[b])return false;
  if(z[b]+S<=z[a] || z[a]+S<=z[b])return false;
  return true;
}


void init(){
  for(int i=0;i<MAX_N;i++){
    G[i].clear();
  }
  memset(t,0,sizeof(t));
}

int Ans,flg;

void dfs(int pos,int prev,int sum,int depth,int root){

  if(depth==K){
    flg=1;
    for(int i=0;i<(int)G[pos].size();i++){
      if(root==G[pos][i]){
        sum+=( t[pos][root] );
      }
    }
    Ans=max(Ans,sum);
    return;
  }

  for(int i=0;i<(int)G[pos].size();i++){
    int to=G[pos][i];
    if(to==prev)continue;
    if(to==root)continue;
    dfs(to,pos,sum+t[pos][to],depth+1,root);
  }
}



int solve(){
  if(K==1)return S*S*6;
  if(K==2){
    int maxm=0;
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        maxm=max(maxm,t[i][j]);
      }
    }
    if(maxm==0){
      return -1;
    }
    return S*S*12-maxm;
  }
  Ans=flg=0;
  for(int i=0;i<N;i++){
    dfs(i,-1,0,1,i);
  }
  if(Ans==0)return -1;
  return S*S*6*K-Ans;
}

int main(){
  while(1){
    cin>>N>>K>>S;
    if(N==0&&K==0&&S==0)break;

    init();
    for(int i=0;i<N;i++){
      cin>>x[i]>>y[i]>>z[i];
      for(int j=0;j<i;j++){
        assert( x[i]!=x[j] || y[i]!=y[j] || z[i]!=z[j] );
      }
    }


    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        if(i==j)continue;

        if(isIntersect(i,j)){
          t[i][j]=calc(i,j);
          G[i].push_back(j);
        }
      }
    }
    int output=solve();
    cout<< output <<endl;
  }
  return 0;
}

