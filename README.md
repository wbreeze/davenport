This is an implementation of Davenport's algorithm for computing
a preference order using the Kemeny rule [(1)][kemeny]
for preference aggregation.
The algorithm aggregates partial rankings from multiple sources into an
aggregate partial ranking that is proven in 1978 [(2)][young] to be:
- Condorcet: If a majority ranks A before B, A is before B in the aggregate.
- Consistent: If the aggregate places A before B in subsets of the
preferences, it places A before B in the full set of the preferences.
- Neutral: It gives equal weight to all preferences.

Find Davenport's algorithm described in
_A Computational Study of the Kemeny Rule for Preference
Aggregation_ [(3)][davenport].
We use the improved lower bounds developed by Conitzer and Davenport in
_Improved Bounds for Computing Kemeny Rankings_ [(4)][bounds].

A general description of the method (not the algorithm)
may be found on Wikipedia as "[Kemeny-Young method][kym]".
Numerical Recipes contains a [C++ implementation][kycpp].

This implementation has no dependencies on any big libraries.
As such, it contains a taylored
implementation of an algorithm for maximum flow through a network.
The algorithm used is highest label preflow push.

## Building

This follows the GNU AutoConf convention. From the root of the source tree
(e.g. ~/Davenport):
- `./configure`
- `make`

To run tests:
- `cd test` (optional)
- `make check`

## References
- [1][kemeny] John Kemeny. Mathematics without numbers.
_Daedalus_, Vol. 88, pages 571-591, 1959.
- [2][young] H. P. Young and A Levenglick.
A consistent extension of Condorcet's election principle.
_SIAM Journal on Applied Mathematics_, Vol. 35, No. 2, pages 285-300, 1978.
- [3][davenport] Andrew Davenport and Jayant Kalagnanam.
A computational study of the Kemeny rule for preference aggregation.
_Proceedings of the Nineteenth National Conference on Artificial Intelligence_,
AAAI, pages 697--702, 2004.
- [4][bounds] Vincent Conitzer, Andrew Davenport, and Jayant Kalagnanam.
Improved bounds for computing Kemeny rankings.
_Proceedings of the Twenty-first AAAI Conference on Artificial Intelligence_,
AAAI, pages 620--626, 2006.

[kemeny]:https://www.jstor.org/stable/20026529
[young]: https://doi.org/10.1137/0135023
[kym]: https://en.wikipedia.org/wiki/Kemeny%E2%80%93Young_method
[kycpp]: http://numerical.recipes/whp/ky/kemenyyoung.html
[davenport]: https://aaai.org/Library/AAAI/2004/aaai04-110.php
[bounds]: https://aaai.org/Library/AAAI/2006/aaai06-099.php
