#include <iostream>
#include "segment-tree-min-max.h"
using namespace std;

int main()
{
    segmentTreeMinMax arbIntervaleMinMax;
    int a[] = {0,1,2,3,10,10,6,7,8,9,10};
    arbIntervaleMinMax.create(a,10u);
    cout<<arbIntervaleMinMax.queryMax(4,9);
    return 0;
}
