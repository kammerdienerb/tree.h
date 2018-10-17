# tree.h

_tree.h_ is a header-only generic red/black tree implementation in C. It utilizes (abuses?) the C preprocessor to be provide a level of generality near C++ templates like the STL’s std::map.

## Using ##
To use _tree.h_, you must first `#include "tree.h"` in your source code. For every type that you wish to hold in a tree, EXACTLY ONE 'using' statement is required:

```C
/* main.c */
#include "tree.h"

use_tree(float, int);

...
```
If the either the key type or the value type is referenced with anything but a bare identifier (e.g. `char *`, `float[10]`), it must first be wrapped in a typedef:

```C
/* main.c */
#include "tree.h"

typedef char * str;

use_tree(str, double);

...
```

After that, you may use any of the following macro-like functions to create, destroy, and operate on trees and their iterators.

`tree_make(key_type, value_type)`        - Allocates, initializes, and returns a new tree.

`tree_make_c(key_type, value_type, cmp)` - Allocates, initializes, and returns a new tree with the comparator function `cmp`.

`tree_free(t)`                           - `free()`s the tree. This does NOT deallocate tree keys or values.

`tree_len(t)`                            - Returns the number of tree elements.

`tree_lookup(t, key)`                    - Search the tree for `key`. Returns an iterator.

`tree_insert(t, key, val)`               - Add the `key`, `val` pair to the tree or update the value associated with the key if it already exists.

`tree_delete(t, key)`                    - Remove `key` and its value from the tree. Returns `1` if the key was found, `0` otherwise.

`tree_begin(t)`                          - Returns an iterator to the first (ordered by key) element in the tree.

`tree_last(t)`                           - Returns an iterator to the last (ordered by key) element in the tree.

`tree_geq(t, key)`                       - Returns an iterator to the first key which is greater than or equal to `key`. Analogous to `std::map::lower_bound`.

`tree_gtr(t, key)`                       - Returns an iterator to the first key which is greater than `key`. Analogous to `std::map::upper_bound`.

`tree_it_key(it)`                        - Returns the key from iterator `it`.

`tree_it_val(it)`                        - Returns the value from iterator `it`.

`tree_it_next(it)`                       - Advances the iterator to the next (ordered by key) element in the tree.

`tree_it_prev(it)`                       - Reverses the iterator to the previous (ordered by key) element in the tree.

`tree_it_good(it)`                       - Returns `1` if the iterator is valid, `0` otherwise.

`tree_traverse(t, it)`                   - Shorthand for a `for` loop that visits every tree element (ordered by key).


By default, _tree.h_ will use the _<_ operator to compare keys. `make_tree_c` takes an additional last argument which is a function pointer that will compare keys.

See _tree_test.c_ for examples of using _tree.h_'s interface.


### Note ###
_tree.h_ requires the C preprocessor's \_\_VA\_ARGS\_\_ and so requires that it is compiled in C99 mode.

## Download ##
You can clone the project with [Git](http://git-scm.com "Git") by running:

    $ git clone git://github.com/kammerdienerb/tree.h

