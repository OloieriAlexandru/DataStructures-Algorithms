#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H
#include <vector>
#include <algorithm>
#include <stack>

// https://infoarena.ro/job_detail/2448095?action=view-source

class convexHull
{
#define ld long double
#define mp std::make_pair
#define pb push_back
#define uint unsigned int
private:
    struct point
    {
        ld x, y;
        point(ld x, ld y, convexHull *pt)
        {
            this->x = x, this->y = y, this->ptr = pt;
        }
        convexHull *ptr;
        bool operator<(point other) const
        {
            point third = ptr->points[0];
            point me = *this;
            return (ptr->crossProduct(third, me, other) < 0);
        }
        bool isSmaller(point &other)
        {
            return x < other.x || (x == other.x && y < other.y);
        }
    };
    std::vector<point>points;
    ld crossProduct(point a, point b, point c) const
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    void sortPoints()
    {
        int minPos = 0;
        for (uint i=1;i<points.size();++i)
            if (points[i].isSmaller(points[minPos]))
                minPos = i;
        std::swap(points[0], points[minPos]);
        auto it = points.begin();++it;
        sort(it, points.end());
    }
public:
    void addPoint(ld x, ld y)
    {
        points.push_back(point(x, y, this));
    }
    bool getConvexHull(std::vector<std::pair<ld,ld>> &ans)
    {
        if (points.size() < 3) return false;
        ans.clear();
        sortPoints();
        std::stack<point> st;
        st.push(points[0]);
        points.push_back(points[0]);
        for(uint i=1;i<points.size()-1;++i)
        {
            if (crossProduct(st.top(), points[i], points[i+1]) > 0)
                while (!st.empty())
            {
                points[i] = st.top();
                st.pop();
                if (crossProduct(st.top(), points[i], points[i+1]) <= 0) break;
            }
            st.push(points[i]);
        }
        while (!st.empty())
        {
            ans.pb(mp(st.top().x, st.top().y));
            st.pop();
        }
        return true;
    }
#undef x
#undef y
};

#endif
