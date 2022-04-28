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

class compare{
public:
  int operator()(const pair<int,int>& p1,const pair<int,int>& p2){
    return p1.second > p2.second;
  }
};

void solveTSP(vector<vector<pair<int,int>>>& graph){
  int nodes = graph.size();
  // min cost
  priority_queue<pair<int,int>,vector<pair<int,int>>,compare> pq; // node,weight
  int ansCost = INT_MAX;
  string ansPath = "";
  
  for(int src = 0;src < nodes;src++){
    vector<bool> visited(nodes,false);
    visited[src] = true;
    string path = "";
    pq.push({src,0});
    int cost = 0;
    int lastNode;

    while(!pq.empty()){
      auto current = pq.top();pq.pop();
      visited[current.first] = true;
      while(!pq.empty()){
        pq.pop();
      }
      int node = current.first;
      lastNode = node;
      path += to_string(node) + "->";
      int weight = current.second;
      cost += weight;
      for(auto& ngh:graph[node]){
        if(visited[ngh.first] == false){
          pq.push(ngh);
        }
      }
    }
    path += to_string(src);
    for(auto& pr:graph[lastNode]){
      if(pr.first == src){
        cost += pr.second;
        break;
      }
    }

    if(cost < ansCost){
      ansCost = cost;
      ansPath = path;
    }
    debug(mp(src,cost));
    debug(path);
  }
  cout<<endl;
  cout<<"Path : "<<ansPath<<endl;
  cout<<"Cost : "<<ansCost<<endl;

}

void solve(){
  int n;cin>>n;
  // tsp
  vector<vector<pair<int,int>>> graph(n);
  
  while(true){
    int src,dest,cost;
    cin>>src>>dest>>cost;
    if(src == -1 || dest == -1 || cost == -1){
      break;
    }
    graph[src].push_back({dest,cost});
    graph[dest].push_back({src,cost});
  }

  int i = 0;
  for(auto& vec:graph){
    cout<<i<<": ";
    for(auto& pr:vec){
      cout<<pr.first<<","<<pr.second<<" | ";
    }
    cout<<endl;
    i++;
  }

  solveTSP(graph);

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