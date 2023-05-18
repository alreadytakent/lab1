#include<iostream>
#include<chrono>
#include<random>

void swap(int *numbers, int i, int j){
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
}

int strategyC(int *numbers, int *counters, int N, int a){
    if (numbers[0] == a){
        counters[0]++;
        return 0;
    }
    for (int i=0; i!=N; i++){
        if (numbers[i] == a){
            counters[i]++;
            if (counters[i] > counters[i-1]){
                swap(numbers, i-1, i);
                swap(counters, i-1, i);
                return i-1;
            }
            return i;
        }
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
    unsigned T = 10000;
    for (int N=10000; N!=1000000; N+=10000){
        int *numbers = new int[N];
        int *counters = new int[N];
        for (int i=0; i!=N; i++){
            numbers[i] = i;
            counters[i] = 0;
        }
        unsigned *test_seq = new unsigned[T];
        get_test_seq(test_seq, N, T);
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            strategyC(numbers, counters, N, numbers[test_seq[i]]);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<N<<','<<time_span.count()<<'\n';
        delete[] numbers;
        delete[] counters;
        delete[] test_seq;
    }
    return 0;
}
