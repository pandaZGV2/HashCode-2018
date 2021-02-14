#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long int ull;
typedef long int li;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define f first
#define s second
#define pb push_back
#define mp make_pair

#define file_read                                         \
    freopen("input/c_no_hurry.in", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define endl "\n"
#define iamspeed                 \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
class ride
{
public:
    pi start;
    pi finish;
    int earliest;
    int latest;
    ll distance;
    int score;
    int id;
    ride()
    {
        distance = 0;
        id = 0;
    }
};
class car
{
public:
    vector<pair<pi, pi>> sflist;
    int bonus;
    vector<int> ridelist;
    int time;
    int distance;
    car()
    {
        time = 0;
        bonus = 0;
        distance = 0;
    }
};
bool cmpfunc(ride lhs, ride rhs)
{
    return lhs.earliest < rhs.earliest;
}
int main(void)
{
    file_read;
    iamspeed;
    int R, C, F, N, B, T;
    cin >> R >> C >> F >> N >> B >> T;
    vector<ride> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i].start.f >> a[i].start.s >> a[i].finish.f >> a[i].finish.s >> a[i].earliest >> a[i].latest;
        a[i].id = i;
        a[i].distance = abs(a[i].start.f - a[i].finish.f) + abs(a[i].start.s - a[i].finish.s);
    }
    sort(a.begin(), a.end(), cmpfunc);
    vector<car> fleet(F);
    for (int i = 0; i < F; i++)
    {
        if (a.empty())
        {
            break;
        }
        fleet[i].sflist.pb(mp(a[0].start, a[0].finish));
        fleet[i].ridelist.pb(a[0].id);
        fleet[i].time = a[0].distance + (a[0].start.f + a[0].start.s);
        a.erase(a.begin());
        for (int j = 0; j < a.size(); j++)
        {
            if (fleet[i].time <= a[j].earliest or a[j].latest-fleet[i].time)
            {
                if (fleet[i].time == a[j].earliest)
                {
                    fleet[i].bonus += B;
                }
                fleet[i].sflist.pb(mp(a[j].start, a[j].finish));
                fleet[i].ridelist.pb(a[j].id);
                fleet[i].time += a[j].distance + (abs(a[j].start.f - fleet[i].sflist[fleet[i].sflist.size() - 1].s.f) + abs(a[j].start.s - fleet[i].sflist[fleet[i].sflist.size() - 1].s.s));
                fleet[i].distance += a[j].distance;
            }
            a.erase(a.begin() + j);
        }
    }
    int score = 0;
    for (int i = 0; i < F; i++)
    {
        if (fleet[i].time != 0)
        {
            score += fleet[i].distance + fleet[i].bonus;
            cout << i + 1 << " ";
            for (auto r : fleet[i].ridelist)
            {
                cout << r << " ";
            }
            cout << endl;
        }
    }
    cout<<score<<endl;


    return 0;
}