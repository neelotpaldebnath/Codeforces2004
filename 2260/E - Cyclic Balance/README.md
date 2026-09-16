<h2><a href="https://codeforces.com/contest/2260/problem/E" target="_blank" rel="noopener noreferrer">2260E — Cyclic Balance</a></h2>

| | |
|---|---|
| **Difficulty** | Unrated |
| **Language** | PyPy 3-64 |
| **Verdict** | ✅ Accepted |
| **Problem Link** | [Codeforces 2260E](https://codeforces.com/contest/2260/problem/E) |

## Topics
`binary search` `constructive algorithms` `dp` `math`

---

## Problem Statement

<div class="header"><div class="title">E. Cyclic Balance</div><div class="time-limit"><div class="property-title">time limit per test</div>2 seconds</div><div class="memory-limit"><div class="property-title">memory limit per test</div>512 megabytes</div><div class="input-file input-standard"><div class="property-title">input</div>standard input</div><div class="output-file output-standard"><div class="property-title">output</div>standard output</div></div><div><p>Consider a string $$$t=t_1t_2\ldots t_m$$$ consisting of the characters <span class="tex-font-style-tt">0</span> and <span class="tex-font-style-tt">1</span>. We call the pairs of adjacent characters of the string $$$t$$$ the pairs $$$t_1t_2, t_2t_3, \ldots, t_{m-1}t_m$$$, as well as the pair $$$t_mt_1$$$. The last pair connects the end of the string with its beginning, so exactly $$$m$$$ pairs are considered in total. If the string consists of only one character, the only pair that is considered is $$$t_1 t_1$$$.</p><p>We call a string $$$t$$$ <span class="tex-font-style-underline">cyclically balanced</span> if, among its pairs of adjacent characters, the numbers of pairs <span class="tex-font-style-tt">00</span>, <span class="tex-font-style-tt">01</span>, <span class="tex-font-style-tt">10</span>, and <span class="tex-font-style-tt">11</span> are equal.</p><p>The cost of a binary string is the minimum number of characters that need to be inserted into it so that it becomes cyclically balanced. Characters may be inserted in any positions, including before the first and after the last character of the string. It is not allowed to delete or replace the original characters.</p><p>You are given a binary string $$$s$$$ and $$$q$$$ queries. In each query, indices $$$l$$$ and $$$r$$$ are given. Find the cost of the substring $$$s_l s_{l+1}\ldots s_r$$$.</p></div><div class="input-specification"><div class="section-title">Input</div><p>The first line contains two integers $$$n$$$ and $$$q$$$ ($$$1 \le n, q \le 3 \cdot 10^5$$$) — the length of the string and the number of queries.</p><p>The second line contains $$$s$$$ — a sequence of length $$$n$$$ consisting of the characters <span class="tex-font-style-tt">0</span> and/or <span class="tex-font-style-tt">1</span>.</p><p>Then follow $$$q$$$ lines; the $$$i$$$-th of them contains two integers $$$l_i$$$ and $$$r_i$$$ ($$$1 \le l_i \le r_i \le n$$$) — the boundaries of the substring for the corresponding query.</p></div><div class="output-specification"><div class="section-title">Output</div><p>Print $$$q$$$ integers: the $$$i$$$-th integer should be equal to the cost of the substring from the $$$i$$$-th query.</p></div><div class="sample-tests"><div class="section-title">Example</div><div class="sample-test"><div class="input"><div class="title">Input<div title="Copy" data-clipboard-target="#id0023983067781718514" id="id007624737967013941" class="input-output-copier">Copy</div></div><pre id="id0023983067781718514"><div class="test-example-line test-example-line-even test-example-line-0">11 7</div><div class="test-example-line test-example-line-even test-example-line-0">00111100000</div><div class="test-example-line test-example-line-even test-example-line-0">1 8</div><div class="test-example-line test-example-line-even test-example-line-0">1 1</div><div class="test-example-line test-example-line-even test-example-line-0">1 2</div><div class="test-example-line test-example-line-even test-example-line-0">1 4</div><div class="test-example-line test-example-line-even test-example-line-0">3 6</div><div class="test-example-line test-example-line-even test-example-line-0">2 7</div><div class="test-example-line test-example-line-even test-example-line-0">7 11</div></pre></div><div class="output"><div class="title">Output<div title="Copy" data-clipboard-target="#id009717521780959879" id="id0048488382672423314" class="input-output-copier">Copy</div></div><pre id="id009717521780959879">4
3
2
0
4
2
7
</pre></div></div></div>