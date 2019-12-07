#include "TensorFinal_h.h"
#include <cassert>

using namespace std;

void getTested();


int main()
{
    getTested();
}

void getTested(){
    Tensor t_1_1(3);
    Tensor t_1_2(3);
    Tensor t_2_1(4,4);
    Tensor t_2_2(4,4);
    Tensor t_3_1(3,3,3);
    Tensor t_3_2(3,3,3);

    t_1_1.putElem(0,1);
    t_1_1.putElem(1,2);
    t_1_1.putElem(2,3);
    t_1_2.putElem(0,1);
    t_1_2.putElem(1,2);

    t_2_1.putElem({0,0},1);
    t_2_1.putElem({0,1},2);
    t_2_1.putElem({1,0},3);
    t_2_1.putElem({1,1},4);
    t_2_2.putElem({0,0},1);
    t_2_2.putElem({0,1},2);
    t_2_2.putElem({1,0},3);
    t_2_2.putElem({1,1},4);

    t_3_1.putElem({0,0,0},1);
    t_3_1.putElem({0,0,1},2);
    t_3_1.putElem({0,1,0},3);
    t_3_1.putElem({1,0,0},4);
    t_3_1.putElem({1,1,1},5);
    t_3_1.putElem({0,1,1},6);
    t_3_1.putElem({1,1,0},7);
    t_3_1.putElem({1,0,1},8);

    t_3_2.putElem({0,0,0},1);
    t_3_2.putElem({0,0,1},2);
    t_3_2.putElem({0,1,0},3);
    t_3_2.putElem({1,0,0},4);
    t_3_2.putElem({1,1,1},5);
    t_3_2.putElem({0,1,1},6);
    t_3_2.putElem({1,1,0},7);
    t_3_2.putElem({1,0,1},8);

    assert(t_1_1.getElem(1) == 2);
    assert(t_2_1.getElem(1,1)== 4);
    assert(t_3_1.getElem(1,1,1) == 5);

    Tensor t_sum = t_3_1 + t_3_2;
    assert(t_sum.getElem(1,1,0) == 14);

    Tensor t_substr = t_3_1 - t_3_2;
    assert(t_substr.getElem(1,1,0) == 0);

    t_2_1.reshape(2,2);
    assert(t_2_1.getElem(2,2)==3);

    Tensor t_to_cut(5,5);
    t_to_cut.putElem({1,1}, 3);
    Tensor fin = t_to_cut.cut({0,2}, {0,2});
    assert(fin.getElem(1,1)==3);

    cout << "success";
}
