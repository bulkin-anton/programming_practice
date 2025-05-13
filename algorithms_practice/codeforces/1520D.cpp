#include <iostream>
#include <vector>

using namespace std;
int
main(void){
    int t, cnt;
    cin >> t;
    for (int i = 0; i < t; i++){
        int n;
        cin >> n;
        vector <int> a(n);
        cnt = 0;
        for (int j = 0; j < n; j++){
            cin >> a[j];
        }
        for (int j = 0; j < (n - 1); j++){
            for (int k = j + 1; k < n; k++){
                if ((a[k] - a[j]) == (k - j)){
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
