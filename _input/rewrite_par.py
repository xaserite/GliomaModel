import os
from pathlib import Path

def line_prepender(filename, line):
    with open(filename, 'r+') as f:
        content = f.read()
        f.seek(0, 0)
        f.write(line.rstrip('\r\n') + '\n' + content)

def word_swapper(filename):
    with open(filename, 'r+') as f:
        w = f.read().split()
        content = w[0]+'\n'+w[1]+'\t'+w[3]+'\n'+w[2]+'\t'+w[4]+'\t'+w[5]+'\n'+w[6]+'\t'+w[7]+'\n'+w[8]
        f.seek(0,0)
        f.write(content)

line = '1'
directory = 'C:\\Users\\mswin\\Documents\\C++\\MasterThesis\\GliomaModel\\_input'
filelist = os.listdir(directory)
for each_file in filelist:
    if each_file.startswith('par_'):
        word_swapper(each_file)
        #print(each_file)

