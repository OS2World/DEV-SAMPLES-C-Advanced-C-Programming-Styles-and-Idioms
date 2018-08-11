/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <generic.h>
#include <iostream.h>
#include <string.h>

#define LocalScope(function) struct name3(function,Local,Scope) { public
#define EndLocalScope } local

void BubbleSort(int n, char *records[], char *keys[])
{
    // Bubble Sort from Knuth, Vol. 3
    LocalScope(BubbleSort):
        int bound, t;
        void CompareExchange(int j, char *records[], char *keys[]) {
            if (::strcmp(keys[j], keys[j+1]) > 0) {
                char *temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
                temp = keys[j];
                keys[j] = keys[j+1];
                keys[j+1] = temp;
                t = j;
            }
        }
    EndLocalScope;

    local.bound = n;
    do {
        local.t = -1;
        for (int j = 0; j < local.bound-1; j++) {
            local.CompareExchange(j, records, keys);
        }
        local.bound = local.t + 1;
    } while (local.t != -1);
}

char *records[] = {
    "Stroustrup, Bjarne",
    "Lippman, Stan",
    "Hansen, Tony",
    "Koenig, Andrew"
};

char *keys[] = {
    "bs",
    "stan",
    "hansen",
    "ark"
};

void main() {
    for (int i = 0; i < 4; i++) {
        cout << records[i] << "\t" << keys[i] << endl;
    }
    BubbleSort(4, records, keys);
    cout << endl;
    for (i = 0; i < 4; i++) {
        cout << records[i] <<  "\t" << keys[i] <<endl;
    }
}
