# The algorithm

This is a sketch of Davenport's algorithm, in some detail,
based upon the description in the paper [(1)][davenport].
Some definitions follow.

- Create majority graph M.
- Compute components C of M and topological sort T.
- Produce a solution graph S among components C as described in
  step 2 of Algorithm 1.
- Enumerate edges E of majority graph M not yet in the solution S.
   These will all be from some component C of size 3 or more.
- Order E according to decreasing majority (greedy heuristic)
- ** (S, M, C, E, T, d=0)
- If E is not empty
    - Find lower bound is d plus sum of lower bounds from components C of
       size 3 or more.
    - If lower bound is equal or lesser than best found (bound)
        - For each edge e of E, in order (branch)
            - S' is copy of S, M' copy of M, E' copy of E, d' = 0
             (This can be done with minimum additional memory by tracking
               changes to S, M, and E; then backing-out the changes after the
               recursion.)
            - Add e to S' and compute transitive closure of S'.
            - Remove any disagreement edges from M' and E' (as a result of
               the closure) and add their majority weight to d'.
            - Compute components C' of M' and topological sort T.
              (We believe that, at this point, S' is the same as would be
              computed from C' by step 2 of Algorithm 1; so, in effect, we have
              now applied Algorithm 1 as a propogation step.)
            - Recurse at ** with (S', M', C', E', T, d + d')
- Otherwise, we have a complete partial order in T
    - The total, d sums majority disagreements. As a check, we can compute the
       Kemeny distance of T, using the preference graph, and track that
       distance as well.
    - If d is better than best found (implies same for Kemeny distance)
        - Discard orderings found so far
        - Update best found
    - If d is equal to best found
        - Add (partial) ordering T to solution set. (Items without a majority
          preference among them form partial ordered, "tied" components.)

## Definitions

- Each alterative is represented by a node, `a_i`
- A "majority graph" contains directed edges `e_i,j` weighted with
  the number of preferences for `a_i` over `a_j` minus the number of
  preferences for `a_j` over `a_i`, when that number is positive.
  (There are no edges where the preference difference is zero
  or negative.) Each pair of nodes `a_i` and `a_j` (`i <> j`)
  has at most one edge in the majority graph.
- A "solution graph" contains an unweighted, directed edge `e_i,j` indicating
  that `a_i` is preferred to `a_j` in the solution. Each pair of nodes
  `a_i` and `a_j` (`i <> j`) has at most one edge in the solution graph.
  The solution graph is kept transitive.
- A "component" is a list of nodes for which there is a path, along directed
  edges, from any one of the nodes in the list to any other in the list,
  and then back to themselves.  A maximal component contains all nodes
  for which that property holds.  There can be multiple maximal components
  in a graph.  The smallest component size is one (a node that has no paths
  leading back to itself).
- A "transitive closure" is a graph with the property that wherever there is
  an edge from `a_i` to `a_j` and an edge from `a_j` to `a_k` (`i <> j <> k`)
  there is also an edge from `a_i` to `a_k`.
- A "topological sort" places the maximal components of a graph in sequence
  such that all edges leading out of each component lead to components later
  in the sequence.

[davenport]: https://aaai.org/Library/AAAI/2004/aaai04-110.php
