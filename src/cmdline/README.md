# Command line driver
The command line driver will run the Davenport algorithm using a text file
as input.

The format for the input text file is:
```
if <= pref if |
      pref
pref <= label OP prefs NL
prefs <= label OP prefs |
         label
label <= <% any characters other than '>' '=' %>
OP : [ '>' | '=' ]
NL : "\n"
```

Here is an example input:
```
9>2>3>8>5>7=1=4=0=6
4>9>0>6>3>2>5>1>7>8
5>3>2>4>8=7>1>9>0>6
1>4>7=2>5>0>8>6>9>3
4>5>8>1>6>3>0>2>9>7
5>1>0>8>2>4>7>3>9=6
```

Each line expresses one preference.
A preference consists of option labels in preference order, separated by
'>'. An '=' may be substituted for '>', which indicates that the labels
joined by the '=' are equally preferred.

Here is a sample run:
```
src/cmdline[i19]$ echo "aoeunth>rcgoeu=tnhj>nthaoeu" | ./davenport
This is Davenport 0.1.0.
Label aoeunth has index 0
Label rcgoeu has index 1
Label tnhj has index 2
Label nthaoeu has index 3
Preference graph with 4 candidates is
 :/:   0   1   2   3
  0:   0   1   1   1
  1:   0   0   0   1
  2:   0   0   0   1
  3:   0   0   0   0
Majority graph:
 :/:   0   1   2   3
  0:   0   1   1   1
  1:   0   0   0   1
  2:   0   0   0   1
  3:   0   0   0   0
Solution with 0 disagreements:
  1   2   2   4
1 viable solutions investigated.
Aggregate partial order solution:
  1   2   2   4
At rank    1: aoeunth
At rank    2: rcgoeu = tnhj
At rank    3:
At rank    4: nthaoeu
src/cmdline[i19]$ 
```
