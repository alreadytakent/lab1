#include<iostream>
#include<chrono>
#include<random>

void swap(int *numbers, int i, int j){
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
}

int strategyB(int *numbers, int N, int a){
    if (numbers[0] == a) return 0;
    for (int i=0; i!=N; i++){
        if (numbers[i] == a){
            swap(numbers, i-1, i);
            return i-1;
        }
    }
    return -1;
}

int f(int x){
    return 1 + x/1000;
}

unsigned log10(int N){
    unsigned ans = 0, accum = 1;
    while (N > accum){
        ans++;
        accum *= 10;
    }
    return ans;
}

int binary_search(int *numbers, int N, int a){
    int i_lower=0, i_upper=N-1, i_mid;
    while (i_upper != i_lower + 1){
        i_mid = (i_lower+i_upper)/2;
        if (numbers[i_mid] >= a) i_upper = i_mid;
        else i_lower = i_mid;
    }
    return i_lower;
}

void get_test_seq(unsigned *test_seq, int *integral_f, int N, unsigned T){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, 9);
    unsigned n = log10(integral_f[N-1]);
    for (unsigned i=0; i!=T; i++){
        unsigned a = 0;
        for (unsigned j=0; j!=n; j++){
            a = a*10 + arr[dstr(rng)];
        }
        while (a > integral_f[N-1]){
            a = 0;
            for (unsigned j=0; j!=n; j++){
                a = a*10 + arr[dstr(rng)];
            }
        }
        test_seq[i] = binary_search(integral_f, N, a);
    }
}

int main(){
    unsigned T = 1000;
    int *integral_f = new int[1000000];
    int accum = 0;
    for (int i=0; i!=1000000; i++){
        accum += f(i);
        if (accum < 0){
            std::cout<<"Negative diff";
            return 0;
        }
        integral_f[i] = accum;
    }
    for (int N=10000; N!=1000000; N+=10000){
        int *numbers = new int[N];
        for (int i=0; i!=N; i++){
            numbers[i] = i;
        }
        unsigned *test_seq = new unsigned[T];
        get_test_seq(test_seq, integral_f, N, T);
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            strategyB(numbers, N, numbers[test_seq[i]]);
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<N<<','<<time_span.count()<<'\n';
        delete[] numbers;
        delete[] test_seq;
    }
    delete[] integral_f;
    return 0;
}

