#ifndef MAJORITY_ELEMENT_H
#define MAJORITY_ELEMENT_H
#include <vector>

// https://infoarena.ro/job_detail/2446030?action=view-source

template<class T>
class majorityElement
{
private:
#define uint unsigned int
    std::vector<T>elements;
public:
    void addElement(T &el)
    {
        elements.push_back(el);
    }
    bool findMajorityElement(T &ans, uint &nrAp)
    {
        int ap = 1;
        T maj = elements[0];
        for (uint i=1;i<elements.size();++i)
        {
            if (elements[i] == maj)
                ++ap;
            else
                --ap;
            if (ap == -1)
                ap = 1, maj = elements[i];
        }
        ap = 0;
        for (uint i=0;i<elements.size();++i)
            if (elements[i] == maj) ++ap;
        bool res = false;
        if (ap * 2 > elements.size()) res = true, ans = maj, nrAp = ap;
        return res;
    }
};

#endif
