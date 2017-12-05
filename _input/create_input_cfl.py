import os
import string

directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input\\no_borders'
Es = [1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.0078125,0.00390625,0.001953125,0.0009765625]
t = 0.25
xN = 64
tN = 4
for  i in range(1,8):
    for eps in Es:
        filename = 'cfl_' + str(eps).replace('.','') + '_' \
               + str(i).replace('.','') + '.data'
        content = '1\n' + str(int(tN/eps)) + '\t' + str(t) + '\n' + str(xN) + \
                  '\t-4\t4\n1\t0\n' + str(eps)
        with open(filename, 'w') as f:
            f.write(content)
    xN = xN *2
    tN = tN *2
