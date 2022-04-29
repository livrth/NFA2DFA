#include <bits/stdc++.h>
using namespace std;
// #define DEBUG2

void solve() {
    set<string> T; //字符集
    vector<string> S; //NFA初始状态集合

    int T_SIZE; //字符集大小
    int STATE_SIZE; //NFA状态数量

    cin >> T_SIZE >> STATE_SIZE;
    map<pair<string, string>, vector<string>> mp;
    for (int i = 0; i < STATE_SIZE; i++) {
        string state; //具体状态
        cin >> state;
        S.push_back(state);
        for (int i = 0; i < T_SIZE; i++) { //当前状态对于所有字符集能到的状态
            string alpha;
            cin >> alpha;
            T.insert(alpha);
            int set_size;
            cin >> set_size;
            for (int i = 0; i < set_size; i++) {
                string single_state;
                cin >> single_state;
                mp[make_pair(state, alpha)].push_back(single_state);
            }
        }
    }

#ifdef DEBUG1
    for (auto t : mp) {
        auto pp = t.first;
        auto collection = t.second;
        cout << pp.first << ' ' <<  pp.second << endl;
        for (auto x : collection) cout << x << ' ';
        cout << endl;
    }
#endif

    //枚举所有子集
    vector<vector<string>> ALL(1 << STATE_SIZE, vector<string>());
    for (int i = 0; i < (1 << STATE_SIZE); i++) {
        for (int k = 0; k < STATE_SIZE;  k++) {
            if ((i >> k) & 1) {
                ALL[i].push_back(S[k]);
            }
        }
    }

    //排序便于输出
    sort(ALL.begin(), ALL.end(), [&](vector<string> T1, vector<string> T2) {
        return T1.size() < T2.size();
    });

#ifdef DEBUG2
    sort(ALL.begin(), ALL.end(), [&](vector<string> T1, vector<string> T2) {
        return T1.size() < T2.size();
    });
    for (auto t : ALL) {
        for (auto j : t) {
            cout << j << ' ';
        }
        cout << endl;
    }
#endif

    vector<vector<string>> reachable_state; //所有可达状态

    for (auto t : ALL) { //遍历所有子集 [p,q,r] [q,r]...
        for (auto set_ele : t) cout << set_ele << ' ';
        cout << "#: ";
        for (auto c : T) { //0, 1 输入
            set<string> temp_union; //[p,0] [q,0] [r,0] union
            for (auto j : t) { //枚举所有字符集  [p,0] [q,0] [r,0]  / [p,1][q,1][r,1]
                auto v = mp[make_pair(j, c)];
                for (auto ele : v) temp_union.insert(ele);
            }
            if (temp_union.size() > 1 && temp_union.count("NULL"))
                temp_union.erase("NULL");
            for (auto union_ele : temp_union) cout << union_ele << ' ';
            cout << "| ";
        }
        cout << endl;
    }
    system("pause");

}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}