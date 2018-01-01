//
// Created by Kangbeibei on 2018/1/1.
//
/*
 * 假设有8升、3升、5升容量的3个桶，
 * 最初8升的桶装满了水
 * 请问将这8升水等分有几种方法？
 * (PS: 只能使用题中的3个桶.)*/
#ifndef DUMPWATER_DUMPWATER_H
#define DUMPWATER_DUMPWATER_H

#include <iostream>
#define BUCKETS_COUNT 3
int Dumpwater();
bool CanTakeDumpAction(int from, int to);

#endif //DUMPWATER_DUMPWATER_H
