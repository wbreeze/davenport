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
Numerical Recipes contains a [C++ implementation][kycpp]
of a stochastic approximation algorithm.

You can find another description
of the method and the algorithm on
[wind and water](https://wnw.wbreeze.com/2019/08/davenport.html).
The post following that one describes the motivation for
and development of this code base.

This implementation has no dependencies on any big libraries.
As such, it contains:
- a taylored implementation of an algorithm for maximum flow through a network.
  The algorithm used is highest label preflow push.
- a quicksort implementation
- an implementation of Tarjan's algorithm for finding components and
  their topological sort.

## Installing

This library is installed from source. You will need to already have
installed:
- `git`,
- the GNU autoconf tools,
  - On MacOS with Homebrew, `brew install autoconf automake libtool`
- a C compiler.
- Currently you need to have installed [Cutter](
  https://github.com/clear-code/cutter/) as well.
  - (There is [an issue](https://github.com/wbreeze/davenport/issues/16)
    to remove that requirement.)
  - On MacOS with Homebrew, `brew install --cask cutter`

Given those:
- Check-out the source, `git clone https://github.com/wbreeze/davenport.git`
- Change to the resulting `davenport` directory, `cd davenport`
- Run the `bootstrap` script
- Change to the `src` directory
- Run the installation script as root, `make install`

On some systems, including Debian and Ubuntu Linux, you must now

- Refresh the shared library loader as root, `ldconfig /usr/local/lib`

### I don't have root access

One option is to have someone who does install it for you.
Another (untested) option, assuming most of the basic requirements,
such as `git`, `autoconf`, and a C compiler are installed on the system,
is to install it locally and use the `LD_LIBRARY_PATH` environment
variable to lead the linker to the library:

```
> mkdir -p ${HOME}/local
> export LOCAL_LIBS=${HOME}/local
> autoreconf --install
> ./configure --prefix=$LOCAL_LIBS
> make install
> export LD_LIBRARY_PATH=${LOCAL_LIBS}/lib/:${LD_LIBRARY_PATH}
```
-
Consider putting the last export into your shell startup.
You will probably have to do something similar first, to install the
Cutter library. It will be a pain. There's a question and answer
about installing libraries locally
[at SuperUser](https://superuser.com/q/324613).

Also see the [INSTALL](INSTALL) file generted from GNU Autoconf.

### Command line driver
The installation includes a command line program, "davenport"
whose source is in the `cmdline` directory.
After compiling the library using `make` in the `src` directory you can
compile the command line program using `make` in the `cmdline` directory.

Further information may be found in the
[README](cmdline/README.md) for that program.
Find the source at [cmdline](cmdline).

## Building

This follows the GNU AutoConf convention. With the exception of the
`make` command, the process is the same as Installing (above).
For the `make` command, just type "make" rather than "make install".

To run tests:
- `cd test` (optional)
- `make check`

### Development

When developing, you can use the `bootstrap` script together with the
generated `configure` script.

- `./bootstrap`
- `./configure`

To see the cutter output from the tests, either:
- `make check`
- `cat test/run_test.sh.log`
or
- `test/run_test.sh`

## Performance and Memory

In the following,
- "n" is the number of alternatives that are ranked
- "n_e" is n^2 / 2, a bound on the number of pair-wise orderings
- "n_c" is the maximal number of alternatives found to be within multiple
  alternative components of the majority graph. Its worst case value is n^2.

This implementation allocates storage as follows:
- an n^2 element array of int values to represent the majority graph
  (which, in reality is passed-in by the caller)
- an n^2 element array of unsigned char values to represent the solution
  graph
- an n element array of int to represent components of the majority graph
- an n element array to represent a topological sort of the solution graph
- an n element array to represent the most recent solution
- an n_e element array of int to represent edges to explore in the
  majority graph
- an n_e element array of int to represent order of edge addition to the
  solution graph
- three n element arrays of int for book-keeping in component identification
- a handful of integers on the stack for each of up to {n_c}^2 recursions

At each iteration it (currently) allocates and frees 2 * {n_c}^2 + n_c * 4
integers. This could be changed to another 2 * n^2 allocation for the
duration of the run.

Broadly, the algorithm uses O(n^2) integers storage. The constant around n^2 is
about five.

The implementation uses a number of processes that are n^2 to initialize
edge arrays, maintain transitive closure and the like. None of these contain
anything particularly compute intensive.

The Tarjan component finding is linear in n.
The preflow_push algorithm is worst case cubic in n_c `O({n_c}^3)`.
Both are performed at each iteration.

The algorithm will in best case make one iteration and in worst case make
${n^2}!$ iterations. It is not very hard to make a worst case example; however,
the worst case is rare in practice. The improved bounds article ([4][bounds])
and the aerobatic flight ranking article ([5][ranking]) both demonstrate
extensive application experience with tenable runtimes.

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
- [5][ranking] Andrew Davenport and Douglas Lovell. Ranking Pilots in
Aerobatic Flight Competitions, IBM Research Report RC23631, 2005.

[kemeny]:https://www.jstor.org/stable/20026529
[young]: https://doi.org/10.1137/0135023
[kym]: https://en.wikipedia.org/wiki/Kemeny%E2%80%93Young_method
[kycpp]: http://numerical.recipes/whp/ky/kemenyyoung.html
[davenport]: https://aaai.org/Library/AAAI/2004/aaai04-110.php
[bounds]: https://aaai.org/Library/AAAI/2006/aaai06-099.php
[travis]: https://travis-ci.org/wbreeze/davenport.svg?branch=master
[ranking]: https://domino.research.ibm.com/library/cyberdig.nsf/0/f0cef204f8d781628525702300545d8f
