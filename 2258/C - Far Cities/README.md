<h2><a href="https://codeforces.com/contest/2258/problem/C" target="_blank" rel="noopener noreferrer">2258C — Far Cities</a></h2>

| | |
|---|---|
| **Difficulty** | 1600 |
| **Language** | C++23 (GCC 14-64, msys2) |
| **Verdict** | ✅ Accepted |
| **Problem Link** | [Codeforces 2258C](https://codeforces.com/contest/2258/problem/C) |

## Topics
`interactive` `trees` `two pointers`

---

## Problem Statement

<div class="header"><div class="title">C. Far Cities</div><div class="time-limit"><div class="property-title">time limit per test</div>2 seconds</div><div class="memory-limit"><div class="property-title">memory limit per test</div>256 megabytes</div><div class="input-file input-standard"><div class="property-title">input</div>standard input</div><div class="output-file output-standard"><div class="property-title">output</div>standard output</div></div><div><p>   </p><p><span class="tex-font-style-it">This is an interactive problem.</span></p><p><span class="tex-font-style-it">Seferoglu lives in a small coastal city called Samsun, a city where not many people study competitive programming. Whenever an event takes place, he has to travel to far cities where he can meet his friends. Since he is tired of calculating the length of his journey exactly each time, he is just curious about the maximum distance he will ever have to travel between two cities in the worst case scenario. Your task is to help him find this distance while keeping the amount of web searches he has to make small.</span> </p><p>There is a hidden tree$$$^{\text{∗}}$$$ with $$$n$$$ vertices. You can make queries. In one query, you choose two vertices $$$1 \le u, v \le n$$$ and an integer $$$0 \le d \le n$$$; the grader responds with $$$1$$$ if $$$\operatorname{dist}(u, v) \ge d$$$ and $$$0$$$ otherwise. Here, $$$\operatorname{dist}(u,v)$$$ denotes the distance$$$^{\text{†}}$$$ between vertices $$$u$$$ and $$$v$$$ in the tree.</p><p>Your task is to determine the diameter's length$$$^{\text{‡}}$$$ of the tree and any pair of nodes that are this distance apart. You may ask at most $$$3 \cdot n$$$ queries. </p><div class="statement-footnote"><p>$$$^{\text{∗}}$$$A tree is a connected graph without cycles.</p><p>$$$^{\text{†}}$$$The distance between two nodes in a tree is the number of edges in the unique simple path between these nodes.</p><p>$$$^{\text{‡}}$$$The diameter's length is the largest distance between two vertices.</p></div></div><div class="input-specification"><div class="section-title">Input</div><p>Each test contains multiple test cases. The first line contains the number of test cases $$$t$$$ ($$$1 \le t \le 500$$$). The description of the test cases follows.</p><p>The first line of each test case contains $$$n$$$ ($$$2 \le n \le 1000$$$), denoting the number of vertices in the tree. </p><p>It is guaranteed that the sum of $$$n$$$ over all test cases does not exceed $$$1000$$$.</p></div><div><div class="section-title">Interaction</div><p>To make a query, first pick $$$u$$$, $$$v$$$ and $$$d$$$ ($$$1 \le u, v \le n$$$, $$$0 \le d \le n$$$), a pair of nodes and a constant to check the distance between them against, and output the following line (without quotes): </p><ul> <li> <span class="tex-font-style-tt">"? u v d"</span> </li></ul><p>Afterwards, you should read one single integer ($$$1$$$ or $$$0$$$), whether $$$d$$$ was less than or equal to $$$\text{dist}(u, v)$$$ or not.</p><p>Note you may ask at most $$$3 \cdot n$$$ such queries.</p><p>Next, if your program has found an answer, it should print the following line (without quotes):</p><ul> <li> <span class="tex-font-style-tt">"! u v d"</span> </li></ul><p>For some candidate $$$u$$$ and $$$v$$$ nodes denoting the endpoints of a diameter ($$$1 \le u, v \le n$$$) and the length of the path between them ($$$0 \le d \le n-1$$$). If there are multiple answers, any one of them may be printed.</p><p>Note that this action is <span class="tex-font-style-bf">not</span> counted towards the maximum query limit.</p><p>The grader is <span class="tex-font-style-bf">non-adaptive</span>. This means that the graph is fixed at the beginning and will not change based on your interactions.</p><p>After printing each query do not forget to output the end of line and flush$$$^{\text{∗}}$$$ the output. Otherwise, you will get <span class="tex-font-style-tt">Idleness limit exceeded</span> verdict.</p><p>If, at any interaction step, you read $$$-1$$$ instead of valid data, your solution must exit immediately. This means that your solution will receive <span class="tex-font-style-tt">Wrong answer</span> because of an invalid query or any other mistake. Failing to exit can result in an arbitrary verdict because your solution will continue to read from a closed stream.</p><p><span class="tex-font-style-bf">Hacks</span></p><p>To hack, use the following format:</p><p>The first line contains the number of test cases $$$t$$$ ($$$1 \le t \le 500$$$). </p><p>The first line of each test case contains $$$n$$$ ($$$2 \le n \le 1000$$$), denoting the number of vertices in the tree. </p><p>The next $$$n-1$$$ lines of each test case contain two integers each $$$u_i, v_i$$$ ($$$1 \le u_i, v_i \le n$$$), denoting the edges of the tree. </p><div class="statement-footnote"><p>$$$^{\text{∗}}$$$To flush, use: </p><ul> <li> <span class="tex-font-style-tt">fflush(stdout)</span> or <span class="tex-font-style-tt">cout.flush()</span> in C++; </li><li> <span class="tex-font-style-tt">sys.stdout.flush()</span> in Python; </li><li> see the documentation for other languages. </li></ul></div></div><div class="sample-tests"><div class="section-title">Example</div><div class="sample-test"><div class="input"><div class="title">Input<div title="Copy" data-clipboard-target="#id009442232764737869" id="id0029289434615897636" class="input-output-copier">Copy</div></div><pre id="id009442232764737869">3

4

1

0

0

0

2

4

1

1

1

1

0

0

0

0</pre></div><div class="output"><div class="title">Output<div title="Copy" data-clipboard-target="#id004098325032085208" id="id0001132567553058883" class="input-output-copier">Copy</div></div><pre id="id004098325032085208">? 1 2 1

? 1 2 2

? 2 3 2

? 3 4 2

! 1 4 3

! 1 2 1

? 1 2 1

? 1 3 1

? 1 4 1

? 3 4 2

? 3 4 3

? 1 2 2

? 1 3 2

? 1 4 2

! 4 2 2</pre></div></div></div><div class="note"><div class="section-title">Note</div><p>The hidden graph in the first test case is $$$(1,2), (2,3), (3,4)$$$.</p><p>The hidden graph in the second test case is $$$(1,2)$$$.</p><p>The hidden graph in the third test case is $$$(1,2), (1,3), (1,4)$$$. </p><p>In the third test case, the answer <span class="tex-font-style-tt">"! 3 4 2"</span> is also correct.</p><center> <table class="tex-tabular bordertable"><tbody><tr><td class="tex-tabular-text-align-center tex-tabular-border-right"><img class="tex-graphics" src="https://espresso.codeforces.com/6772bf5c4f2448f399faa2bdf0108308ba232501.png" style="max-width: 100.0%;max-height: 100.0%;"></td><td class="tex-tabular-border-left tex-tabular-text-align-center tex-tabular-border-right"><img class="tex-graphics" src="https://espresso.codeforces.com/59792fc602936fe4f2f8d9cae0cb06b2906942c6.png" style="max-width: 100.0%;max-height: 100.0%;"></td><td class="tex-tabular-border-left tex-tabular-text-align-center"><img class="tex-graphics" src="https://espresso.codeforces.com/33f495ea7ebd9709bc0b58c357c3e2b57f92b169.png" style="max-width: 100.0%;max-height: 100.0%;"></td><td></td></tr><tr><td class="tex-tabular-text-align-center tex-tabular-border-right"><span class="tex-font-size-small">The tree of the first testcase</span></td><td class="tex-tabular-border-left tex-tabular-text-align-center tex-tabular-border-right"><span class="tex-font-size-small">The tree of the second testcase</span></td><td class="tex-tabular-border-left tex-tabular-text-align-center"><span class="tex-font-size-small">The tree of the third testcase</span></td></tr></tbody></table> </center></div>