#include "../libcoyotl/mtwister.h"
#include "../libcoyotl/mwc1038.h"
#include "../libcoyotl/kissrng.h"
#include "../libcoyotl/mwc256.h"
#include "../libcoyotl/cmwc4096.h"
using namespace libcoyotl;

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

static const long TEST_SIZE = 1000000000;

double test_prng(prng & generator)
{
    uint32_t  i, count, total;
    double n, l, s;
    int counts[10];

    /*
    //  each real function
    cout << "\nrand_real1 - interval [0,1]" << endl;

    s = 1.1;
    l = -0.1;
    
    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = generator.get_rand_real1();
        
        if (n < s) s = n;
        if (n > l) l = n;
    }

    cout << "    largest = " << l << "\n   smallest = " << s << endl;

    //  each real function
    cout << "\nrand_real2 - interval [0,1)" << endl;
    
    s = 1.1;
    l = -0.1;
    
    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = generator.get_rand_real2();

        if (n < s) s = n;
        if (n > l) l = n;
    }

    cout << "    largest = " << l << "\n   smallest = " << s << endl;

    //  each real function
    cout << "\nrand_real3 - interval (0,1)" << endl;
    
    s = 1.1;
    l = -0.1;
    
    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = generator.get_rand_real3();

        if (n < s) s = n;
        if (n > l) l = n;
    }

    cout << "    largest = " << l << "\n   smallest = " << s << endl;

    //  each real function
    cout << "\nrand_real53 - interval [0,1) - 53-bit precision" << endl;
    
    s = 1.1;
    l = -0.1;
    
    for (i = 0; i < TEST_SIZE; ++i)
    {
        n = generator.get_rand_real53();

        if (n < s) s = n;
        if (n > l) l = n;
    }

    cout << "    largest = " << l << "\n   smallest = " << s << endl;

    //  check ranges
    for (i = 0; i < 10; ++i)
        counts[i] = 0;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        int x = generator.get_rand_index(10);
        ++counts[x];
    }

    cout << "\n";

    total = 0;

    for (i = 0; i < 10; ++i)
    {
        cout << "counts " << i << " = " << counts[i] << endl;
        total += counts[i];
    }

    cout << "total = " << total << endl;
    */
    
    // get starting time    
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME,&start);
    
    // test generation speed
    for (i = 0; i < TEST_SIZE; ++i)
        uint32_t dummy = generator.get_rand();

    // calculate run time
    clock_gettime(CLOCK_REALTIME,&stop);        
    return ((stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0);
}

int main()
{
    cout.precision(15);
    cout.setf(ios::showpoint | ios::fixed);
    
    mtwister mtwister_gen;
    double mtwister_time = test_prng(mtwister_gen);

    mwc1038 mwc1038_gen;
    double mwc1038_time = test_prng(mwc1038_gen);
    
    kissrng kissrng_gen;
    double kissrng_time = test_prng(kissrng_gen);
    
    mwc256 mwc256_gen;
    double mwc256_time = test_prng(mwc256_gen);
    
    cmwc4096 cmwc4096_gen;
    double cmwc4096_time = test_prng(cmwc4096_gen);
    
    cout.precision(2);
    cout << "\nALGORITHM TIMING (random numbers / second)" << endl;
    
    cout << "mtwister = " << right << setw(7) << mtwister_time
                          << " (" << (unsigned long)(double(TEST_SIZE) / mtwister_time)
                          << " rn/sec)" << endl;
    
    cout << " mwc1038 = " << right << setw(7) << mwc1038_time
                          << " (" << (unsigned long)(double(TEST_SIZE) / mwc1038_time)
                          << " rn/sec)"  << endl;
    
    cout << " kissrng = " << right << setw(7) << kissrng_time 
                          << " (" << (unsigned long)(double(TEST_SIZE) / kissrng_time)
                          << " rn/sec)"  << endl;
    
    cout << "  mwc256 = " << right << setw(7) << mwc256_time
                          << " (" << (unsigned long)(double(TEST_SIZE) / mwc256_time)
                          << " rn/sec)"   << endl;
    
    cout << "cmwc4096 = " << right << setw(7) << cmwc4096_time
                          << " (" << (unsigned long)(double(TEST_SIZE) / cmwc4096_time)
                          << " rn/sec)" << endl;
                
    return 0;
}

