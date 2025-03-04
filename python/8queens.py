#!/usr/bin/python3

N = 8
queens = [0] * N

def check(x1, y1, x2, y2):
  if y1 == y2:
    return False
  if x2 - x1 == y2 - y1 or x2 - x1 == y1 - y2:
    return False
  return True

def find(q):
  if q == N:
    for i in range(N):
      pos = queens[i]
      line = '.' * pos + 'Q' + '.' * (N - pos - 1)
      print(line)
    print()
    return
  for i in range(N):
    ok = True
    for k in range(q):
      ok = check(k, queens[k], q, i)
      if not ok:
        break
    if ok:
      queens[q] = i
      find(q + 1)

find(0)
