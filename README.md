This is an implementation of Davenport's algorithm for computing Kemeny rankings.
The algorithm aggregates partial rankings from multiple sources into a partial
ranking that is proven to be the best estimator of the true preference order.

Find Davenport's algorithm described in
[A Computational Study of the Kemeny Rule for Preference Aggregation]()
We use the improved lower bounds developed by Conitzer and Davenport in
[Improved Bounds for Computing Kemeny Rankings]()

This implementation has no dependencies on any big libraries.
As such, it contains a taylored
implementation of an algorithm for maximum flow through a network.
The algorithm used is highest label preflow push.

