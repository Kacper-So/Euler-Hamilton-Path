#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

void display_fill(bool **adjacency_matrix,int n){
    float full = (n*n)-n;
    float counter = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjacency_matrix[i][j] == true) counter++;
        }
    }
    cout<<"Wypelnienie grafu : "<<(counter/full)*100<<"%"<<endl;
}

float fill_check(bool **adjacency_matrix,int n){
    float full = (n*n)-n;
    float counter = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjacency_matrix[i][j] == true) counter++;
        }
    }
    return (counter/full)*100;
}

void insertEdge(bool **adjacency_matrix,int x, int y)
{
    adjacency_matrix[x][y] = true;
    adjacency_matrix[y][x] = true;
}

void create_graph(bool **adjacency_matrix,int n, float fill)
{
  int maxEdges = n * (n - 1) / 2;
  int requiredEdges = maxEdges * (fill/100);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adjacency_matrix[i][j] = false;

  // Prosty sposób na spójny graf: cykl Eulera ze wszystkich wierzchołków
  requiredEdges -= n;
  for (int i = 0; i < n; i++)
  insertEdge(adjacency_matrix,i, (i + 1) % n);

  for (int i = 0; i < requiredEdges / 4; i++)
  {
    int x1, x2, y1, y2;

    while(true)
    {
      x1 = rand() % n;
      y1 = rand() % n;
      x2 = rand() % n;
      y2 = rand() % n;

      if (x1 == y1 || x2 == y2)
        continue;
      if (x1 == y2 || x2 == y1)
        continue;
      if (x1 == x2 || y1 == y2)
        continue;
      if (adjacency_matrix[x1][y1] || adjacency_matrix[x1][y2] || adjacency_matrix[x2][y1] || adjacency_matrix[x2][y2])
        continue;

      break;
    }

    insertEdge(adjacency_matrix,x1, y1);
    insertEdge(adjacency_matrix,x1, y2);
    insertEdge(adjacency_matrix,x2, y1);
    insertEdge(adjacency_matrix,x2, y2);
  }
}

void display_graph(bool **adjacency_matrix, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjacency_matrix[i][j] == true) cout<<"1 ";
            else cout<<"0 ";
        }
        cout<<endl;
    }
}

void Euler(int v, bool **adjacency_matrix,int n,vector<int> &cycle){
    for(int i=0;i<n;i++){
        while(adjacency_matrix[v][i]){
            adjacency_matrix[v][i] = false;
            adjacency_matrix[i][v] = false;
            Euler(i,adjacency_matrix,n,cycle);
        }
    }
    cycle.push_back(v);
}

int counter2=0;
bool *visited;
void Hamilton_all(int v,int root,vector<int> &cycle, int n, bool **adjacency_matrix)
{
  bool test;
  cycle.push_back(v);
  if( cycle.size() < n ){
    visited[v] = true;
    for(int i=0;i<n;i++){
        if(adjacency_matrix[v][i] && !visited[i]){
            Hamilton_all(i,root,cycle,n,adjacency_matrix);
        }
    }
    visited[v] = false;
  }
  else{
    test = false;
    for(int i=0;i<n;i++){
        if(adjacency_matrix[v][i] && i == root){
            test = true;
            break;
        }
    }
    if(test){
        counter2++;
        //for(int i=0;i<cycle.size();i++){
        //    cout<<cycle[i]<<" ";
        //}
        //cout<<endl;
    }
  }
  cycle.pop_back();
}

vector<int> cycle2;
bool *visited2;
bool test2 = false;
void Hamilton(int v,int root,int n, bool **adjacency_matrix){
    cycle2.push_back(v);
    visited[v] = true;
    for(int i=0;i<n;i++){
        if(adjacency_matrix[v][i] && !visited[i]){
            Hamilton(i,root,n,adjacency_matrix);
        }
    }
    if(cycle2.size() == n){
        for(int i=0;i<n;i++){
            if(adjacency_matrix[v][i] && i == root){
                test2 = true;
                cycle2.push_back(root);
                break;
            }
        }
    }else if(cycle2.size() != n && test2 == false){
        cycle2.pop_back();
    }
}

int main(){
    srand(time(NULL));
    int n=10;
    visited = new bool[n];
    visited2 = new bool[n];
    //int tab[16];
    //int e=0;
    //while(n!=16){
    counter2=0;
    srand(time(NULL));
    bool **adjacency_matrix = new bool * [n];
    for(int i=0;i<n;i++){
        adjacency_matrix[i] = new bool [n];
    }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adjacency_matrix[i][j] = false;
            }
        }
        create_graph(adjacency_matrix,n,50);

        /*//wczytywanie z txt
        vector<string> v;
        fstream file;
        file.open("euler.txt");
        string line;
        while(!file.eof()){
        getline(file,line);
        v.push_back(line);
        }
        file.close();
        int n = v.size();
        bool **adjacency_matrix = new bool * [n];
        for(int i=0;i<n;i++){
            adjacency_matrix[i] = new bool [n];
        }
        for(int i = 0; i < n; i++){
            for(int j = 0;j < n; j++){
                if(v[i][2*j] == '0') adjacency_matrix[i][j] = false;
                else if(v[i][2*j] == '1') adjacency_matrix[i][j] = true;
            }
        }*/

        display_graph(adjacency_matrix,n);
        display_fill(adjacency_matrix,n);
        //cout<<endl;
        vector<int> cycle_euler;
        vector<int> cycle_hamilton;

        //Cykl Eulera
        //t=clock();
        /*Euler(0,adjacency_matrix,n,cycle_euler);
        //tv[e]=clock()-t;
        cout<<"Cykl Eulera : "<<endl;
        for(int i=0;i<cycle_euler.size();i++){
            cout<<cycle_euler[i]+1<<" ";
        }*/

        cout<<endl;  

        //Cykl Hamiltona
        //t=clock();
        Hamilton(0,0,n,adjacency_matrix);
        //tv[e]=clock()-t;
        cout<<"Cykl hamiltona : "<<endl;
        for(int j=0;j<n+1;j++){
            cout<<cycle2[j]+1<<" ";
        }
        //cout<<endl;
        //Hamilton_all(0,0,cycle_hamilton,n,adjacency_matrix);
        //tab[e]=counter2;
        //cout<<"ilosc cykli Hamiltona : "<<counter2<<endl;
        //n++;
       // e++;
    //}
    //cout<<e;
    //ofstream f("hamilton_counter.txt");
    //for(int j = 0;j < e; j++){
        //f<<tab[j]<<endl;
    //}
    //f.close();
}
