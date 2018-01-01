//
// Created by Kangbeibei on 2018/1/1.
//
#include <cassert>
#include <deque>
#include "DumpWater.h"
#include <algorithm>
#include <functional>

/*
 * from  从哪个桶中倒水
 * to  将水倒在哪个桶中
 * water 倒了多少省水*/
typedef struct tagACTION{
    int from;
    int to;
    int water;
}ACTION;
typedef struct BucketState{
    int bucket_cap[BUCKETS_COUNT];
    int bucket_s[BUCKETS_COUNT];
    ACTION curAction;//初始{-1，1，8}
    bool IsBucketEmpty(int from);
    bool IsBucketFull(int to);
    bool IsFinalState();
    bool CanTakeDumpAction(int from, int to);

};

bool BucketState::IsBucketEmpty(int from){
    return !bucket_s[from];
}
bool BucketState::IsBucketFull(int to){
    return bucket_s[to] == bucket_cap[to];
}
bool BucketState::CanTakeDumpAction(int from, int to){
    assert((from >= 0) && (from < BUCKETS_COUNT));
    assert((to >= 0) && (to < BUCKETS_COUNT));
    /*不是同一个桶，且from桶中有水
     *且to桶中的水不满*/
    return ((from != 0) && !IsBucketEmpty(from) && !IsBucketFull(to));
}
bool BucketState::IsFinalState(){
    return bucket_s[0] == 4 && bucket_s[1] == 4;
}
bool IsSameBucketState(const BucketState state, const BucketState newState){
    for(int i = 0; i < BUCKETS_COUNT; i++){
        if(state.bucket_s[i] != newState.bucket_s[i]) return false;
    }
    return true;
}
bool IsProessedState(std::deque<BucketState>& states, const BucketState& newState){
    std::deque<BucketState>::iterator it;

    it = find_if(states.begin(), states.end(), std::bind2nd(std::ptr_fun(IsSameBucketState), newState));

    return (it != states.end());
}

void PrintResult(std::deque<BucketState>& states){
    for(auto it = states.begin(); it < states.end(); it++){
        if(it < states.end() - 1){
            std::cout<<(*it).bucket_s<<"->";
        }else{
            std::cout<<(*it).bucket_s<<std::endl;
        }
    }
}

void SearchState(std::deque<BucketState>& states){
    /*每次都从当前状态开始*/
    BucketState current = states.back();
    if(current.IsFinalState()){
        PrintResult(states);
        return;
    }
}

