include <iostream>
include <string>
include <vector>
include <map>
include <algorithm>
using namespace std;

int a1[36005];
int a[36005];

int fun() {
    int n;
    double temp;
    int result=0;
    cin>>n;
    
    int i = 0;
    while (i < n) {
        cin>>a1[i];
        i++;
    }
    if (n < 3) return 0;
    
    sort(a1, a1+n);
    
    i = 1;
    a[0] = a1[0];
    int m = 1;
    while (i < n) {
        if (a1[i] != a[m]) {
            a[m] = a1[i];
            m++;
        }
        i++;
    }
    n = m;
    
    for (i = 0; i < n && a[i] < 18000; i++) {
        int num=0;
        temp = a[i] + 18000;
        for (int j = i+1; j < n; j++) {
            if (a[j] < temp) {
                num++;
            }
        }
        result+=num*(num-1)/2;
    }
    
    for (int j = i; j < n && a[j] == 18000; j++) {
        int num=0;
        temp = 36000;
        for (int k = j+1; k < n ; k++) {
            if (a[k] > temp) {
                num++;
            }
        }
        result += num*(num-1)/2;
    }
    
    for (; i < n && a[i] > 18000 ; i++) {
        int num=0;
        temp = a[i] - 18000 ;
        for (int j = i+1; j < n ; j++) {
            if (a[j] > temp) {
                num++;
            }
        }
        result += num*(num-1)/2;
    }
    return result;
}

int main() {
    cout<<fun()<<endl;
    return true;
}