#!/usr/bin/env python3

import pylab as plt
import numpy as np
import sys

data = np.loadtxt(sys.argv[1], delimiter=',')
if len(data.shape) == 1:
    data = np.array([data])
inc = 0
for i, line in enumerate(data):
    x = np.arange(line.size)
    inc += np.max(np.abs(line[line<0]))*1.05 if len(line[line<0]>0) else 0
    pline, = plt.plot(x, line+inc)
    plt.plot(x, np.repeat(inc, line.size), linestyle=':', color=pline.get_color())
    inc += np.max(line) * 1.05
plt.tight_layout()
plt.show()
