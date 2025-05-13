#include <iostream>
using namespace std;

int
main(void){
    int cnt = 0, num, len = 512, el;
    int *arr, *buf;
    arr = new int[len];
    while (cin >> num){
        cnt++;
        if (cnt == len){
            buf = new int[len];
            for (int i = 0; i < cnt; i++){
                buf[i] = arr[i];
            }
            delete []arr;
            len *= 2;
            arr = new int[len];
            for (int i = 0; i < cnt; i++){
                arr[i] = buf[i];
            }
            delete []buf;
        }
        arr[cnt - 1] = num;
    }
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if (arr[i] < arr[j]){
                el = arr[j];
                arr[j] = arr[i];
                arr[i] = el;
            }
        }
    }
    for (int i = 0; i < cnt; i++){
        cout << arr[i] << endl;
    }
    delete []arr;
    return 0;
}
