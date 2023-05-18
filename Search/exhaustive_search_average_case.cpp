#include<iostream>
#include<chrono>
#include<random>

int exhaustive_search(int *numbers, int N, int a){
    for (int i=0; i!=N; i++){
        if(numbers[i] == a) return i;
    }
    return -1;
}

unsigned log10(int N){
    unsigned ans = 0, accum = 1;
    while (N > accum){
        ans++;
        accum *= 10;
    }
    return ans;
}

void get_test_seq(unsigned *test_seq, int N, unsigned T){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, 9);
    unsigned n = log10(N);
    for (unsigned i=0; i!=T; i++){
        unsigned a = 0;
        for (unsigned j=0; j!=n; j++){
            a = a*10 + arr[dstr(rng)];
        }
        while (a > N){
            a = 0;
            for (unsigned j=0; j!=n; j++){
                a = a*10 + arr[dstr(rng)];
            }
        }
        test_seq[i] = a;
    }
}

int main(){
    unsigned T = 100000;
    int *numbers = new int[1000000];
    for (int i=0; i!=1000000; i++){
        numbers[i] = i;
    }
    for (int N=10000; N!=1000000; N+=10000){
        std::cout<<N<<',';
        unsigned *test_seq = new unsigned[T];
        get_test_seq(test_seq, N, T);
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            exhaustive_search(numbers, N, numbers[test_seq[i]]);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<time_span.count()<<'\n';
        delete[] test_seq;
    }
    delete[] numbers;
    return 0;
}
