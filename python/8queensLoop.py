#!/usr/bin/python3

def check(x1, y1, x2, y2):
  if y1 == y2:
    return False
  if x2 - x1 == y2 - y1 or x2 - x1 == y1 - y2:
    return False
  return True

for a in range(4):
  for b in range(4):
    if not check(0, a, 1, b):
      continue
    for c in range(4):
      if not check(0, a, 2, c) or not check(1, b, 2, c):
        continue
      for d in range(4):
        if not check(0, a, 3, d) or not check(1, b, 3, d) or not check(2, c, 3, d):
          continue
        field = [['.'] * 4, ['.'] * 4, ['.'] * 4, ['.'] * 4]
        field[a][0] = 'Q';
        field[b][1] = 'Q';
        field[c][2] = 'Q';
        field[d][3] = 'Q';
        for i in range(4):
          print(''.join(field[i]))
        print()
