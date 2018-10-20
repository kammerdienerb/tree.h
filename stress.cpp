#include <stdio.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tree.h"

use_tree(int, float);

#define N 100000000

template <typename T>
void equ(T a, T b, const char * message) {
    if (a != b) {
        printf("\n%s\n", message);
        std::cout << "Expected " << a << " got " << b << "\n";
        exit(1);
    }
}

int main() {
    std::map<int, float> m;
    tree(int, float)     t;
    tree_it(int, float)  it;
    int                  i,
                         r,
                         len;

    t = tree_make(int, float);

    srand(time(NULL));

    for (i = 0; i < N; i += 1) {
        printf("Testing insertion...%d of %d                     \r", i + 1, N);
        r = rand() % (10 * N);
        m[r] = (float)r * r;
        tree_insert(t, r, (float)r * r);
    }

    printf("\n");

    printf("Testing final length...");
    equ(m.size(), (size_t)tree_len(t), "elem size mismatch");
    len = m.size();
    printf("%d\n", len);

    it       = tree_begin(t);
    auto mit = m.begin();
    i        = 0;

    /* print_tree(t->_root, 0); */

    for (;;) {
        if (mit == m.end())
            break;
        printf("Testing forward iteration...%d of %d                     \r", ++i, len);
        equ(mit->first, tree_it_key(it), "key mismatch");
        equ(mit->second, tree_it_val(it), "val mismatch");
        tree_it_next(it);
        mit++;
    }
    
    printf("\n");

    it  = tree_last(t);
    mit = --m.end();
    i   = 0;

    for (;;) {
        printf("Testing reverse iteration...%d of %d                     \r", ++i, len);
        equ(mit->first, tree_it_key(it), "key mismatch");
        equ(mit->second, tree_it_val(it), "val mismatch");

        if (mit == m.begin())
            break;

        tree_it_prev(it);
        mit--;
    }
    
    printf("\n");


    for (i = 0; i < N;) {
        printf("Testing lower bound...%d of %d                     \r", i + 1, N);
        r = rand() % (10 * N);        
        mit = m.lower_bound(r);
        it  = tree_geq(t, r);
        
        if (mit != m.end()) {
            equ(mit->first, tree_it_key(it), "key mismatch");
            equ(mit->second, tree_it_val(it), "val mismatch");
            i += 1;
        } else {
            if (tree_it_good(it)) {
                printf("\nExpected bad iterator. Got %p (%d, %f)\n", it._node, tree_it_key(it), tree_it_val(it));
                exit(1);
            }

        }
    }

    printf("\n");

    for (i = 0; i < N;) {
        printf("Testing upper bound...%d of %d                     \r", i + 1, N);
        r = rand() % (10 * N);        
        mit = m.upper_bound(r);
        it  = tree_gtr(t, r);

        if (mit != m.end()) {
            equ(mit->first, tree_it_key(it), "key mismatch");
            equ(mit->second, tree_it_val(it), "val mismatch");
            i += 1;
        } else {
            if (tree_it_good(it)) {
                printf("\nExpected bad iterator. Got %p (%d, %f)\n", it._node, tree_it_key(it), tree_it_val(it));
                exit(1);
            }
        }
    }
    
    printf("\n");

    printf("Testing cleanup...\n");
    tree_free(t);

    printf("Done.\n");
}
