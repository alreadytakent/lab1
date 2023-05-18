#include<iostream>
#include<chrono>

void find_pair_straightforward(int *numbers, int *pair, int N, int S){
    for (int i=0; i!=N; i++){
        for (int j=0; j!=N; j++){
            if (numbers[i] + numbers[j] == S){
                pair[0] = i;
                pair[1] = j;
            }
        }
    }
}

int main(){
    unsigned T = 100;
    int *numbers = new int[10000];
    for (int i=0; i!=10000; i++){
        numbers[i] = i;
    }
    int pair[2] = {-1, -1};
    for (int N=100; N!=10000; N+=100){
        std::cout<<N<<',';
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            find_pair_straightforward(numbers, pair, N, -1);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<time_span.count()<<'\n';
    }
    delete[] numbers;
    return 0;
}
