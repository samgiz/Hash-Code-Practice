#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second

#define endl '\n'

typedef long long ll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;


// prll set or vector llo any stream
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

struct Endpoll{
	// Improvements over data center for each . Vector of size C, has 
	vector<ll>Imp;
};

struct Request
{
	ll weight; // number of times the 
	ll eid; // endpoll, video ids
  	Request(ll weight, ll eid){
      	this->weight = weight;
      	this->eid = eid;
    }
};

vector<ll>VidSz; // Video size of each video

struct SerVid{
	ll score, vid, sid;
	
  	SerVid(ll score, ll vid, ll sid){
      	this->score = score;
      	this->vid = vid;
      	this->sid = sid;
    }
  	
  	bool operator<(const SerVid& s) const{
      	return (long double)score/VidSz[vid]<s.score/VidSz[s.vid];
    }
};
struct Server{
	ll score, id;
	
  	Server(ll score, ll id){
      	this->score = score;
      	this->id = id;
    }
  	
  	bool operator<(const Server& s) const{
      	return score<s.score;
    }
};

struct Video{
	ll score, id;
  	
  	Video(ll score, ll id){
      	this->score = score;
      	this->id = id;
    }
  
  	bool operator<(const Video& s) const{
      	return score<s.score;
    }
};



vector<vector<ll> > answer; // for each server, the videos to put int it
ll overall_score; // score of algorithm; prlled at end
priority_queue<SerVid>Ser[10000];
priority_queue<SerVid> Vid;
vector<ll> Cap; // capacity of ith video

vector<Request>Req[10001]; // Req[i] contains requests of ith video
vector<Endpoll>Users;
vector<vector<ll> > low_cost; // for each endpoll for each video the lowest cost 
ll V, E, R, C, X;
ll improvement(ll eid, ll sid, ll vid){
    return max(Users[eid].Imp[sid]-low_cost[eid][vid], (ll)0);
}
ll calculate_score(ll vid, ll sid){
  	ll ans = 0;
	for(auto req: Req[vid]){
      	ans += req.weight * improvement(req.eid, sid, vid);
    }
  	return ans;
}

void do_things(){
	SerVid best = Vid.top();
	Vid.pop();
	Ser[best.vid].pop();
  	if (Cap[best.sid] >= VidSz[best.vid]){
      	answer[best.sid].push_back(best.vid);
  		Cap[best.sid] -= VidSz[best.vid];
      	overall_score += best.score;

      	// updating everything
      	for (auto req : Req[best.vid])
          	low_cost[req.eid][best.vid] = max(low_cost[req.eid][best.vid], Users[req.eid].Imp[best.sid]);
      	
      	vector<SerVid> unused;
      	
      	while(Ser[best.vid].size()){
      		unused.pb(Ser[best.vid].top());
      		Ser[best.vid].pop();
      	}
      	for(auto s: unused){	
          	Ser[s.vid].push(SerVid(calculate_score(s.vid, s.sid), s.vid, s.sid));
        }
    }
  	if (Ser[best.vid].size())
      	Vid.push(Ser[best.vid].top());
}
  
int main(){
	cin>>V>>E>>R>>C>>X;
  	low_cost.resize(E, vector<ll>(V));
  	Cap.resize(C, X);
	VidSz.resize(V);
	for(ll i=0; i<V; i++){
		cin>>VidSz[i];
	}
	Users.resize(E);
	for(ll i=0; i<E; i++){
		ll dclat; // data center latency
		ll k; // number of connected cache servers
		cin>>dclat>>k;
		Users[i].Imp.resize(C);
		for(ll j=0; j<k; j++){
			ll c, l;
			cin>>c>>l;
			Users[i].Imp[c] = dclat-l;
		}
	}
	ll sum = 0;
	for(ll i=0; i<R; i++){
      	ll vid, eid, w;
      	cin>>vid>>eid>>w;
      	sum+=w;
      	Req[vid].pb(Request(w, eid));
	}
  	for(ll vid = 0; vid<V; vid++){
      	for(ll sid=0; sid<C; sid++){
          	Ser[vid].push(SerVid(calculate_score(vid, sid), vid, sid));
        }
      	Vid.push(Ser[vid].top());
    }
  	answer.resize(C);
  	while(Vid.size()){
  		do_things();
  	}
  	cout<<setprecision(20)<<(long double)overall_score*1000/sum << endl;


  	// for (int i = 0; i < C; i++){
   //    	cout << answer[i].size() << endl;
   //    	for (int j = 0; j < answer[i].size(); j++)
   //        	cout << answer[i][j] << ' ';
   //    	cout << endl;
   //  }
}
