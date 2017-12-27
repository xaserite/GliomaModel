import os
import string

directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input'
vN = 4
xN = 100
xL = 48
xR = 53

E = ''
for i in range(1,xN):
    for j in range(1,xL):
        E = E + '1\t1\t1\t1\n'
    for j in range(xL+1,xR-1):
        E = E + '1.75\t1.75\t.25\t.25\n' + '1.75\t1.75\t.25\t.25\n'
    #    E = E + '1.9\t1.9\t.1\t.1\n' + '1.9\t1.9\t.1\t.1\n'
    #    E = E + '.25\t.25\t1.75\t1.75\n' + '.25\t.25\t1.75\t1.75\n'
    for j in range(xR,xN):
        E = E + '1\t1\t1\t1\n'

filename = '2d_vS_' + str(vN).replace('.','') + '_' \
              + str(xN).replace('.','') + '.data'
content = '2\t' + str(vN) + '\n' \
          + str(xN) +'\t' + str(xN) + '\n' \
          + str(.25) +'\t' + str(.25) +'\t' + str(.25) +'\t' + str(.25) +'\n' \
          + '1\t0\t-1\t0\t0\t1\t0\t-1\n' \
          + E
with open(filename, 'w') as f:
    f.write(content)
