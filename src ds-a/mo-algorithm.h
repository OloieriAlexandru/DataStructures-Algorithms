#ifndef MO_ALGORITHM_H
#define MO_ALGORITHM_H

// https://www.spoj.com/status/DQUERY,alexoloieri/ -> 24396919

class moAlgorithm
{
private:
#define MO_CHECK_CREATED(ret) if (!created) return ret
#define uint unsigned int
#define vector std::vector
#define pair std::pair
#define mkp std::make_pair
#define pb push_back
    vector<pair<pair<uint,uint>,uint>>queries;
    uint* arr, *cnt, qCount;
    bool created;
public:
    moAlgorithm(): arr(nullptr), created(false), cnt(nullptr), qCount(0) {}
    bool create(uint n, uint* values, uint maxValue)
    {
        if (created)
            return false;
        if (values == nullptr)
            return false;
        arr = new uint[n+1];
        if (arr == nullptr)
            return false;
        cnt = new uint[maxValue+5];
        if (cnt == nullptr)
        {
            delete[] arr;
            return false;
        }
        for (uint i=0;i<maxValue+5;++i)
            cnt[i] = 0;
        for (uint i=0; i<n; ++i)
            arr[i] = values[i];
        created = true;
        return true;
    }
    bool addQuery(uint x, uint y)
    {
        MO_CHECK_CREATED(false);
        queries.pb(mkp(mkp(x,y), qCount++));
        return true;
    }
    bool getAnsToQueries(vector<uint>& ans)
    {
        MO_CHECK_CREATED(false);
        ans.clear();
        ans.resize(queries.size()+1,0);

        sort(queries.begin(), queries.end(), [](pair<pair<uint,uint>,uint> a, pair<pair<uint,uint>,uint> b)
        {
            uint v1 = a.first.first / 550;
            uint v2 = b.first.first / 550;
            if (v1 == v2)
                return a.first.second < b.first.second;
            return v1 < v2;
        });

        int mo_left =0, mo_right = -1;
        uint anss = 0;
        for (int i=0; i<(int)queries.size(); ++i)
        {
            int lft = queries[i].first.first;
            int rgh = queries[i].first.second;
            while (mo_right<rgh)
            {
                ++mo_right;
                ++cnt[arr[mo_right]];
                if (cnt[arr[mo_right]]==1)
                    ++anss;
            }
            while (mo_left<lft)
            {
                --cnt[arr[mo_left]];
                if (!cnt[arr[mo_left]])--anss;
                ++mo_left;
            }
            while (mo_left>lft)
            {
                --mo_left;
                ++cnt[arr[mo_left]];
                if(cnt[arr[mo_left]]==1)
                    ++anss;
            }
            while (mo_right>rgh)
            {
                --cnt[arr[mo_right]];
                if (!cnt[arr[mo_right]])--anss;
                --mo_right;
            }
            ans[queries[i].second] = anss;
        }
        return true;
    }
};

#endif
