import os
import string

directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input\\no_borders'
Es = [1,0.5,1e-5]
t = 0.3
xN = 16
tN = 1
for  i in range(1,11):
    for eps in Es:
        filename = 'conv_' + str(eps).replace('.','') + '_' \
               + str(i).replace('.','') + '.data'
        content = '1\n' + str(int(tN/eps)) + '\t' + str(t) + '\n' + str(xN) + \
                  '\t-4\t4\n1\t0\n' + str(eps)
        with open(filename, 'w') as f:
            f.write(content)
    xN = xN *4
    tN = tN *4
