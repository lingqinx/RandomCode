#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int a[100000];
int a1[100000];
int un_sum[100000];
int sum[100000];

int * fun() {
    int n;
    cin>>n;
    if (n == 0) return NULL;
    
    int i = 0;
    map<int, int> m;
    while (i < n) {
        cin>>a[i];
        a1[i] = a[i];
        m[a[i]] = 0;
        i++;
    }
    sort(a,a+n);
    un_sum[0] = 0;
    m[a[0]] = 0;
    
    for (i = 1; i < n; i ++) {
        if (a[i-1] < a[i]) un_sum[i] = a[i-1] + un_sum[i-1];
        m[a[i]] = un_sum[i];
    }
    for (int j = 0; j < n; j ++) {
        sum[j] = m[a1[j]];
        cout<<sum[j]<<endl;
    }
    
    return sum;
}

int main() {
    fun();
    return true;
}