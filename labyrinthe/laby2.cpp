#include <iostream>
#include <numeric>

using namespace std;

template<int N> requires (!(N % 2) or !(N % 3) or !(N % 5) or !(N % 7) or !(N % 11))
constexpr bool is_prime_beyond_11()
{
    return false;
}
template<int N>
constexpr bool is_prime_beyond_11()
{
    return true;
}

template<int N>
struct decrement
{
    static const int value = decrement<N - 1>::value;
};

// only if not a multiple of 5
template<int F> requires (F % 5 != 0)
constexpr int gimmeThatFlag()
{
    return decrement<F>::value;
}

// if multiple of 5
template<int F>
constexpr int gimmeThatFlag()
{
    return F % 7;
}

//template<int Z> requires (sizeof(int) == 4 and !((Z >> 31) & 1))
//constexpr int only_negative_gives_15()
//{
//    return decrement<Z>::value;
//}

template<int Z> requires(Z < 0)
constexpr int only_negative_gives_15()
{
    return 15;
}


template<int X, int N>
struct OSS {
    static const int value = OSS<X+15, N+1>::value;
};

template<int N>
struct OSS<1755, N> {
    static const int value = N;
};


template<int N> requires (N == 0) consteval int decimal_to_binary();
template<int N> requires ((N % 10) < 2 && N > 0) consteval int decimal_to_binary();

// Returns 0 if N == 0
template<int N> requires (N == 0)
consteval int decimal_to_binary()
{
    return N;
}

// 1010101010
template<int N> requires ((N % 10) < 2 && N > 0)
consteval int decimal_to_binary()
{
    return N % 10 + 2 * decimal_to_binary<N / 10>();
}

template <int x, int t> requires (x == 0)
consteval int trim_flipped_binary()
{
    return t;
}

template <int x, int t>
consteval int trim_flipped_binary()
{
    return trim_flipped_binary<x / 2, t * 2 + x % 2>();
}

// gets the value in decimal of a binary number trimmed with the bits mirrored
template <int x>
consteval int trim_flipped_binary()
{
    return trim_flipped_binary<x, 0>();
}

// takes 0b000011101010000000 trims it to 0b1110101 and reads it backwards to 0b1010111
static_assert(trim_flipped_binary<0b000011101010000000>() == 0b1010111);

template<
    int Conçu,          // F
    int par,            // L
    int l_esprit,       // A
    int diabolique,     // G
    int du,             // - // 45 + 15 * N1
    int Baron,          //   // N * 7 + 3 && LABYRINTHE - 8
    int Sukumvit,       // P ou s // 80 ou 115 // 10 + 35 * N2
    int LE,             //   // > 20
    int LABYRINTHE,     //   // 1 + LA, 8 + Baron
    int DE,             //   // N * 14 => 70 F, 84 T, 98 b, 112 p
    int LA,             //   // LABYRINTHE - 1
    int MORT,           // a
    int est = 77,       // M
    int truffé,         // S
    int de = 114,       // r
    int pièges = 115,   // s
    int mortels,        // = Baron
    int et = 110,       // n
    int peuplé,         // multiple de 8 et 10 so multipe de 80
    int _de,
    int monstres = 117, // u
    int assoiffés,
    int de_,
    int sang,
    int ET = 110,       // n
    int VOUS = 97,      // a  0b1100001
    int oserez = 117,   // u
    int vous,           // 
    int y = 111,        // o
    int entrer = 114    // r
>
concept test = requires {
    -~de == pièges;
    (par % 2 == 0);
    (par % 6 == 4);
    decimal_to_binary<et>() == 6;
    oserez == OSS<0, 0>::value;
    (LE / 20 == LE % 10);
    is_prime_beyond_11<Baron>();
    est % 10 == est / 10;                        // good
    (du * 2 + 7 == MORT);
    (peuplé == ((peuplé / 10) * 2 * 5));
    (80 / (LABYRINTHE - Baron) == 10);
    !(assoiffés - peuplé + ~0);
    decimal_to_binary<monstres + 994>() == 15;   // good
    Baron % 7 == 3;
    DE % 14 == 0;
    de == entrer;                                // good
    !is_prime_beyond_11<vous - 5>();
    (assoiffés + de - de_ - est == monstres - vous); // (ass + 37 - de_ == 117 - vous)
    (diabolique - Conçu == LABYRINTHE - _de);
    (mortels == Baron);
    (char)(truffé - 212) == 127;
    ((LABYRINTHE - LA) == 1 - ((LABYRINTHE - LA) != (LABYRINTHE - LA)));
    gimmeThatFlag<Sukumvit>() == 3;
    decimal_to_binary<y>() == 7;                 // good
    LE < Baron;
    (vous / 58) == (int)((float)vous / 58.0f);   // useless
    trim_flipped_binary<VOUS>() == 67;           // good
    ~de == -115;                                 // good
    (!!(diabolique - Conçu) == (diabolique - Conçu));
    (Conçu * par * l_esprit == 345800);
    (Conçu % par == 70);
    vous != 42;
    Sukumvit > Baron;
    (du % only_negative_gives_15<128 - du * 3>() == 0); // good
    (par % 19 == 0);
    Baron % 9 == 2;
    LE % 4 == !!is_prime_beyond_11<LE>();
    decimal_to_binary<ET>() == 6; // good
    pièges - sang == peuplé - Conçu;
    (est / 7) % 10 == (est / 7) / 10; // good
    only_negative_gives_15<LABYRINTHE - DE>() % 3 == 0;
    (peuplé == ((peuplé / 8) * 2 * 4));
    -diabolique == Baron - diabolique + est - (est + Baron);
};

