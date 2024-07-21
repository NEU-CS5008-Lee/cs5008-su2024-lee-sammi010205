// name: Fang Huang
// email: huang.fang@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    if (n == 0) return 1;
    if (n == 1) return 2;
    if (n == 2) return 7;

    d[0] = 1;
    d[1] = 2;
    for (int i = 2; i <= n; i++) {
	    d[i] = 2*d[i-1] + 3*d[i-2];
	    for (int j = i-3; j >=0; j--) {
		    d[i] += 2*d[j];
	    }
    }
    return d[n];
    



}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
