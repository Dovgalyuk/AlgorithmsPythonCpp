#include <iostream>

int main()
{
  // SEND + MORE = MONEY
  for (int S = 1 ; S <= 9 ; ++S)
  {
    for (int E = 0 ; E <= 9 ; ++E)
    {
      for (int N = 0 ; N <= 9 ; ++N)
      {
        for (int D = 0 ; D <= 9 ; ++D)
        {
          for (int M = 1 ; M <= 9 ; ++M)
          {
            for (int O = 0 ; O <= 9 ; ++O)
            {
              for (int R = 0 ; R <= 9 ; ++R)
              {
                for (int Y = 0 ; Y <= 9 ; ++Y)
                {
                  if (S != E && S != N && S != D
                    && S != M && S != O && S != R
                    && S != Y && E != N && E != D
                    && E != M && E != O && E != R
                    && E != Y && N != D && N != M
                    && N != O && N != R && N != Y
                    && D != M && D != O && D != R
                    && D != Y && M != O && M != R
                    && M != Y && O != R && O != Y
                    && R != Y
                    && S * 1000 + E * 100 + N * 10 + D
                    + M * 1000 + O * 100 + R * 10 + E
                    == M * 10000 + O * 1000 + N * 100
                    + E * 10 + Y)
                  {
                    std::cout << "SEND+MORE=MONEY\n";
                    std::cout << S << E << N << D << '+'
                      << M << O << R << E << '='
                      << M << O << N << E << Y << '\n';
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
