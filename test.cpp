#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
#define pb push_back
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define oo 2e9+7
const int MOD = 1e9 + 7;
 
vector<vector<ll>> v(200, vll(200));

void prep(){
    ll count = 0;
    for (int j = 0; j < 200; j+=2)
    {
        for (int i = 0; i < 200; i+=2)
        {
            v[i][j] = count++;
            v[i][j+1] = count++;
            v[i+1][j] = count++;
            v[i+1][j+1] = count++;
        }
    }
}

void solve(int oops)
{
    int n, m;
    cin >> n >> m;

    cout << n*m << endl;
    vector<vector<ll>> v(n, vll(m));
    ll count = 0;
    for (int i = 0; i < n-1; i+=2)
    {
        for (int j = 0; j < m-1; j+=2)
        {
            v[i][j] = count++;
            v[i][j+1] = count++;
            v[i+1][j] = count++;
            v[i+1][j+1] = count++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    

}
int main()
{
    #ifdef ONLINE_JUDGE
       fast_cin();
    #endif
    #ifndef ONLINE_JUDGE
       freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
    #endif
    // prep();
    int  t = 1;
    cin >> t;
    int oops = 1;
    while(t--){
       solve(oops);
       oops++;
    }
    return 0;
}