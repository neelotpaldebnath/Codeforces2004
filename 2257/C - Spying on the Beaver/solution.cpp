/* Goal to be an expert*/
#include<bits/stdc++.h>
#include<tuple> 
using namespace std;
#define ll long long
#define INF INT_MAX
#define dd double
#define endl "
"
#define pb push_back
#define all(v) v.begin(),v.end()
#define mp make_pair
#define fi first
#define se second
#define vll vector<ll>
#define pll pair<ll,ll>
#define fo(i,n) for(int i=0;i<n;i++)
#define fo1(i,n) for(int i=1;i<=n;i++)
#define min3(a,b,c) min(a,min(b,c))
#define s(v) (ll)v.size()
#define e(v) v.empty()
#define bscount(x) __builtin_popcountll(x)
#define ppc               __builtin_popcount
#define ppcll             __builtin_popcountll
ll mod = 1000000007;
// ll n,k,t,m,q,flag=0;
ll power(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// ordered_set s ; s.order_of_key(a) -- no. of elements strictly less than a
// s.find_by_order(i) -- itertor to ith element (0 indexed)
ll min(ll a, ll b) {if (a > b)return b; else return a;}
ll max(ll a, ll b) {if (a > b)return a; else return b;}
ll gcd(ll a, ll b) {if (b == 0)return a; return gcd(b, a % b);}
vll div(ll n) { // all divisors of the number
  vll v;
  for (ll i = 1; i * i <= n; i++) {
    if ((n % i) == 0) {
      if (i == n / i) v.pb(i);
      else {
        v.pb(i);
        v.pb(n / i);
      }
    }
  }
  return v;
}
 
ll  isPrime(ll n)
{
  // Corner cases
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
 
  if (n % 2 == 0 || n % 3 == 0)
    return false;
 
  for (int i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
 
  return true;
}
bool isPowerOfTwo(ll n)
{
  if (n == 0)
    return false;
 
  return (ceil(log2(n)) == floor(log2(n)));
}
ll power1(ll x, ll y)
{
  ll temp;
  if ( y == 0)
    return 1LL;
  temp = power(x, y / 2);
  if (y % 2 == 0)
    return temp * temp;
  else
    return x * temp * temp;
}
 
bool cmp(pll a, pll b)
{
  if (a.first > b.first) return true;
  else if (a.first < b.first) return false;
  else
  {
    if (a.second < b.second)return true;
    else return false;
  }
}
 
vll pdiv(ll n) { // all prime divisors of the number
  vll v;
  for (ll i = 1; i * i <= n; i++) 
  {
    if ((n % i) == 0)
    {
      if (i == n / i) 
        {
          if(isPrime(n/i)) v.pb(i);
        }
      else 
      {
 
          if(isPrime(i)) v.pb(i);     
          if(isPrime(n/i)) v.pb(n / i);       
      }
    }
  }
  return v;
}
 
const int N = 1000;
char s[N];
 
int isPalindrome(vll a,ll s,ll e)
{
   ll len=e-s+1;
   for(ll i=s;i<=e;i++)
   {
     if(a[i]!=a[len-i-1])
     {
        return 0;
     }
   }
 
   return 1;
}
ll bit(ll a)
{
  if(a==0) return 0;
  ll ans=0;
  while(a>0)
  {
    a/=2;
    ans++;
  }
 
  return ans;
}
 
void solve()
{ 
  ll n;
  cin>>n;
 
  for(ll i=0;i<(n-1);i++)
  {
    ll p;
    cin>>p;
  }
 
  ll m; cin>>m;
  cout<<m-1<<" ";
 
  vll a(m);
  for(ll i=0;i<m;i++)
  {
    cin>>a[i];
  }
  sort(all(a));
 
  for(ll i=1;i<m;i++)
  {
    cout<<a[i]<<" ";
  }
  cout<<endl;
 
 
 
}
int main()
{
#ifndef ONLINE_JUDGE
  // for getting input from input.txt
  freopen("inputf.in", "r", stdin);
  // for writing output to output.txt
  freopen("outputf.in", "w", stdout);
#endif
  int T;
  T = 1;
  cin>>T;
 
  while (T--)
  {
    solve();
  }
 
  cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms
";
}