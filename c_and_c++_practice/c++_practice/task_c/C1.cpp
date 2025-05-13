#include <iostream>

class Array{
    public:
        Array(int n);
        int& iteam(int i);
        const int& iteam(int i) const;
        friend void arr_out(const Array& x);
        ~Array();
    private:
        int *arr, len;
};

Array::Array(int n){
    arr = new int[n];
    len = n;
}

Array::~Array(){
    delete []arr;
    len = 0;
}

int&
Array::iteam(int i){
    if ((i < 0) || (i >= len)){
        std::cout << "Out of bound" << std::endl;
        exit(0);
    } else{
        return arr[i];
    }
}

const int&
Array::iteam(int i) const{
    if ((i < 0) || (i >= len)){
        std::cout << "Out of bound" << std::endl;
        exit(0);
    } else{
        return arr[i];
    }
}

void
arr_out(const Array& x){
    for (int i = 0; i < x.len; i++){
        if ((i + 1) != x.len){
            std::cout << x.iteam(i) << ' ';
        } else{
            std::cout << x.iteam(i) << std::endl;
        }
    }
}

int
main(){
    Array nums(10);
    for (int i = 0; i < 10; i++){
        std::cin >> nums.iteam(i);
    }
    arr_out(nums);
    return 0;
}
