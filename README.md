# Algorithms and Data Structures

Assignments for academic course on designing algorithms and data structures using C++ STL.

Long task name is a hyperlink to problem description in Polish.

## Bigger tasks

### mar/ ([Mario](mar/mar.pdf))

Shortest route problem on graph with edges of only two possible lengths. Thus implemented Dijkstra's algorithm on two regular queues giving the complexity of ```O(|E| + 2|V|)``` as opposed to regular ```O(|E| + |V|log|V|)``` Dijkstra's implementation using ```std::priority_queue``` (Fibonacci's heap).

### hak/ ([Hakier](hak/hak.pdf))

For a list of initial ranges of natural numbers, dynamically respond to a queries of types: for range ```r_query``` find and remove from initial list a range ```r_init``` so that:

 - ```r_init``` is a subset of ```r_query```
 - ```r_query``` is a subset of ```r_init```
 - ```r_query ∩ r_init``` is empty
 - ```r_query ∩ r_init``` is not empty

Implemented using ```std::set``` table for keeping info of all available ranges and  two **range trees** to query for ranges ending respectively earliest and furthest.

### par/ ([Park Bitowy - *Bit Park*](par/par.pdf))  

Query the **binary tree**: find id of a node that is exactly of ```d``` distance from source node ```n```. Return -1 if there is no such node.

In order to get best possible complexity implemented among:
 - table of logarithmic shortcuts (for each note a link to the ancestor of a distance 1, 2, 4, ...), which made possible to implement function finding [LCA](https://en.wikipedia.org/wiki/Lowest_common_ancestor) in logarithmic time
 - finding furthest node via finding tree diameter (the longest path in tree) with BTS algorithm.

Which finally resulted in ```O(log n)``` queries of ```O(n)``` pre-processing, with ```n``` being number of tree nodes.

## Smaller tasks

### baz/ ([Bazarek - *Lil Bazaar*](baz/baz.pdf))  

Fun little exercise on **suffix sums** with a twist: finding maximum odd sum of exactly ```n``` elements in a list.

### mat/ ([Matryca - *Template*](mat/mat.pdf))

Sounding at first like complicated substring matching problem, is easily trivialised to single loop.

### sor/ ([Sortowanie Komórkowe - *Cellular Sorting*](sor/sor.pdf))

Un-sort list from a given algorithm. The algorithmic part turned out to be way more complicated than I expected and required using short but non-intuitive **dynamic programming** algorithm.

### mec/ ([Mecze - *Games*](mec/mec.pdf))

A haiku: (on STL and its inability to directly compare two bitsets)

```
  there's error: no match
  for operator<
  should have chosen Boost
```

### kin/ ([k-inwersje - *k-inversions*](kin/kin.pdf))
```
  Find a number of k-inversions modulo 10^9 for a given n-permutation
  k \in [2, 10]
  n \in [1, 20 000]
```

Built a table of **range trees** filled consecutively using dynamic programming algorithm. Again a short, but non-intuitive algorithm.

### mal/ ([Malowanie autostrady - *Painting the highway*](mal/mal.pdf))

Sum and subtraction operations on ranges of natural numbers. Dynamically querying for size of set of all numbers within those ranges. Like so:
```
  [1, 3] + [4, 7] = [1, 7]            // size: 7
  [1, 7] - [2, 3] = [1, 1] + [4, 7]   // size: 5
```
Implemented using ```std::set``` of ```std::pair```s.

### prj/ ([Projekty - *Projects*](prj/prj.pdf))

### kap/ ([Kapitan - *The Captain*](kap/kap.pdf))

The two above tasks were solved through some variants of Dijkstra's algorithm.

### inw/ ([Graf Inwersji - *Inversions*](inw/inw.pdf))

Terrifically tangled task turns to two throughout traversals.
