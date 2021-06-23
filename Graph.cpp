#include <iostream>
#include <stack>
using namespace std;
#define MAX 20
void visit(int g[MAX][MAX], int n, int x, int label, int v[MAX]){
  v[x]=label;
  cout<<x<<": "<<label<<endl;
  for(int i=0;i<n;i++){
    if(v[i]==0&&(g[x][i]==1||g[i][x]==1))
      visit(g,n,i,label,v);
  }
}
int tpLienThong(int g[MAX][MAX], int n, int visited[MAX]){
  int label=0;
  for(int i=0;i<n;i++){
    if(visited[i]==0){
      label++;
      visit(g,n,i,label,visited);
    }
  }
  return label;
}
bool Circle(int grid[MAX][MAX], int component, int visit[], int n){
  int node = 0, edges=0;
  for(int i=1;i<=component;i++){
    node = 0;
    edges = 0;
    for(int k=0;k<n;k++){
      if(visit[k]==i){
        node++;
        for(int j=0;j<=k;j++){
          if(grid[k][j]==1) edges++;
        }
      }
    }
    if(edges>=node) return true;
  }
  return false;
}
void printCircle (int grid[MAX][MAX], int node, int n){
  bool *visited = new bool [n];
  int circle[MAX];
  int circleIndex1=0,circleIndex2=0;
  for(int i=0;i<n;i++){
    visited[i]=false;
  }
  int temp,pre=-1,next;
  circle[circleIndex1]=node;
  visited[node]=true;
  bool check =  true;
  while(circleIndex1!=-1){
    temp=circle[circleIndex1];
    check = true;
    for(int j=0;j<n;j++){
      if(grid[temp][j]==1){
        if(j!=pre){
          circleIndex1++;
          circle[circleIndex1]=j;
          grid[temp][j]=2;
          grid[j][temp]=2;
          if(visited[j]){
            circleIndex2=circleIndex1-1;
            cout<<j<<"->";
            for(int x = circleIndex2;circle[x]!=j;x--){
              cout<<circle[x]<<"->";
            }
            cout<<j<<endl;
            circleIndex1--;
          }
          visited[j]=true;
          check = false;
          break;
        }
      }
    }
    pre=temp;
    if(check){

      circleIndex1--;
    }
  }
  cout<<endl;
}
int main(){
  int graph[MAX][MAX];
  int n=8;
  int visited[MAX]={0};
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      graph[i][j]=0;
  }
  graph[0][4]=1;
  graph[0][6]=1;
  graph[1][7]=1;
  graph[2][5]=1;
  graph[2][7]=1;
  graph[3][4]=1;
  graph[3][6]=1;
  graph[4][7]=0;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(graph[i][j]==1)
        graph[j][i]=1;
    }
  }
  for(int i=0;i<n;i++){
    graph[i][i]=0;
    for(int j=0;j<n;j++){
      cout<<graph[i][j]<<" ";
    }
    cout<<endl;
  }
  int component = tpLienThong(graph,n,visited);
  cout<<"So thanh phan lien thong la: "<<component<<endl;
  bool checkCircle =  Circle(graph,component,visited,n);
  if(checkCircle){
    cout<<"Do thi co chu trinh"<<endl;
    printCircle(graph,0,n);
  }
  else
    cout<<"Do thi khong co chu trinh"<<endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout<<graph[i][j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}
