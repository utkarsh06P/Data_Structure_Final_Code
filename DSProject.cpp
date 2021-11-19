#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
const int maxn = 2e6+5;
vector<int> adj[maxn];
vector<int> tadj[maxn];
bool visited[maxn];
stack<int> s;
int order[maxn];
vector<pair<char,char>>op;
vector<pair<int,int>>ch;
string distr;
vector<pair<int,pair<string,string>>>leftOut;

void dfs(int a)
{
    visited[a]=true;
    for(auto x : adj[a])
    {
        if(! visited[x])
            dfs(x);
    }
    s.push(a);
}

void tdfs(int a,int val)
{
    order[a]=val;
    for(auto x : tadj[a])
    {
        if(order[x] == -1)
            tdfs(x,val);
    }
}

int main()
{
    const char separator    = ' ';
    const int nameWidth     = 30;
    const int numWidth      = 8;
    int n,m,i,a,b;
    cout<<"Enter the number of families : ";
    cin>>n;
    cout<<"Enter the number of options : ";
    cin>>m;
    cout<<"Enter the options : (+) for you want to include and (-) for you don't want to include: "<<endl;
    char c1,c2;
    for(i=1; i<=n; i++)
    {
        cin >> c1 >> a >> c2 >>b;
        op.push_back({c1,c2});
        ch.push_back({a,b});
        if(c1 == '-' && c2 == '-')
        {
            adj[2*a].push_back(2*b + 1);
            tadj[2*b + 1].push_back(2*a);
            adj[2*b].push_back(2*a + 1);
            tadj[2*a + 1].push_back(2*b);
        }
        else if(c1 == '-' && c2 == '+')
        {
            adj[2*a].push_back(2*b);
            tadj[2*b].push_back(2*a);
            adj[2*b + 1].push_back(2*a + 1);
            tadj[2*a + 1].push_back(2*b +1);
        }
        else if(c1 == '+' && c2 == '-')
        {
            adj[2*a +1].push_back(2*b +1);
            tadj[2*b +1].push_back(2*a +1);
            adj[2*b].push_back(2*a);
            tadj[2*a].push_back(2*b);
        }
        else if(c1 == '+' && c2 == '+')
        {
            adj[2*a +1].push_back(2*b);
            tadj[2*b].push_back(2*a +1);
            adj[2*b + 1].push_back(2*a);
            tadj[2*a].push_back(2*b +1);
        }
    }

    cout<<endl;

    for(i=1; i<=(2*m)+1; i++)
    {
        order[i]=-1;
        if(! visited[i])
            dfs(i);
    }

    int j = 1;
    while(!s.empty( ))
    {
        int node = s.top();
        s.pop();
        if(order[node] == -1)
        {
            tdfs(node,j);
            j++;
        }
    }

    bool arr[m+1]= {false};
    bool check = false;
    for(i=2; i<=(2*m); i += 2)
    {
        if(order[i] == order[i+1])
        {
            check = true;
        }
        else
            arr[i/2] = order[i] > order[i+1];
    }

    for(i=1; i<=m; i++)
    {
        if(arr[i])
            distr += '+';
        else
            distr += '-';
    }

    int cnt = 0;
    for(int i = 0; i<(int)op.size(); i++)
    {
        int temp = 0;
        temp += distr[ch[i].first-1] == op[i].first;
        temp += distr[ch[i].second-1] == op[i].second;;
        if(temp == 0)
        {
            cnt++;
            string t1 = op[i].first + to_string(ch[i].first);
            string t2 = op[i].second + to_string(ch[i].second);
            leftOut.push_back({i+1,{t1,t2}});
        }
    }

    if(check)
    {
        cout<<"The distribution is NOT POSSIBLE as a few families will be left out"<<endl;
        cout<<"The distribution is : "<<endl;
        cout << left << setw(nameWidth) << setfill(separator) << "Option Number";
        cout << left << setw(nameWidth) << setfill(separator) << "Is Option included?";
        cout<<endl;
        for(int i = 1; i<=m; i++)
        {
            cout << left << setw(nameWidth) << setfill(separator)<<(to_string(i));
            if(arr[i])
            {
                cout << left << setw(nameWidth) << setfill(separator)<<"YES";
            }
            else
            {
                cout << left << setw(nameWidth) << setfill(separator)<<"NO";
            }
            cout<<endl;
        }
        cout<<"Number of families with not even 1 choice reflected in the final distribution : "<<cnt<<endl;
        cout<<"They are : "<<endl;
        cout << left << setw(nameWidth) << setfill(separator)<<"Family Number";
        cout << left << setw(nameWidth) << setfill(separator)<<"Choice 1";
        cout << left << setw(nameWidth) << setfill(separator)<<"Choice 2";
        cout<<endl;
        for(auto i : leftOut)
        {
            cout << left << setw(nameWidth) << setfill(separator)<<to_string(i.first);
            cout << left << setw(nameWidth) << setfill(separator)<<i.second.first;
            cout << left << setw(nameWidth) << setfill(separator)<<i.second.second;
            cout<<endl;
        }
        cout<<endl;
    }

    else
    {
        cout<<"The distribution is : "<<endl;
        cout << left << setw(nameWidth) << setfill(separator) << "Option Number";
        cout << left << setw(nameWidth) << setfill(separator) << "Is Option included?";
        cout<<endl;
        for(int i = 1; i<=m; i++)
        {
            cout << left << setw(nameWidth) << setfill(separator)<<(to_string(i));
            if(arr[i])
            {
                cout << left << setw(nameWidth) << setfill(separator)<<"YES";
            }
            else
            {
                cout << left << setw(nameWidth) << setfill(separator)<<"NO";
            }
            cout<<endl;
        }
        cout<<"No family was left out."<<endl;
    }
    return 0;
}
