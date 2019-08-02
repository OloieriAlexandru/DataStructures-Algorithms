#ifndef LONGEST_COMMON_SUBSEQUENCE_H
#define LONGEST_COMMON_SUBSEQUENCE_H
#include <vector>

// https://infoarena.ro/job_detail/2445112?action=view-source

template <class T>
class longestCommonSubsequence
{
private:
#define pb push_back
#define maxx(a,b) (a)>(b)?(a):(b)
#define uint unsigned int
    std::vector<T>sa, sb;
public:
    void addElementA(T &val)
    {
        sa.push_back(val);
    }
    void addElementB(T &val)
    {
        sb.push_back(val);
    }
    void resetA()
    {
        sa.clear();
    }
    void resetB()
    {
        sb.clear();
    }
    void reset()
    {
        resetA();
        resetB();
    }
    uint getLCSLen()
    {
        std::vector<uint> dp[2];
        dp[0].resize(sb.size() + 1, 0);
        dp[1].resize(sb.size() + 1, 0);
        for (uint i=0; i<sa.size(); ++i)
        {
            dp[i%2][0] = (sa[i] == sb[0] ? 1 : 0);
            for (uint j=1; j<sb.size(); ++j)
                if (sa[i] == sb[j])
                    dp[i%2][j] = dp[!(i%2)][j-1] + 1;
                else
                    dp[i%2][j] = maxx(dp[!(i%2)][j], dp[i%2][j-1]);
        }
        return dp[!(sa.size()%2)][sb.size()-1];
    }
    void getLCS(std::vector<T> &ans)
    {
        std::vector<std::vector<uint>>dp;
        dp.resize(sa.size());
        for (uint i=0; i<sa.size(); ++i)
            dp[i].resize(sb.size(), 0);
        dp[0][0] = (sa[0] == sb[0] ? 1 : 0);
        for (uint j=1; j<sb.size(); ++j)
            if (sa[0]==sb[j]) dp[0][j] = 1;
            else
                dp[0][j] = dp[0][j-1];
        for (uint i=1; i<sa.size(); ++i)
        {
            dp[i][0] = (sa[i] == sb[0] ? 1 : 0);
            for (uint j=1; j<sb.size(); ++j)
                if (sa[i] == sb[j])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = maxx(dp[i-1][j], dp[i][j-1]);
        }
        ans.clear();
        for (int i=sa.size()-1, j=sb.size()-1; i>=0&&j>=0;)
            if (sa[i] == sb[j])
            {
                ans.push_back(sa[i]);
                --i, --j;
            }
            else if (i==0)--j;
            else if (j==0)--i;
            else if (dp[i-1][j] > dp[i][j-1])--i;
            else --j;
    }
};

#endif
