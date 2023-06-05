
/*

Modified from:
https://codegolf.stackexchange.com/a/974

*/

#include <stdio.h>
#include <stdbool.h>

#define intl unsigned long long int

#define PRIMES_MEMO_SIZE 10000

/*
Requirements for SEARCH_N:
 - must be under the maximum value of intl
 - the number of prime numbers up to SEARCH_N must be less than PRIMES_MEMO_SIZE
*/
#define SEARCH_N 100000000

#define SEARCH_DIFF 1000

bool is_prime(intl v);
intl prime(intl i, intl* i2);
bool is_carmichael(intl n);

int main(void)
{
	for (intl i = 1; i < 10000; i++)
	{
		if (is_carmichael(i))
		{
			printf("%llu\n", i);
		}
	}

/*
	intl last_found = 0;

	printf("Searching for difference of %llu or less\n\n", SEARCH_DIFF);

	for (intl i = 1; i <= SEARCH_N; i++)
	{
		if (is_carmichael(i))
		{
			if (i - last_found <= SEARCH_DIFF)
			{
				printf("%llu and %llu with difference = %llu\n", last_found, i, i - last_found);
				last_found = i;
			}
		}
	}

	printf("\nDone searching through n = %llu\n", SEARCH_N);
*/
	return 0;
}

bool is_prime(intl v)
{
	bool isprm = true;
	
	for (intl i = 3, i2 = 9; i2 < v; i++, i2 += i + i + 1)
	{
		if (v % i == 0)
		{
			isprm = false;
			break;
		}
	}

	return isprm;
}

intl prime(intl i, intl* i2)
{
	static intl primes_memo[PRIMES_MEMO_SIZE] = {2, 3, 5};
	static intl primes_sqrd_memo[PRIMES_MEMO_SIZE] = {4, 9, 25};
	static size_t primes_memo_cnt = 3;

	while (i >= primes_memo_cnt)
	{
		intl v = primes_memo[primes_memo_cnt - 1];

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

bool is_carmichael(intl n)
{
	if (n < 2)
	{ return false; }

	intl k = n;
	n--;
	intl i2 = 4;

	for (intl i = 1, p = 2; i2 <= k; p = prime(i++, &i2))
	{
		if (k % p == 0)
		{
			k /= p;

			if  ((k % p == 0) || (n % (p - 1) != 0))
			{ return false; }

			i = 0;
		}
	}

	return (--k != n) && (n % k == 0);
}
