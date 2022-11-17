#include<bits/stdc++.h>
using namespace std;

const int max_size = 100;

char grid[max_size][max_size];
bool visited[max_size][max_size];              //Records the visited nodes
int Distance[max_size][max_size];              //Stores the distance of the node from the start node
pair<int,int> pre[max_size][max_size];

//The arrays A and B are used to navigate top, down, left and right in the grid
int A[4] = {1,-1,0,0};
int B[4] = {0,0,1,-1};

char D[4] = {'D','U','R','L'};


//The breadth first search algorithm begins search from start node (top left corner)

void bfs(){
	
	queue<pair<int,int>> q;
	
	q.push({1,1});                //The coordinates of the start node
	visited[1][1] = true;         //The start node is visited
	Distance[1][1] = 0;           //Distance to the start node from itself is 0
	
	while(!q.empty()){            
		
		pair<int,int> s = q.front();    //load the front node into s
		
		q.pop();                         //delete the front node
		
		for(int i = 0; i < 4; ++i){      //Each cell maybe connected to any of the four neighbouring cells
			
			//Coordinates of the neighbouring cell
			int y = s.first + A[i];   
			int x = s.second + B[i];	
			
			if(grid[y][x] == '.'){
				
				if(visited[y][x]) continue;
				
				visited[y][x] = true;
				
				//distance to node (y,x) is distance to the parent node plus 1
				Distance[y][x] = Distance[s.first][s.second] + 1;
				
				//the parent of (y,x) is s
				pre[y][x] = s;
				
				q.push({y,x});
			}
		}
	}
}
		
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin>>n>>m;
	
	//Set all the cell inside the gird to #
	memset(grid, '#', sizeof(grid));
	
	//reading the labyrinth from the console and creating a hedge around the labyrinth
	//i.e, starting from (1,1) not from (0,0) to avoid out of bound error inside bfs()
	
	for(int i = 1; i <= n; ++i){
		
		for(int j = 1; j <= m; ++j){
			
			cin>>grid[i][j];
		}
	}
	
	bfs();  //Start the bredth first search from the start node
	
	//if the (n,m) is not visisted then there is not path from start to end
	if(!visited[n][m]){
		
		cout<<"There is no such path\n";
		exit(0);
	}
	
	cout<<Distance[n][m]<<"\n";   //Distance of the shortest path
	
	vector<pair<int,int>> path;
	
    pair<int,int> p = {n,m};   //starting bactracking 
	
	//code to track the path 
    while(p != make_pair(1,1)){
		
	    path.push_back(p);
		
		p = pre[p.first][p.second];
    }
    
	path.push_back(p);
	
    reverse(path.begin(), path.end());   //invert the path
	
    int l = path.size();
	
	//code to print the path
    for(int i = 1; i < l; ++i){
	        
	    int y = path[i-1].first;
	    int x = path[i-1].second;
	        
	    int a = path[i].first;
	    int b = path[i].second;
	        
	    if(a - y == 1) cout<<'D';
	    if(a - y == -1) cout<<'U';
	    if(b - x == 1) cout<<'R';
	    if(b - x == -1) cout<<'L';
   	}
   	
   	return 0;
}

