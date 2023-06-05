# finding_twin_carmichael_nums

## Purpose

Finds all (up to a certain amount) pairs of non-prime Carmichael numbers that have a gap within a certain threshold.

Created for a friend's personal project.

## Usage

Adjust SEARCH_N, SEARCH_GAP, and PRIMES_MEMO_SIZE in `carmichael_twin_search.c`

## Example
where SEARCH_N = 50000000, SEARCH_GAP = 1000, PRIMES_MEMO_SIZE = 8388608

Output:

```
Searching for gap of 1000 or less

561 and 1105 with gap = 544
1105 and 1729 with gap = 624
1729 and 2465 with gap = 736
2465 and 2821 with gap = 356
8719309 and 8719921 with gap = 612

Done searching through n = 50000000
```
