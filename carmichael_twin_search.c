
/*

File: carmichael_twin_search.c
Author: fjordimm
Created: 6-5-2023
Last Updated: 6-5-2023

Credits:
 - Uses almost direct copies of code from https://codegolf.stackexchange.com/a/974 for:
    - is_prime()
    - prime()
    - is_carmichael()

Machine used by author:
	Windows 11 (OS Build 22621.1702)
Compiled using:
	gcc.exe (tdm64-1) 10.3.0

*/

///////

// SEARCH_N: The number to stop searching at
//  - Must be under the maximum value of the 'carmich_t' type
//  - The number of prime numbers less than or equal to SEARCH_N must be smaller than PRIMES_MEMO_SIZE
#define SEARCH_N 50000000

// SEARCH_DIFF: The maximum gap of two Carmichael numbers for them to be printed out
#define SEARCH_GAP 1000

// PRIMES_MEMO_SIZE: The size of the prime number memoization array
//  - Will break for large numbers depending on the machine (it is the length for a static array of 'carmich_t's)
#define PRIMES_MEMO_SIZE 8388608 // arbitrary, but currently set to 2^23

///////

#include <stdio.h>
#include <stdbool.h>

#define carmich_t unsigned long long int

bool is_prime(carmich_t v);
carmich_t prime(carmich_t i, carmich_t* i2);
bool is_carmichael(carmich_t n);

int main(void)
{
	carmich_t last_found = 0;

	printf("Searching for gap of %llu or less\n\n", SEARCH_GAP);

	for (carmich_t i = 1; i <= SEARCH_N; i++)
	{
		if (is_carmichael(i))
		{
			if ((last_found != 0) && (i - last_found <= SEARCH_GAP))
			{
				printf("%llu and %llu with gap = %llu\n", last_found, i, i - last_found);
			}
			
			last_found = i;
		}
	}

	printf("\nDone searching through n = %llu\n", SEARCH_N);

	return 0;
}

bool is_prime(carmich_t v)
{
	bool isprm = true;
	
	for (carmich_t i = 3, i2 = 9; i2 < v; i++, i2 += i + i + 1)
	{
		if (v % i == 0)
		{
			isprm = false;
			break;
		}
	}

	return isprm;
}

carmich_t prime(carmich_t i, carmich_t* i2)
{
	static carmich_t primes_memo[PRIMES_MEMO_SIZE] = {2, 3, 5};
	static carmich_t primes_sqrd_memo[PRIMES_MEMO_SIZE] = {4, 9, 25};
	static size_t primes_memo_cnt = 3;

	while (i >= primes_memo_cnt)
	{
		carmich_t v = primes_memo[primes_memo_cnt - 1];

		do
		{ v += 2; }
		while (!is_prime(v));

		primes_memo[primes_memo_cnt] = v;
		primes_sqrd_memo[primes_memo_cnt] = v * v;
		primes_memo_cnt++;
	}

	*i2 = primes_sqrd_memo[i];
	return primes_memo[i];
}

bool is_carmichael(carmich_t n)
{
	if (n < 2)
	{ return false; }

	carmich_t k = n;
	n--;
	carmich_t i2 = 4;

	for (carmich_t i = 1, p = 2; i2 <= k; p = prime(i++, &i2))
	{
		if (k % p == 0)
		{
			k /= p;

			if  ((k % p == 0) || (n % (p - 1) != 0))
			{ return false; }

			i = 0;
		}
	}

	k--;
	return (k != n) && (n % k == 0);
}
