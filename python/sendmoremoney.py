#!/usr/bin/python3

# SEND + MORE = MONEY
for S in range(1, 10):
  for E in range(10):
    for N in range(10):
      for D in range(10):
        for M in range(1, 10):
          for O in range(10):
            for R in range(10):
              for Y in range(10):
                if S != E and S != N and S != D \
                  and S != M and S != O and S != R \
                  and S != Y and E != N and E != D \
                  and E != M and E != O and E != R \
                  and E != Y and N != D and N != M \
                  and N != O and N != R and N != Y \
                  and D != M and D != O and D != R \
                  and D != Y and M != O and M != R \
                  and M != Y and O != R and O != Y \
                  and R != Y \
                  and S * 1000 + E * 100 + N * 10 + D \
                  + M * 1000 + O * 100 + R * 10 + E \
                  == M * 10000 + O * 1000 + N * 100 \
                  + E * 10 + Y:
                    print("SEND+MORE=MONEY")
                    print(f"{S}{E}{N}{D}+{M}{O}{R}{E}={M}{O}{N}{E}{Y}")