template<
int Conçu,          // F
int par,            // L
int l_esprit,       // A
int diabolique,     // G
int du,             // - // 45 + 15 * N1
int Baron,          //   // N * 7 + 3 && LABYRINTHE - 8
int Sukumvit,       // P ou s // 80 ou 115 // 10 + 35 * N2
int LE,             //   // > 20
int LABYRINTHE,     //   // 1 + LA, 8 + Baron
int DE,             //   // N * 14 => 70 F, 84 T, 98 b, 112 p
int LA,             //   // LABYRINTHE - 1
int MORT,           // a
int est,            // M 77
int truffé,         // S
int de,             // r
int pièges,         // s
int mortels,        // = Baron
int et,             // n
int peuplé,         // multiple de 8 et 10 so multipe de 80
int _de,
int monstres,       // u
int assoiffés,
int de_,
int sang,
int ET,             // n
int VOUS,           // a  0b1100001
int oserez,         // u
int vous,           // 
int y,              // o
int entrer          // r
> 

requires test
class Flag
{
public:
    void show_flag() const {

        cout << (char) Conçu;
        cout << (char) par;
        cout << (char) l_esprit;
        cout << (char) diabolique;
        cout << (char) du;
        cout << (char) par;
        cout << (char) Baron;
        cout << (char) Sukumvit;
        cout << (char) LE;
        cout << (char) Baron;
        cout << (char) LABYRINTHE;
        cout << (char) DE;
        cout << (char) LA;
        cout << (char) MORT;
        cout << (char) vous;
        cout << (char) Baron;
        cout << (char) Sukumvit;
        cout << (char) est;
        cout << (char) Baron;
        cout << (char) truffé;
        cout << (char) vous;
        cout << (char) de;
        cout << (char) Baron;
        cout << (char) pièges;
        cout << (char) Sukumvit;
        cout << (char) mortels;
        cout << (char) et;
        cout << (char) vous;
        cout << (char) peuplé;
        cout << (char) _de;
        cout << (char) monstres;
        cout << (char) Sukumvit;
        cout << (char) assoiffés;
        cout << (char) de_;
        cout << (char) Baron;
        cout << (char) par;
        cout << (char) Baron;
        cout << (char) est;
        cout << (char) sang;
        cout << (char) ET;
        cout << (char) y;
        cout << (char) vous;
        cout << (char) VOUS;
        cout << (char) oserez;
        cout << (char) entrer;
        cout << (char) Baron;

        cout << endl;
    }
};

//int main()
//{
//    constexpr int LE = 68;
//    static_assert(LE % 4 == !!is_prime_beyond_11<LE>());
//
//    // to find truffé
//    /*for (int i = 0; i < 100000; ++i)
//    {
//        if ((char)(i - 212) == 127)
//            cout << +i << '\n';
//    }*/
//}

int main() {
    Flag<
0, // int Conçu,
0, // int par,
0, // int l_esprit,
0, // int diabolique,
0, // int du,
0, // int Baron,
0, // int Sukumvit,
0, // int LE,
0, // int LABYRINTHE,
0, // int DE,
0, // int LA,
0, // int MORT,
0, // int est,
0, // int truffé,
0, // int de,
0, // int pièges,
0, // int mortels,
0, // int et, // != 7, != 3, 0 => 0
0, // int peuplé,
0, // int _de,
0, // int monstres,
0, // int assoiffés,
0, // int de_,
0, // int sang,
0, // int ET,
0, // int VOUS,
117, // int oserez,
0, // int vous,
0, // int y,
0 // int entrer
    > f;
    f.show_flag();
}
