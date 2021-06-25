#include <iostream>
#include <list>
using namespace std;
#define MAX 20
struct Node {
  int x;
  Node *pNext;
};
struct List {
  Node *pHead, *pTail;
};
struct Queue{
  List data;
};
void createList(List &l) {
  l.pHead = NULL;
  l.pTail = NULL;
}
Node* createNode(int x) {
  Node *p = new Node;
  if (p != NULL) {
    p->x = x;
    p->pNext = NULL;
  }
  return p;
}
void addTail(List &l, Node *p) {
  if (l.pHead == NULL) {
    l.pHead = p; l.pTail = p;
  }
  else {
    l.pTail->pNext = p; l.pTail = p;
  }
}
int removeHead(List &l) {
  Node *p = l.pHead;
  int r = 0;
  if (l.pHead != NULL) {
    l.pHead = p->pNext;
    delete p;
    r = 1;
    if (l.pHead == NULL)
      l.pTail = NULL;
    }
  return r;
}
void createQueue(Queue &q){
  createList(q.data);
}
int isEmpty(Queue q){
  return (q.data.pHead==NULL);
}
void enQueue(Queue &q,int x){
  Node *p = createNode(x);
  addTail(q.data,p);
}
void deQueue(Queue &q){
  removeHead(q.data);
}
int frontQueue(Queue &q, int &x) {
  if (isEmpty(q))
    return 0;
  x = q.data.pHead->x;
  return 1;
}
void visit(int g[MAX][MAX], int n, int x, int label, int v[MAX]){
  v[x]=label;
  //cout<<x<<": "<<label<<endl;
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
void DFS(int grid[MAX][MAX], bool visited[], int n, int start){
  visited[start]=true;
  cout<<start<<"\t";
  for(int i = 0; i<n;i++){
    if(!visited[i]&&grid[start][i]){
      DFS(grid,visited,n,i);
    }
  }
}
void BFS(int grid[MAX][MAX],bool visited[], int n, int start)
{
     // Create a queue for BFS
    Queue queue;
    createQueue(queue);
    // Mark the current node as visited and enqueue it
    visited[start] = true;
    enQueue(queue,start);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    while(!isEmpty(queue))
    {
        // Dequeue a vertex from queue and print it
        frontQueue(queue,start);
        cout << start << " ";
        deQueue(queue);
        for (int i = 0; i <n; i++)
        {
            if (grid[start][i]==1&&!visited[i])
            {
                visited[i] = true;
                enQueue(queue,i);
            }
        }
    }
}
/*void printCircle (int grid[MAX][MAX], int node, int n){
  bool *visited = new bool [n];
  int circle[MAX];
  int circleIndex1=0,circleIndex2=0;
  for(int i=0;i<n;i++){
    visited[i]=false;
  }
  for (int i = 0; i < MAX; i++) {
    circle[i]=-1;
  }
  int temp,pre=-1,next;
  circle[circleIndex1]=node;
  visited[node]=true;
  bool check;
  while(circleIndex1!=-1){
    temp=circle[circleIndex1];
    if(circleIndex1>0)
      pre=circle[circleIndex1-1];
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
    if(check){
      if(circle[circleIndex1+1]!=-1){
        next = circle[circleIndex1+1];
        grid[temp][next]=1;
        grid[next][temp]=1;
        visited[next]=false;
        circle[circleIndex1+1]=-1;
      }
      circleIndex1--;
    }
  }
  cout<<endl;
}*/
int main(){
  int graph[MAX][MAX];
  int n=8;
  int visit[MAX]={0};
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
  int component = tpLienThong(graph,n,visit);
  cout<<"So thanh phan lien thong la: "<<component<<endl;
  bool checkCircle =  Circle(graph,component,visit,n);
  /*if(checkCircle){
    cout<<"Do thi co chu trinh"<<endl;
  }
  else
    cout<<"Do thi khong co chu trinh"<<endl;*/
  bool *visited = new bool [n];
  for(int i=0;i<n;i++){
    visited[i]=false;
  }
  BFS(graph,visited,n,1);
  return 0;
}
