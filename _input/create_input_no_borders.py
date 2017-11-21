import os
import string

directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input\\no_borders'
Es = [1,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.05,0.01,0.005,0.001,1e-5]
times = [0.001,0.005,0.01,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5]

for t in times:
    for eps in Es:
        filename = 'par_' + str(t).replace('.','') + '_' \
               + str(eps).replace('.','') + '.data'
        content = '1\n4000\t' + str(t) + '\n800\t-4\t4\n1\t0\n' + str(eps)
        with open(filename, 'w') as f:
            f.write(content)
