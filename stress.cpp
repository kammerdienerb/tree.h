#include <stdio.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tree.h"

use_tree(int, float);

int N = 1000000;

template <typename T>
void equ(T a, T b, const char * message) {
    if (a != b) {
        printf("\n%s\n", message);
        std::cout << "Expected " << a << " got " << b << "\n";
        exit(1);
    }
}

int main(int argc, char ** argv) {
    std::map<int, float>           m;
    std::map<int, float>::iterator mit;
    tree(int, float)               t;
    tree_it(int, float)            it;
    int                            i,
                                   r,
                                   len;

    if (argc > 2) {
        printf("usage: %s [N]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        sscanf(argv[1], "%d", &N);
    }

    t = tree_make(int, float);

    srand(time(NULL));

    for (i = 0; i < N; i += 1) {
        printf("Testing insertion...%d of %d                     \r", i + 1, N);
        r = rand() % (10 * N);
        m[r] = (float)r * r;
        tree_insert(t, r, (float)r * r);
    }

    printf("\n");

    printf("Testing length...");
    equ(m.size(), (size_t)tree_len(t), "elem size mismatch");
    len = m.size();
    printf("%d\n", len);

    for (i = 0; i < N / 10;) {
        printf("Testing deletion from beginning...%d of %d                     \r", ++i, N / 10);

        mit = m.begin();
        it  = tree_begin(t);

        m.erase(mit);

        equ(1, tree_delete(t, tree_it_key(it)), "tree_delete() returned incorrect value");
        equ(m.size(), (size_t)tree_len(t), "size mismatch");
    }

    printf("\n");

    for (i = 0; i < N / 10;) {
        printf("Testing deletion from end...%d of %d                     \r", ++i, N / 10);

        mit = --m.end();
        it  = tree_last(t);

        m.erase(mit);

        equ(1, tree_delete(t, tree_it_key(it)), "tree_delete() returned incorrect value");
        equ(m.size(), (size_t)tree_len(t), "size mismatch");
    }

    printf("\n");

    for (i = 0; i < N / 10;) {
        printf("Testing lookup and random deletion...%d of %d                     \r", i + 1, N / 10);

        r = rand() % (10 * N);

        mit = m.find(r);
        it  = tree_lookup(t, r);

        if (mit == m.end()) {
            if (tree_it_good(it)) {
                printf("\nExpected bad iterator. Got %p (%d, %f)\n", it._node, tree_it_key(it), tree_it_val(it));
                exit(1);
            }
        } else {
            equ(mit->first, tree_it_key(it), "key mismatch");
            equ(mit->second, tree_it_val(it), "val mismatch");

            m.erase(mit);

            equ(1, tree_delete(t, tree_it_key(it)), "tree_delete() returned incorrect value");
            equ(m.size(), (size_t)tree_len(t), "size mismatch");

            i += 1;
        }
    }

    printf("\n");

    len = m.size();
    it  = tree_begin(t);
    mit = m.begin();
    i   = 0;

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
