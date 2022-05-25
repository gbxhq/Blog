#include <iostream>
#include "Header/Vt.h"

using namespace std;

//完美排序
void stooge_sort(vector<int> &vt,int i,int j){
    if(vt[i]>vt[j]) swap(vt[i],vt[j]);
    if(i+1>=j)  return;

    int k = (j-i+1)/3; //三等分
    stooge_sort(vt,i,j-k); //递归前2/3区域
    stooge_sort(vt,i+k,j); //递归前后/3区域
    stooge_sort(vt,i,j-k); //再递归前2/3区域
}

int main(){

    vector<int> vt1 {6,9,5,6,8,2,0};
    stooge_sort(vt1,0,6);
    showVt(vt1);
    return 0;
}