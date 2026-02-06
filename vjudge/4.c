#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
	ll yes;
	ll no;
	ll diff;
} Person;

int compare(const void *a, const void *b) {
	Person *p1 = (Person *)a;
	Person *p2 = (Person *)b;
	if (p1->diff > p2->diff) return -1;
	if (p1->diff < p2->diff) return 1;
	return 0;
}

int main(void) {
	int t;
	scanf("%d", &t);
	while (t--) {
		ll n, m;
		scanf("%lld %lld", &n, &m);
		Person *persons = (Person *)malloc(n * sizeof(Person));
		ll total_yes = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &persons[i].yes, &persons[i].no);
			persons[i].diff = persons[i].no - persons[i].yes;
			total_yes += persons[i].yes;
		}
		// 按diff降序排序
		qsort(persons, n, sizeof(Person), compare);
		
		// 计算前缀diff和
		ll *diff_sum = (ll *)malloc((n + 1) * sizeof(ll));
		diff_sum[0] = 0;
		for (int i = 0; i < n; i++) {
			diff_sum[i + 1] = diff_sum[i] + persons[i].diff;
		}
		
		ll ans = 0;
		// 枚举y
		for (ll y = 0; y <= n; y++) {
			if (n - y == 1) continue; // 有邻居的人数为1，无效
			if (y == 0) {
				if (m >= n) {
					ll happiness = total_yes;
					if (happiness > ans) ans = happiness;
				}
			} else if (y == n) {
				if (m >= 2 * n - 1) {
					ll happiness = total_yes + diff_sum[n]; // 即sum(no)
					if (happiness > ans) ans = happiness;
				}
			} else {
				// 1 <= y <= n-1 且 n-y >= 2
				if (n - y >= 2) {
					if (m >= n + y) {
						ll happiness = total_yes + diff_sum[y];
						if (happiness > ans) ans = happiness;
					}
				}
			}
		}
		printf("%lld\n", ans);
		free(diff_sum);
		free(persons);
	}
	return 0;
}
