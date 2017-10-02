#include "triTable.hpp"
#include "utils.hpp"

int triTable[256][13] = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 3, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, 2, 3, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 1, 5, 3, 1, -1, -1, -1, -1 },
  { 1, 3, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 5, 3, 3, 7, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 5, 4, 7, 4, 7, 2, 4, 3, 2, -1, -1, -1, -1 },
  { 2, 6, 1, 1, 7, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 6, 4, 7, 4, 7, 0, 4, 1, 0, -1, -1, -1, -1 },
  { 7, 5, 6, 5, 6, 0, 5, 2, 0, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 5, 1, 8, 5, -1, -1, -1, -1 },
  { 2, 3, 6, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 3, 8, 3, 8, 6, 3, 10, 6, -1, -1, -1, -1 },
  { 0, 1, 5, 2, 3, 6, 8, 10, 4, -1, -1, -1, -1 },
  { 6, 10, 8, 6, 8, 5, 6, 5, 3, 3, 1, 5, -1 },
  { 1, 3, 7, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, 1, 3, 7, -1, -1, -1, -1 },
  { 0, 5, 3, 3, 7, 0, 8, 10, 4, -1, -1, -1, -1 },
  { 7, 5, 8, 7, 8, 2, 3, 7, 2, 10, 8, 2, -1 },
  { 2, 6, 1, 1, 7, 2, 8, 10, 4, -1, -1, -1, -1 },
  { 7, 6, 10, 7, 10, 0, 1, 7, 0, 8, 10, 0, -1 },
  { 7, 5, 6, 5, 6, 0, 5, 2, 0, 8, 10, 4, -1 },
  { 7, 5, 6, 5, 6, 8, 5, 10, 8, -1, -1, -1, -1 },
  { 8, 9, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 8, 8, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 2, 9, 2, 9, 4, 2, 8, 4, -1, -1, -1, -1 },
  { 2, 3, 6, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, 8, 9, 5, -1, -1, -1, -1 },
  { 0, 1, 8, 8, 9, 0, 2, 3, 6, -1, -1, -1, -1 },
  { 6, 4, 8, 6, 8, 1, 3, 6, 1, 9, 8, 1, -1 },
  { 1, 3, 7, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, 8, 9, 5, -1, -1, -1, -1 },
  { 0, 3, 8, 3, 8, 7, 3, 9, 7, -1, -1, -1, -1 },
  { 7, 9, 8, 7, 8, 4, 7, 4, 3, 3, 2, 4, -1 },
  { 2, 6, 1, 1, 7, 2, 8, 9, 5, -1, -1, -1, -1 },
  { 6, 4, 7, 4, 7, 0, 4, 1, 0, 8, 9, 5, -1 },
  { 6, 7, 9, 6, 9, 0, 2, 6, 0, 8, 9, 0, -1 },
  { 6, 4, 7, 4, 7, 8, 4, 9, 8, -1, -1, -1, -1 },
  { 10, 4, 9, 9, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
  { 10, 2, 9, 2, 9, 0, 2, 5, 0, -1, -1, -1, -1 },
  { 9, 1, 10, 1, 10, 0, 1, 4, 0, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 3, 6, 10, 4, 9, 9, 5, 10, -1, -1, -1, -1 },
  { 3, 0, 5, 3, 5, 10, 6, 3, 10, 9, 5, 10, -1 },
  { 9, 1, 10, 1, 10, 0, 1, 4, 0, 2, 3, 6, -1 },
  { 9, 1, 10, 1, 10, 3, 1, 6, 3, -1, -1, -1, -1 },
  { 1, 3, 7, 10, 4, 9, 9, 5, 10, -1, -1, -1, -1 },
  { 10, 2, 9, 2, 9, 0, 2, 5, 0, 1, 3, 7, -1 },
  { 3, 0, 4, 3, 4, 9, 7, 3, 9, 10, 4, 9, -1 },
  { 10, 2, 9, 2, 9, 3, 2, 7, 3, -1, -1, -1, -1 },
  { 2, 6, 1, 1, 7, 2, 10, 4, 9, 9, 5, 10, -1 },
  { 0, 1, 5, 10, 6, 9, 9, 7, 10, -1, -1, -1, -1 },
  { 0, 2, 4, 10, 6, 9, 9, 7, 10, -1, -1, -1, -1 },
  { 10, 6, 9, 9, 7, 10, -1, -1, -1, -1, -1, -1, -1 },
  { 10, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, 10, 11, 6, -1, -1, -1, -1 },
  { 2, 3, 10, 10, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 3, 0, 11, 0, 11, 4, 0, 10, 4, -1, -1, -1, -1 },
  { 0, 1, 5, 2, 3, 10, 10, 11, 2, -1, -1, -1, -1 },
  { 5, 4, 10, 5, 10, 3, 1, 5, 3, 11, 10, 3, -1 },
  { 1, 3, 7, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 5, 3, 3, 7, 0, 10, 11, 6, -1, -1, -1, -1 },
  { 5, 4, 7, 4, 7, 2, 4, 3, 2, 10, 11, 6, -1 },
  { 2, 1, 10, 1, 10, 7, 1, 11, 7, -1, -1, -1, -1 },
  { 7, 11, 10, 7, 10, 4, 7, 4, 1, 1, 0, 4, -1 },
  { 5, 7, 11, 5, 11, 2, 0, 5, 2, 10, 11, 2, -1 },
  { 5, 4, 7, 4, 7, 10, 4, 11, 10, -1, -1, -1, -1 },
  { 8, 4, 11, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 0, 11, 0, 11, 2, 0, 6, 2, -1, -1, -1, -1 },
  { 0, 1, 5, 8, 4, 11, 11, 6, 8, -1, -1, -1, -1 },
  { 1, 2, 6, 1, 6, 8, 5, 1, 8, 11, 6, 8, -1 },
  { 11, 3, 8, 3, 8, 2, 3, 4, 2, -1, -1, -1, -1 },
  { 0, 3, 8, 3, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, 11, 3, 8, 3, 8, 2, 3, 4, 2, -1 },
  { 11, 3, 8, 3, 8, 1, 3, 5, 1, -1, -1, -1, -1 },
  { 1, 3, 7, 8, 4, 11, 11, 6, 8, -1, -1, -1, -1 },
  { 8, 0, 11, 0, 11, 2, 0, 6, 2, 1, 3, 7, -1 },
  { 0, 5, 3, 3, 7, 0, 8, 4, 11, 11, 6, 8, -1 },
  { 2, 3, 6, 8, 5, 11, 11, 7, 8, -1, -1, -1, -1 },
  { 1, 2, 4, 1, 4, 11, 7, 1, 11, 8, 4, 11, -1 },
  { 8, 0, 11, 0, 11, 1, 0, 7, 1, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 5, 11, 11, 7, 8, -1, -1, -1, -1 },
  { 8, 5, 11, 11, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 9, 5, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 9, 5, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 1, 8, 8, 9, 0, 10, 11, 6, -1, -1, -1, -1 },
  { 1, 2, 9, 2, 9, 4, 2, 8, 4, 10, 11, 6, -1 },
  { 2, 3, 10, 10, 11, 2, 8, 9, 5, -1, -1, -1, -1 },
  { 3, 0, 11, 0, 11, 4, 0, 10, 4, 8, 9, 5, -1 },
  { 0, 1, 8, 8, 9, 0, 2, 3, 10, 10, 11, 2, -1 },
  { 1, 3, 9, 9, 11, 1, 8, 10, 4, -1, -1, -1, -1 },
  { 1, 3, 7, 8, 9, 5, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, 8, 9, 5, 10, 11, 6, -1 },
  { 0, 3, 8, 3, 8, 7, 3, 9, 7, 10, 11, 6, -1 },
  { 2, 3, 6, 8, 10, 4, 9, 11, 7, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 7, 1, 11, 7, 8, 9, 5, -1 },
  { 0, 1, 5, 8, 10, 4, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, 9, 11, 7, -1, -1, -1, -1 },
  { 8, 10, 4, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 9, 5, 11, 9, -1, -1, -1, -1 },
  { 9, 11, 6, 9, 6, 2, 9, 2, 5, 5, 0, 2, -1 },
  { 1, 9, 11, 1, 11, 4, 0, 1, 4, 6, 11, 4, -1 },
  { 1, 2, 9, 2, 9, 6, 2, 11, 6, -1, -1, -1, -1 },
  { 3, 11, 9, 3, 9, 4, 2, 3, 4, 5, 9, 4, -1 },
  { 3, 0, 11, 0, 11, 5, 0, 9, 5, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 9, 9, 11, 1, -1, -1, -1, -1 },
  { 1, 3, 9, 9, 11, 1, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 3, 7, 4, 5, 6, 5, 6, 9, 5, 11, 9, -1 },
  { 0, 1, 5, 2, 3, 6, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, 9, 11, 7, -1, -1, -1, -1 },
  { 2, 3, 6, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 1, 5, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 9, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 9, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, 9, 11, 7, -1, -1, -1, -1 },
  { 2, 3, 6, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 1, 5, 2, 3, 6, 9, 11, 7, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 1, 5, 3, 1, 9, 11, 7, -1 },
  { 1, 3, 9, 9, 11, 1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 9, 9, 11, 1, -1, -1, -1, -1 },
  { 3, 0, 11, 0, 11, 5, 0, 9, 5, -1, -1, -1, -1 },
  { 4, 5, 9, 4, 9, 3, 2, 4, 3, 11, 9, 3, -1 },
  { 1, 2, 9, 2, 9, 6, 2, 11, 6, -1, -1, -1, -1 },
  { 4, 6, 11, 4, 11, 1, 0, 4, 1, 9, 11, 1, -1 },
  { 6, 11, 9, 6, 9, 5, 6, 5, 2, 2, 0, 5, -1 },
  { 4, 5, 6, 5, 6, 9, 5, 11, 9, -1, -1, -1, -1 },
  { 8, 10, 4, 9, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 1, 5, 8, 10, 4, 9, 11, 7, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 5, 1, 8, 5, 9, 11, 7, -1 },
  { 2, 3, 6, 8, 10, 4, 9, 11, 7, -1, -1, -1, -1 },
  { 0, 3, 8, 3, 8, 6, 3, 10, 6, 9, 11, 7, -1 },
  { 0, 1, 5, 2, 3, 6, 8, 10, 4, 9, 11, 7, -1 },
  { 1, 3, 7, 8, 9, 5, 10, 11, 6, -1, -1, -1, -1 },
  { 1, 3, 9, 9, 11, 1, 8, 10, 4, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, 1, 3, 9, 9, 11, 1, -1 },
  { 3, 0, 11, 0, 11, 5, 0, 9, 5, 8, 10, 4, -1 },
  { 2, 3, 10, 10, 11, 2, 8, 9, 5, -1, -1, -1, -1 },
  { 1, 2, 9, 2, 9, 6, 2, 11, 6, 8, 10, 4, -1 },
  { 0, 1, 8, 8, 9, 0, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 9, 5, 10, 11, 6, -1, -1, -1, -1 },
  { 8, 9, 5, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 5, 11, 11, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 5, 11, 11, 7, 8, -1, -1, -1, -1 },
  { 8, 0, 11, 0, 11, 1, 0, 7, 1, -1, -1, -1, -1 },
  { 2, 1, 7, 2, 7, 8, 4, 2, 8, 11, 7, 8, -1 },
  { 2, 3, 6, 8, 5, 11, 11, 7, 8, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, 8, 5, 11, 11, 7, 8, -1 },
  { 8, 0, 11, 0, 11, 1, 0, 7, 1, 2, 3, 6, -1 },
  { 1, 3, 7, 8, 4, 11, 11, 6, 8, -1, -1, -1, -1 },
  { 11, 3, 8, 3, 8, 1, 3, 5, 1, -1, -1, -1, -1 },
  { 0, 2, 4, 11, 3, 8, 3, 8, 1, 3, 5, 1, -1 },
  { 0, 3, 8, 3, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
  { 11, 3, 8, 3, 8, 2, 3, 4, 2, -1, -1, -1, -1 },
  { 2, 1, 5, 2, 5, 11, 6, 2, 11, 8, 5, 11, -1 },
  { 0, 1, 5, 8, 4, 11, 11, 6, 8, -1, -1, -1, -1 },
  { 8, 0, 11, 0, 11, 2, 0, 6, 2, -1, -1, -1, -1 },
  { 8, 4, 11, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1 },
  { 5, 4, 7, 4, 7, 10, 4, 11, 10, -1, -1, -1, -1 },
  { 2, 10, 11, 2, 11, 5, 0, 2, 5, 7, 11, 5, -1 },
  { 10, 11, 7, 10, 7, 1, 10, 1, 4, 4, 0, 1, -1 },
  { 2, 1, 10, 1, 10, 7, 1, 11, 7, -1, -1, -1, -1 },
  { 2, 3, 6, 5, 4, 7, 4, 7, 10, 4, 11, 10, -1 },
  { 0, 5, 3, 3, 7, 0, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, 10, 11, 6, -1, -1, -1, -1 },
  { 1, 3, 7, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 3, 11, 10, 3, 10, 5, 1, 3, 5, 4, 10, 5, -1 },
  { 0, 1, 5, 2, 3, 10, 10, 11, 2, -1, -1, -1, -1 },
  { 3, 0, 11, 0, 11, 4, 0, 10, 4, -1, -1, -1, -1 },
  { 2, 3, 10, 10, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, 10, 11, 6, -1, -1, -1, -1 },
  { 0, 1, 5, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 10, 11, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 10, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 10, 6, 9, 9, 7, 10, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 10, 6, 9, 9, 7, 10, -1, -1, -1, -1 },
  { 0, 1, 5, 10, 6, 9, 9, 7, 10, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, 10, 6, 9, 9, 7, 10, -1 },
  { 10, 2, 9, 2, 9, 3, 2, 7, 3, -1, -1, -1, -1 },
  { 0, 3, 7, 0, 7, 10, 4, 0, 10, 9, 7, 10, -1 },
  { 0, 1, 5, 10, 2, 9, 2, 9, 3, 2, 7, 3, -1 },
  { 1, 3, 7, 10, 4, 9, 9, 5, 10, -1, -1, -1, -1 },
  { 9, 1, 10, 1, 10, 3, 1, 6, 3, -1, -1, -1, -1 },
  { 0, 2, 4, 9, 1, 10, 1, 10, 3, 1, 6, 3, -1 },
  { 0, 3, 6, 0, 6, 9, 5, 0, 9, 10, 6, 9, -1 },
  { 2, 3, 6, 10, 4, 9, 9, 5, 10, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
  { 9, 1, 10, 1, 10, 0, 1, 4, 0, -1, -1, -1, -1 },
  { 10, 2, 9, 2, 9, 0, 2, 5, 0, -1, -1, -1, -1 },
  { 10, 4, 9, 9, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
  { 6, 4, 7, 4, 7, 8, 4, 9, 8, -1, -1, -1, -1 },
  { 0, 8, 9, 0, 9, 6, 2, 0, 6, 7, 9, 6, -1 },
  { 0, 1, 5, 6, 4, 7, 4, 7, 8, 4, 9, 8, -1 },
  { 2, 6, 1, 1, 7, 2, 8, 9, 5, -1, -1, -1, -1 },
  { 8, 9, 7, 8, 7, 3, 8, 3, 4, 4, 2, 3, -1 },
  { 0, 3, 8, 3, 8, 7, 3, 9, 7, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, 8, 9, 5, -1, -1, -1, -1 },
  { 1, 3, 7, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 9, 8, 1, 8, 6, 3, 1, 6, 4, 8, 6, -1 },
  { 0, 1, 8, 8, 9, 0, 2, 3, 6, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, 8, 9, 5, -1, -1, -1, -1 },
  { 2, 3, 6, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 2, 9, 2, 9, 4, 2, 8, 4, -1, -1, -1, -1 },
  { 0, 1, 8, 8, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 8, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 9, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 7, 5, 6, 5, 6, 8, 5, 10, 8, -1, -1, -1, -1 },
  { 0, 2, 4, 7, 5, 6, 5, 6, 8, 5, 10, 8, -1 },
  { 0, 8, 10, 0, 10, 7, 1, 0, 7, 6, 10, 7, -1 },
  { 2, 6, 1, 1, 7, 2, 8, 10, 4, -1, -1, -1, -1 },
  { 2, 10, 8, 2, 8, 7, 3, 2, 7, 5, 8, 7, -1 },
  { 0, 5, 3, 3, 7, 0, 8, 10, 4, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, 1, 3, 7, -1, -1, -1, -1 },
  { 1, 3, 7, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 10, 6, 8, 6, 3, 8, 3, 5, 5, 1, 3, -1 },
  { 0, 1, 5, 2, 3, 6, 8, 10, 4, -1, -1, -1, -1 },
  { 0, 3, 8, 3, 8, 6, 3, 10, 6, -1, -1, -1, -1 },
  { 2, 3, 6, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 1, 10, 1, 10, 5, 1, 8, 5, -1, -1, -1, -1 },
  { 0, 1, 5, 8, 10, 4, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 8, 8, 10, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 8, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 7, 5, 6, 5, 6, 0, 5, 2, 0, -1, -1, -1, -1 },
  { 6, 4, 7, 4, 7, 0, 4, 1, 0, -1, -1, -1, -1 },
  { 2, 6, 1, 1, 7, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 5, 4, 7, 4, 7, 2, 4, 3, 2, -1, -1, -1, -1 },
  { 0, 5, 3, 3, 7, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 3, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 4, 5, 6, 5, 6, 1, 5, 3, 1, -1, -1, -1, -1 },
  { 0, 1, 5, 2, 3, 6, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 4, 3, 3, 6, 0, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 3, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 2, 4, 1, 1, 5, 2, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
};

std::pair<int, int> getCubeVertexIndices(int edgeNum) {
  switch (edgeNum) {
    case 0:
      return {0, 1};
    case 1:
      return {1, 3};
    case 2:
      return {0, 2};
    case 3:
      return {2, 3};
    case 4:
      return {0, 4};
    case 5:
      return {1, 5};
    case 6:
      return {2, 6};
    case 7:
      return {3, 7};
    case 8:
      return {4, 5};
    case 9:
      return {5, 7};
    case 10:
      return {4, 6};
    case 11:
      return {6, 7};
    default:
      // Should never reach here
      return {-1, -1};
  }
}

glm::vec3 getCubeVertex(int vertexNum) {
  switch (vertexNum) {
    case 0:
      return glm::vec3(0, 0, 1);
    case 1:
      return glm::vec3(1, 0, 1);
    case 2:
      return glm::vec3(0, 1, 1);
    case 3:
      return glm::vec3(1, 1, 1);
    case 4:
      return glm::vec3(0, 0, 0);
    case 5:
      return glm::vec3(1, 0, 0);
    case 6:
      return glm::vec3(0, 1, 0);
    case 7:
      return glm::vec3(1, 1, 0);
  }
}

std::pair<glm::vec3, glm::vec3> getPositionAndNormal(
    int edgeVertexNum, float* densityCube, glm::vec3* gradientCube, float isoLevel) {
  int leftIdx, rightIdx;
  std::tie(leftIdx, rightIdx) = getCubeVertexIndices(edgeVertexNum);

  float weight =
      (isoLevel - densityCube[rightIdx]) / (densityCube[leftIdx] - densityCube[rightIdx]);

  glm::vec3 position = lerp(getCubeVertex(leftIdx), getCubeVertex(rightIdx), weight);
  glm::vec3 normal = lerp(gradientCube[leftIdx], gradientCube[rightIdx], weight);

  return {position, normal};
}
