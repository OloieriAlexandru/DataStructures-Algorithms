#ifndef LONGEST_INCREASING_SUBSEQUENCE_H
#define LONGEST_INCREASING_SUBSEQUENCE_H

// https://www.infoarena.ro/job_detail/2475261

#include <unordered_map>
#include <vector>
#include <set>
#include <utility>
template <class T>
class longestIncreasingSubsequence
{
private:
#define mkp std::make_pair
#define leftChild node << 1
#define rightChild node << 1 | 1
#define inf 999999999
#define mp make_pair
#define pii std::pair<int,int>
    std::unordered_map<T,int> index;
    std::vector<T> v;
    std::vector<int> dp, lst;
    std::vector<pii> segTree;
    int n;
    void build()
    {
        for (int i=0;i<segTree.size();++i){
            segTree[i] = mkp (-inf, i);
        }
    }
    pii query(int node, int st, int dr, int x, int y)
    {
        if (st > dr || x > y) return mkp(-inf, -1);
        if (x <= st && dr <= y)
            return segTree[node];
        int m = (st + dr) / 2;
        pii resL = mkp(-inf, -1);
        pii resR = mkp(-inf, -1);
        if (x <= m)
            resL = query(leftChild, st, m, x, y);
        if (y > m)
            resR = query(rightChild, m+1, dr, x, y);
        if (resL.first > resR.first) return resL;
        return resR;
    }
    void update(int node, int st, int dr, int x, int y, int z)
    {
        if (st == dr)
        {
            segTree[node].first = y;
            segTree[node].second = z;
            return;
        }
        int m = (st + dr) / 2;
        if (x <= m)
            update(leftChild, st, m, x, y, z);
        else
            update(rightChild, m+1, dr, x, y, z);
        if (segTree[leftChild].first > segTree[rightChild].first)
            segTree[node] = segTree[leftChild];
        else
            segTree[node] = segTree[rightChild];
    }
    void prepareForLIS()
    {
        index.clear();
        std::set<T> normalize;
        for (auto x:v)
            normalize.insert(x);
        n = 0;
        for (auto x:normalize)
            index[x] = ++n;
        segTree.resize(n*4+4);
        build();
        dp.resize(v.size(), 0);
        lst.resize(v.size(), -1);
    }
public:
    longestIncreasingSubsequence() {}
    longestIncreasingSubsequence(int sz) {v.resize(sz);}
    void addElement(T x)
    {
        v.push_back(x);
    }
    bool getLIS(std::vector<T>& ans)
    {
        if (!v.size()) return false;
        ans.clear();
        prepareForLIS();
        dp[0] = 0;
        update(1, 1, n, index[v[0]], 1, 0);
        pii best;
        for (int i=1;i<v.size();++i)
        {
            best = query(1, 1, n, 1, index[v[i]]-1);
            if (best.first == -inf)
                dp[i] = 1;
            else
            {
                dp[i] = best.first + 1;
                lst[i] = best.second;
            }
            update(1, 1, n, index[v[i]], dp[i], i);
        }
        int maxx = -1, pos;
        for (int i=0;i<v.size();++i){
            if (dp[i] > maxx) maxx = dp[i], pos = i;
        }
        while (pos != -1)
        {
            ans.push_back(v[pos]);
            pos = lst[pos];
        }
        std::reverse(ans.begin(), ans.end());
        return true;
    }
};

#endif
