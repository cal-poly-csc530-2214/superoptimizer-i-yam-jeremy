#include <iostream>
#include <chrono>

int myabs(int x) {
   if (x >= 0) return x;        // Absolute value.
   else return -x;
}

int myabs_fast(int x) {
    //return (-(((((unsigned int)x) >> (x >> 31)) ^ x)) ^ (((unsigned int)x) >> (x >> 31)));
    //return (((unsigned int)(-(x) ^ x) >> (x >> 31)) ^ -(x));
    return (((-(x) ^ x) & (x >> 31)) ^ x);
}

int avg(int x, int y) {
    return ((unsigned long long)x + (unsigned long long)y) >> 1;
}

int avg_fast(int x, int y) {
    return (((y ^ x) >> 1) + (y & x));
}

int main() {
    constexpr int bits = 32;
    constexpr size_t size = 1L << bits;
    int* resultA = new int[size];
    int* resultB = new int[size];

    auto startDefault = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        /*int x = i >> (bits/2);
        int mask = 1 << (bits/2);
        mask -= 1;
        int y = i & mask;
        resultA[i] = avg(x, y);*/
        resultA[i] = myabs(i);
    }
    auto endDefault = std::chrono::high_resolution_clock::now();

    auto startFast = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        /*int x = i >> (bits/2);
        int mask = 1 << (bits/2);
        mask -= 1;
        int y = i & mask;
        resultB[i] = avg_fast((i >> (bits/2)), i & 0xFFFF);*/
        resultB[i] = myabs_fast(i);
    }
    auto endFast = std::chrono::high_resolution_clock::now();

    for (long i = 0; i < size; i++) {
        if (resultA[i] != resultB[i]) {
            /*int x = i >> (bits/2);
            int mask = 1 << (bits/2);
            mask -= 1;
            int y = i & mask;
            std::cerr << "(" << x << ", " << y << "): " << resultA[i] << " != " << resultB[i] << std::endl;*/
            std::cerr << "[" << i << "]: " << resultA[i] << " != " << resultB[i] << std::endl;
        }
    }

    auto durationDefault = std::chrono::duration_cast<std::chrono::microseconds>(endDefault - startDefault);
    auto durationFast = std::chrono::duration_cast<std::chrono::microseconds>(endFast - startFast);
  
    // To get the value of duration use the count()
    // member function on the duration object
    std::cout << "Default time: " << durationDefault.count() << " microseconds" << std::endl;
    std::cout << "Fast time: " << durationFast.count() << " microseconds" << std::endl;

    delete[] resultA;
    delete[] resultB;
}