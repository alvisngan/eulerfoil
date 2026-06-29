
#if defined(_MSC_VER)
    #define EF_ALIGNAS(n) __declspec(align(n))
#elif defined(__GNUC__) || defined(__clang__)
    #define EF_ALIGNAS(n) __attribute__((aligned(n)))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 2011112L
    #define EF_ALIGNAS(n) _Alignas(n)
#else
    #error "EF_ALIGNAS requires GCC, Clang, MSVC, or a C11 compiler"
#endif
