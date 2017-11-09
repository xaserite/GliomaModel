import os
import string

directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input'
eps = 0.5
times = [0.01,0.05,0.1,0.2,0.3,0.4,0.5,0.7,0.9]

for t in times:
    filename = 'par_' + str(t).replace('.','') + '_' \
               + str(eps).replace('.','') + '.data'
    content = '1\n4000\t' + str(t) + '\n200\t-1\t1\n1\t0\n' + str(eps)
    with open(filename, 'w') as f:
        f.write(content)
