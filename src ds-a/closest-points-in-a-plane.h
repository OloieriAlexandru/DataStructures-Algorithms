#ifndef CLOSEST_POINTS_IN_A_PLANE_H
#define CLOSEST_POINTS_IN_A_PLANE_H
#include <vector>
#include <utility>

// https://infoarena.ro/job_detail/2446463?action=view-source

template <class T>
class closestPoints
{
#define pair std::pair
#define vector std::vector
#define lld long long
#define minn(a,b) ((a)<(b)?(a):(b))
#define infinity 2223372036854775807LL
#define uint unsigned int
private:
    vector<pair<T,T>>v;
    vector<pair<T,T>>xv,yv;
    lld distance(pair<T,T> &a, pair<T,T> &b)
    {
        return  1LL * (a.first - b.first) * (a.first - b.first) +
                1LL * (a.second - b.second) * (a.second - b.second);
    }
    lld minnn(T a, T b)
    {
        return minn(a,b);
    }
    lld divideEtImpera(int l, int r)
    {
        if (l >= r) return infinity;
        if (r - l == 1)
        {
            if (yv[l] > yv[l + 1])
                swap(yv[l],yv[l+1]);
            return distance(xv[l], xv[l+1]);
        }
        int m = (l + r) / 2;
        lld bst = minnn(divideEtImpera(l,m-1),divideEtImpera(m,r));
        sort(yv.begin()+l,yv.begin()+r+1);
        int sz = 0;
        for (int i=l; i<=r; ++i)
            if (abs(yv[i].second - xv[m].first) <= bst)
                v[sz++] = yv[i];
        for (int i=0; i<sz-1; ++i)
            for (int j=i+1; j<sz && j - i < 10; ++j)
                bst = minnn(bst, distance(v[i],v[j]));
        return bst;
    }
public:
    closestPoints() {}
    closestPoints(uint expectedMaximumN)
    {
        v.resize(expectedMaximumN);
        xv.resize(expectedMaximumN);
    }
    void addPoint(T a, T b)
    {
        xv.push_back(make_pair(a,b));
    }
    lld computeMinimumDistance()
    {
        sort(xv.begin(), xv.end());
        yv.clear();
        for (int i=0; i<xv.size(); ++i)
            yv.push_back(make_pair(xv[i].second, xv[i].first));
        v.resize(xv.size() + 1);
        return divideEtImpera(0,xv.size()-1);
    }
#undef vector
#undef pair
};

#endif
