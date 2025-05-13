#include <iostream>
using namespace std;

enum {SIZE = 512};

class N{
    public:
        void append_el(int num);
        void sort();
        int get_length() const;
        int get_el(int n) const;
        N(int n);
        ~N();
    private:
        int len = SIZE, cnt = 0;
        int *arr;
};

N::N(int n){
    arr = new int[n];
}

N::~N(){
    delete []arr;
}

int
N::get_el(int n) const{
    return arr[n];
}

void N::append_el(int num){
    int *buf;
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

void N::sort(){
    int el;
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if (arr[i] < arr[j]){
                el = arr[j];
                arr[j] = arr[i];
                arr[i] = el;
            }
        }
    }
}

int N::get_length(void) const{
    return cnt;
}

int
main(void){
    N x(SIZE);
    int num;
    while (cin >> num){
        x.append_el(num);
    }
    x.sort();
    int cnt = x.get_length();
    for (int i = 0; i < cnt; i++){
        cout << x.get_el(i) << endl;
    }
    return 0;
}
