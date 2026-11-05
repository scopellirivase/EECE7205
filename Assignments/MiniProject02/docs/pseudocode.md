# Pseudocode

Pseudocode for the operations in `airport_bst.cpp`. Keys are IATA codes compared as
strings. `h` is the height of the tree, and insert, search and delete run in O(h).
Insert, search and delete are iterative; the other tree functions are recursive
(depth at most `h`, which is at most 6,071 even for a sorted build).

## Task 1: load and build

```
LOAD(file):                                   // data/airports.csv
    records <- empty array;  skipped <- 0
    for each line of file:
        cells <- SPLIT-CSV(line)              // a comma inside "quotes" does not split
        if cells has fewer than 8 fields or cells[4] is not 3 characters (\N):
            skipped <- skipped + 1
        else
            append Airport(cells) to records  // also stored in a code -> record table

SPLIT-CSV(line):
    insideQuotes <- false;  cell <- ""
    for each character ch of line:
        if ch = '"':
            if insideQuotes and next character = '"': add '"' to cell, skip it   // escaped quote
            else insideQuotes <- not insideQuotes
        else if ch = ',' and not insideQuotes:
            output cell;  cell <- ""
        else add ch to cell
    output cell

BUILD():
    root <- NULL
    for i <- 0 to n - 1:                      // file order
        if INSERT(records[i]) fails: report duplicate (rule I4: not inserted, counted)
    report the number of insertions, HEIGHT and AVERAGE-DEPTH
```

## Insert (iterative)

```
INSERT(a):
    parent <- NULL;  cur <- root
    while cur != NULL:
        if a.key = cur.key: return false      // duplicate, nothing inserted
        parent <- cur
        if a.key < cur.key: cur <- cur.left
        else                cur <- cur.right
    node <- new Airport copied from a, with left = right = NULL
    if parent = NULL:            root <- node
    else if a.key < parent.key:  parent.left <- node
    else                         parent.right <- node
    return true
```

## Task 2: search (iterative)

```
FIND(code):
    cur <- root
    while cur != NULL and cur.key != code:
        add cur.key to the path
        if code < cur.key: cur <- cur.left
        else               cur <- cur.right
    if cur != NULL: add cur.key to the path
    return cur                                // NULL = not found
    // comparisons = number of codes in the path

MIN():  cur <- root;  while cur.left  != NULL: cur <- cur.left;   return cur
MAX():  cur <- root;  while cur.right != NULL: cur <- cur.right;  return cur
```

## Task 3: delete (cases D1, D2, D3)

```
REMOVE(code):
    parent <- NULL;  cur <- root
    while cur != NULL and cur.key != code:
        parent <- cur
        if code < cur.key: cur <- cur.left
        else               cur <- cur.right
    if cur = NULL: return false

    if cur has no children:                   // D1: leaf
        nothing to do, cur is removed below
    else if cur has only a left child:        // D2
        nothing to do, cur is removed below
    else if cur has only a right child:       // D2
        nothing to do, cur is removed below
    else:                                     // D3: two children
        succParent <- cur;  succ <- cur.right
        while succ.left != NULL:              // successor = leftmost node of the right subtree
            succParent <- succ;  succ <- succ.left
        copy the data of succ into cur        // keys, name, city, ... (not the child pointers)
        parent <- succParent;  cur <- succ    // now remove succ instead; it has no left child

    child <- cur.left if cur.left != NULL, else cur.right      // at most one child
    if parent = NULL:        root <- child
    else if parent.left = cur: parent.left <- child
    else                       parent.right <- child
    free cur
    return true
```

```
FIND-EXAMPLE(kind):             // used by the tests to pick one node of each delete case
    q <- the children of the root
    for each node n in q, in order (level order):
        if n matches kind (leaf / only left / only right / two children): return n.key
        append the children of n to q
    return none
```

## Task 4: traversals, validation, save and load

```
INORDER(n):   if n = NULL return;  INORDER(n.left);  visit n;  INORDER(n.right)    // sorted order
PREORDER(n):  if n = NULL return;  visit n;  PREORDER(n.left);  PREORDER(n.right)

LEVEL-ORDER():
    q <- [root]
    for i <- 0 while i < |q|:
        output q[i].key;  append q[i].left and q[i].right if they exist

VALIDATE(n, lo, hi):                          // start with VALIDATE(root, none, none)
    if n = NULL: return true
    if lo exists and n.key <= lo: return false
    if hi exists and n.key >= hi: return false
    return VALIDATE(n.left, lo, n.key) and VALIDATE(n.right, n.key, hi)

SAVE(file):  write the line "#preorder", then the PREORDER codes, one per line
LOAD-TREE(file):
    clear the tree
    for each code in the file, in order: INSERT(the stored record of that code)
    // inserting a preorder list in order gives back the same shape
```

`load FILE` looks at the first character of the file: `#` means a saved preorder
list, anything else is airport data.

## Height, average depth, top levels

```
HEIGHT(n):    if n = NULL return -1;  return 1 + max(HEIGHT(n.left), HEIGHT(n.right))
SUM-DEPTHS(n, d):  if n = NULL return 0;  return d + SUM-DEPTHS(n.left, d+1) + SUM-DEPTHS(n.right, d+1)
AVERAGE-DEPTH():   SUM-DEPTHS(root, 0) / number of nodes          // the root has depth 0

PRINT-TOP-LEVELS(k):
    cur <- [root]
    repeat k times:
        print every node in cur (a missing node prints "-")
        next <- both children of every node in cur (NULL for a missing node's children)
        cur <- next
```

## Task 5: range query

```
RANGE(from, to):
    visit(n):
        if n = NULL: return
        count n as visited
        if from < n.key: visit(n.left)        // otherwise the left subtree is all < from
        if from <= n.key <= to: output n
        if n.key < to:   visit(n.right)       // otherwise the right subtree is all > to
    visit(root)
    return the number of visited nodes
```

## Task 6: balanced build and the experiment

```
BUILD-BALANCED(a, lo, hi):                    // a is sorted with no duplicates
    if lo > hi: return NULL
    mid <- (lo + hi) / 2
    node <- new Airport copied from a[mid]
    node.left  <- BUILD-BALANCED(a, lo, mid - 1)
    node.right <- BUILD-BALANCED(a, mid + 1, hi)
    return node                               // height = floor(log2 n)

REBALANCE():
    a <- INORDER() copied into an array
    free the old tree
    root <- BUILD-BALANCED(a, 0, n - 1)

EXPERIMENT():
    sorted   <- records sorted by key, duplicates removed
    shuffled <- records in a fixed random order
    queries  <- 10,000 random codes chosen from sorted
    tree 1 <- INSERT each record in file order
    tree 2 <- INSERT each record of sorted
    tree 3 <- BUILD-BALANCED(sorted)
    tree 4 <- INSERT each record of shuffled (bonus)
    for each tree:
        start timer;  FIND each query;  stop timer
        report HEIGHT, AVERAGE-DEPTH and the time
```
