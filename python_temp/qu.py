#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

def quadratic(a, b, c):
    x = math.sqrt( b*b - 4*a*c );
    y1 = -b + x;
    y2 = -b - x;

    return y1 / (2 * a), y2 / (2 * a)

print( quadratic( 2, 3, 1) )
print( quadratic( 1, 3, -4) )

