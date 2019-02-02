#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second

#define endl '\n'

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;


// print set or vector into any stream
//////////////////////////////////////////////
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::set<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}
///////////////////////////////////////////////

struct Video{
	int size; // in megabytes
	int id;
};

struct Endpoint{
	int id;
	// Improvements over data center. Vector of size C, has 
	vector<int>Imp; 
};

// struct Server
// {
// 	int cap; // capacity in megaytes
// };

struct Request
{
	int weight; // number of times the 
	int eid, vid; // endpoint, video ids
};

int main(){
	int V, E, R, C, X;
	cin>>V>>E>>R>>C>>X;
	vector<Video>Vid(V);
	for(int i=0; i<V; i++){
		cin>>Vid[i].size;
		Vid[i].id = i;
	}
	vector<Endpoint>Users(V);
	for(int i=0; i<E; i++){
		int dclat; // data center latency
		int k; // number of connected cache servers
		cin>>dclat>>k;
		Users[i].Imp.resize(C);
		for(int j=0; j<k; j++){
			int c, l;
			cin>>c>>l;
			Users[i].Imp[j] = dclat-l;
		}
	}
	vector<Request>Req(R);
	for(int i=0; i<R; i++){
		cin>>Req[i].vid>>Req[i].eid>>Req[i].weight;
	}
}
