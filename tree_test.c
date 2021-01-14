#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tree.h"

use_tree(int, float);
typedef char *str;
use_tree_c(str, str, strcmp);

void print_tree_items(tree(int, float) t) {
    int i = 0;

    printf("tree with %llu items:\n", tree_len(t));

    for (
    tree_it(int, float) it = tree_begin(t);
    tree_it_good(it);
    tree_it_next(it)) {
        printf("%d -- %d: %f\n", i++, tree_it_key(it), tree_it_val(it));
    }
}

void print_tree(tree_node(int, float) node, int level) {
    if (!node)
        return;
    int i;
    print_tree(node->_children[1], level + 1);
	for (i = 0; i < level; ++i)
		printf("  ");
	printf("%d(%d) = %f\n", node->_key, node->_parent ? node->_parent->_key : -1, node->_val);
    print_tree(node->_children[0], level + 1);
}

int main() {
    tree(int, float) t = tree_make(int, float);
    tree(str, str) s_t = tree_make(str, str);

    for (int i = 0; i < 10; i += 1) {
        tree_insert(t, i * i, (float)i);
    }

    print_tree(t->_root, 0);

    tree_it(int, float) it = tree_lookup(t, 49);

    if (tree_it_good(it)) {
        printf("found 49: %f\n", tree_it_val(it));
    } else {
        printf("did not find 49\n");
    }
    it = tree_lookup(t, 80);
    if (tree_it_good(it)) {
        printf("found 80: %f\n", tree_it_val(it));
    } else {
        printf("did not find 80\n");
    }

    it = tree_geq(t, 49);
    printf("geq(49) = %d\n", tree_it_key(it));

    it = tree_gtr(t, 49);
    printf("gtr(49) = %d\n", tree_it_key(it));

    tree_traverse(t, it) {
        printf("%d -- %f\n", tree_it_key(it), tree_it_val(it));
    }

    tree_it_prev(it);

    printf("last: %d\n", tree_it_key(it));

    for (it = tree_begin(t); tree_it_good(it); it = tree_begin(t)) {
        printf("-----------------------\ndeleting %d\n", tree_it_key(it));
        tree_delete(t, tree_it_key(it));
        print_tree(t->_root, 0);
    }

    tree_insert(s_t, strdup("epoch"),    strdup("exultant"));
    tree_insert(s_t, strdup("scarf"),    strdup("magic"));
    tree_insert(s_t, strdup("feeling"),  strdup("general"));
    tree_insert(s_t, strdup("fearless"), strdup("tremendous"));
    tree_insert(s_t, strdup("dapper"),   strdup("spicy"));
    tree_insert(s_t, strdup("helpful"),  strdup("fool"));
    tree_insert(s_t, strdup("laugh"),    strdup("tan"));
    tree_insert(s_t, strdup("toe"),      strdup("tacky"));
    tree_insert(s_t, strdup("flight"),   strdup("eager"));
    tree_insert(s_t, strdup("oval"),     strdup("income"));
    tree_insert(s_t, strdup("jitter"),   strdup("weigh"));
    tree_insert(s_t, strdup("yam"),      strdup("small"));
    tree_insert(s_t, strdup("aloof"),    strdup("popsicle"));

    if (tree_delete(s_t, "doesn't exist"))
        printf("how did we delete a key that doesn't exist?\n");

    char * k, *v;
    tree_it(str, str) s_it;

    s_it = tree_lookup(s_t, "oval");
    k = tree_it_key(s_it);
    v = tree_it_val(s_it);

    if (tree_delete(s_t, "oval")) {
        printf("deleted 'oval'\n");
        free(k);
        free(v);
    }

    printf("\n");

    int max_len = 0;
    tree_traverse(s_t, s_it) {
        int l = strlen(tree_it_key(s_it));
        if (l > max_len)
            max_len = l;
    }
    tree_traverse(s_t, s_it) {
        printf("%*s %s\n", -max_len, tree_it_key(s_it), tree_it_val(s_it));
        free(tree_it_key(s_it));
        free(tree_it_val(s_it));
    }

    tree_free(s_t);
    tree_free(t);

    return 0;
}
