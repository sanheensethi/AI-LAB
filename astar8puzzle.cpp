#include<bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define endl "\n"
#define is ==
#define set_bits __builtin_popcountll
#define all(x) (x).begin(), (x).end()
#define test ll T; cin>>T; while(T--) solve();
#define test1 ll T=1; while(T--) solve();
#define loop(i,s,n) for(ll i=s;i<n;i++)
#define rloop(i,s,n) for(ll i=s;i>=n;i--)
#define fill(a,value) memset(a,value,sizeof(a))
#define umap unordered_map
#define pb push_back
#define mp(a,b) make_pair(a,b)

// Take Vector
#define takeVector(n,T) vector<T> arr(n); for(int i=0;i<n;i++) cin>>arr[i];

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;

/*DEBUGGING TEMPLATE*/

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" : "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T, class V> void _print(unordered_map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(unordered_map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}


/*######################################################################################################################################*/
/*SOLUTION*/ 
class Cost{
public:
  int g; // depth
  int h; // no of tiles
  int f; // g+f
  vector<vector<vector<int>>> path;
  vector<vector<int>> puzz;
  bool reached = false;
  pair<int,int> blank;
  string direction;
  Cost(){

  }
  Cost(int g,vector<vector<int>>& puzz,vector<vector<int>>& goal,pair<int,int>& blank){
    this->g = g;
    this->h = calcHero(puzz,goal);
    this->f = this->g+this->h;
    this->puzz = puzz;
    this->blank.first = blank.first;
    this->blank.second = blank.second;
  }

private:
  int calcHero(vector<vector<int>>& puzz,vector<vector<int>>& goal){
    int cost = 0;
    int n = puzz.size();
    for(int i=0;i<n;i++){
      for(int j = 0;j < n;j++){
        if(puzz[i][j] != 0 && puzz[i][j] != goal[i][j]){
          cost++;
        }
      }
    }
    if(cost == 0){
      this->reached = true;
    }
    return cost;
  }

private:
  pair<int,int> coord(vector<vector<int>>& puzz,int num){
    for(int i = 0;i<puzz.size();i++){
      for(int j=0;j<puzz.size();j++){
        if(puzz[i][j] == num){
          return {i,j};
        }
      }
    }
    return {-1,-1};
  }
  int manhattan(vector<vector<int>>& puzz,vector<vector<int>>& goal){
    int cost = 0;
    int n = puzz.size();
    pair<int,int> t1t2;
    for(int i=0;i<n;i++){
      for(int j = 0;j<n;j++){
        t1t2 = coord(puzz,goal[i][j]);
        cost += abs(i - t1t2.first) + abs(j - t1t2.second);
      }
    }
    if(cost == 0){
      this->reached = true;
    }
    return cost;
    if(cost == 0){
      this->reached = true;
    }
    return cost;
  }

};

class Compare{
public:
  int operator()(const Cost& c1,const Cost& c2){
    return c1.f > c2.f;
  }
};

void runAstar(vector<vector<int>>& puzz,vector<vector<int>>& goal,pair<int,int>& blank){
  priority_queue<Cost, vector<Cost>, Compare> pq;
  Cost iniCost(0,puzz,goal,blank);
  iniCost.direction = "Initial";
  pq.push(iniCost);
  bool flag = false;
  map<vector<vector<int>>,bool> alreadyDone;
  Cost ans;
  alreadyDone[puzz] = true;

  
  while(!pq.empty()){
    Cost current = pq.top();pq.pop();
    
    vector<vector<int>> puzz = current.puzz;
    int n = puzz.size();
    pair<int,int> position = current.blank;
    int i = position.first;
    int j = position.second;
    int depth = current.g;
    // vector<int> vec{depth,current.h,current.f};
    

    if(current.reached == true){
      flag = true;
      current.path.emplace_back(current.puzz);
      ans = current;
      break;
    }
    // left
    if(j-1 >= 0){
      swap(puzz[i][j-1],puzz[i][j]);
      pair<int,int> bb;
      bb.first = i;
      bb.second = j-1;
      if(alreadyDone.find(puzz) == alreadyDone.end()){
        Cost leftMove(depth+1,puzz,goal,bb);
        if(current.path.size()>0){
          for(auto matrix:current.path){
            leftMove.path.emplace_back(matrix);
          }
        }
        leftMove.path.emplace_back(current.puzz);
        leftMove.direction = "Left";
        pq.push(leftMove);
        alreadyDone[puzz] = true;
      }
      swap(puzz[i][j-1],puzz[i][j]);
    }
    // right
    if(j+1 < n){
      swap(puzz[i][j+1],puzz[i][j]);
      pair<int,int> bb;
      bb.first = i;
      bb.second = j+1;
      if(alreadyDone.find(puzz) == alreadyDone.end()){
        Cost rightMove(depth+1,puzz,goal,bb);
        if(current.path.size()>0){
          for(auto matrix:current.path){
            rightMove.path.emplace_back(matrix);
          }
        }
        rightMove.path.emplace_back(current.puzz);
        rightMove.direction = "Right";
        pq.push(rightMove);
        alreadyDone[puzz] = true;
      }
      swap(puzz[i][j+1],puzz[i][j]);
    }
    // up
    if(i-1 >= 0){
      swap(puzz[i-1][j],puzz[i][j]);
      pair<int,int> bb;
      bb.first = i-1;
      bb.second = j;

      if(alreadyDone.find(puzz) == alreadyDone.end()){
        Cost upMove(depth+1,puzz,goal,bb);
        if(current.path.size()>0){
          for(auto matrix:current.path){
            upMove.path.emplace_back(matrix);
          }
        }
        upMove.path.emplace_back(current.puzz);
        upMove.direction = "Up";
        pq.push(upMove);
        alreadyDone[puzz] = true;
      }
      swap(puzz[i-1][j],puzz[i][j]);
    }
    // down
    if(i+1 < n){
      swap(puzz[i+1][j],puzz[i][j]);
      pair<int,int> bb;
      bb.first = i+1;
      bb.second = j;
      if(alreadyDone.find(puzz) == alreadyDone.end()){
        Cost downMove(depth+1,puzz,goal,bb);
        if(current.path.size()>0){
          for(auto matrix:current.path){
            downMove.path.emplace_back(matrix);
          }
        }
        downMove.path.emplace_back(current.puzz);
        downMove.direction = "Down";
        pq.push(downMove);
        alreadyDone[puzz] = true;
      }
      swap(puzz[i+1][j],puzz[i][j]);
    }
  }
  if(flag == true){
    cout<<"Reached"<<endl;
  }else{
    int size = pq.size();
    cout<<"Not Reached"<<endl;
    debug(size);
  }
  cout<<endl;
  cout<<"Path Printing : "<<endl;
  int s = ans.path.size();
  debug(s)
  for(auto& matrix:ans.path){
    for(auto& vec:matrix){
      for(auto& val:vec){
        cout<<val<<" ";
      }
      cout<<endl;
    }
    cout<<endl<<endl;
  }
}

void solve(){
  vector<vector<int>> goal(3,vector<int>(3,0));
  vector<vector<int>> puzz(3,vector<int>(3,0));

  goal[0][0] = 2;
  goal[0][1] = 8;
  goal[0][2] = 1;
  goal[1][0] = 0;
  goal[1][1] = 4;
  goal[1][2] = 3;
  goal[2][0] = 7;
  goal[2][1] = 6;
  goal[2][2] = 5;

  // initial state:
  pair<int,int> blank;

  puzz = {{1,2,3},
          {8,0,4},
          {7,6,5}};

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      //cin>>puzz[i][j];
      if(puzz[i][j] == 0){
        blank.first = i;
        blank.second = j;
      }
    }
  }
  runAstar(puzz,goal,blank);
}

/*######################################################################################################################################*/


signed main() {
  #ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
  #endif
  fastio();
  test1
  // test
  return 0;
}