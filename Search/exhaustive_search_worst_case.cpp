#include<iostream>
#include<chrono>

int exhaustive_search(int *numbers, int N, int a){
    for (int i=0; i!=N; i++){
        if(numbers[i] == a) return i;
    }
    return -1;
}

int main(){
    unsigned T = 10000;
    int *numbers = new int[1000000];
    for (int i=0; i!=1000000; i++){
        numbers[i] = i;
    }
    for (int N=10000; N!=1000000; N+=10000){
        std::cout<<N<<',';
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            exhaustive_search(numbers, N, -1);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<time_span.count()<<'\n';
    }
    delete[] numbers;
    return 0;
}
