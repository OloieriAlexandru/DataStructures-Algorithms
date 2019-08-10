#ifndef STRING_MATCHING_RABIN_KARP_H
#define STRING_MATCHING_RABIN_KARP_H
#include <string>

// https://infoarena.ro/job_detail/2446863?action=view-source

class rabinKarp
{
private:
#define mod 1000000007
#define lld long long
#define uint unsigned int
#define RABIN_KARP_CHECK_CREATED(ret) if (!created) return ret
#define RABIN_KARP_OK 1
#define RABIN_KARP_NO 2
#define RABIN_KARP_ERROR 3
#define pb push_back
    lld *pows, patternHash;
    uint n, pw = 31, patternLen;
    bool created, patternSet;
    lld computeSize(std::string &pattern)
    {
        lld ret = 0;
        for (uint i=0; i<pattern.size(); ++i)
            ret = (ret + pows[pattern.size() - i - 1] * pattern[i]) % mod;
        return ret;
    }
public:
    rabinKarp(): pows(nullptr), created(false), patternSet(false) {}
    bool create(uint maxPatternSize)
    {
        if (created) return false;
        pows = new lld[maxPatternSize + 2];
        if (pows == nullptr)
            return false;
        n = maxPatternSize;
        pows[0] = 1;
        for (uint i=1; i<=maxPatternSize; ++i)
            pows[i] = (pows[i-1] * pw) % mod;
        created = true;
        return true;
    }
    bool setPattern(std::string &pattern)
    {
        RABIN_KARP_CHECK_CREATED(false);
        if (pattern.size() >= n) return false;
        patternHash = computeSize(pattern);
        patternLen = pattern.size();
        patternSet = true;
        return false;
    }
    uint patternsAppear(std::string &source)
    {
        RABIN_KARP_CHECK_CREATED(RABIN_KARP_ERROR);
        if (!patternSet) return RABIN_KARP_ERROR;
        lld currentHash = 0;
        for (uint i=0; i<patternLen; ++i)
            currentHash = (currentHash + pows[patternLen-i-1] * source[i]) % mod;
        if (currentHash == patternHash)
            return RABIN_KARP_OK;
        for (uint i=patternLen; i<source.size(); ++i)
        {
            currentHash = currentHash - source[i-patternLen] * pows[patternLen-1];
            currentHash %= mod;
            if (currentHash < 0)
                currentHash = mod + currentHash;
            currentHash = (currentHash * pw + source[i] ) % mod;
            if (currentHash == patternHash)
                return RABIN_KARP_OK;
        }
        return RABIN_KARP_NO;
    }
    uint getAllPatternMatches(std::string &source, std::vector<uint> &appearences)
    {
        RABIN_KARP_CHECK_CREATED(RABIN_KARP_ERROR);
        if (!patternSet) return RABIN_KARP_ERROR;
        appearences.clear();
        lld currentHash = 0;
        for (uint i=0; i<patternLen; ++i)
            currentHash = (currentHash + pows[patternLen-i-1] * source[i]) % mod;
        if (currentHash == patternHash)
            appearences.pb(0);
        for (uint i=patternLen; i<source.size(); ++i)
        {
            currentHash = currentHash - source[i-patternLen] * pows[patternLen-1];
            currentHash %= mod;
            if (currentHash < 0)
                currentHash = mod + currentHash;
            currentHash = (currentHash * pw + source[i]) % mod;
            if (currentHash == patternHash)
                appearences.pb(i-patternLen+1);
        }
        if (appearences.size())
            return RABIN_KARP_OK;
        else
            return RABIN_KARP_NO;
    }
};

#endif
