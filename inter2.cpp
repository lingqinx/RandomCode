include <iostream>
include <string>
include <vector>
include <map>

using namespace std;

int a[36005];

int fun() {
    int n;
    double temp;
    int result=0;
    cin>>n;
    
    int i = 0;
    map<int, int> m;
    while (i < n) {
        cin>>a[i];
        i++;
    }
    if (n < 3) return 0;
    
    sort(a, a+n);
    
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
    for (; i < n && a[i] >18000 ; i++) {
        int num=0;
        temp = a[i] - 18000 ;

        for (int j = i+1; j < n ; j++) {
            if (a[j] >temp) {
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