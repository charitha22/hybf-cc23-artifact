import sys

import numpy as np

import matplotlib.pyplot as plt

def loadData(path, versions):
  data = {}
  with open(path) as f:
    for line in f:
      entries = [e.strip() for e in line.split(',')]
      val = entries[-1]
      v = entries[-2]
      key = ','.join(entries[:-2])
      if key not in data.keys():
        data[key] = {}
      print(line)
      data[key][v] = float(val)
  
  for k in list(data.keys()):
    if 'baseline' not in data[k].keys() or np.any([v not in data[k].keys() for v in versions]):
      del data[k]
    elif 'baseline' in data[k].keys() and float(data[k]['baseline'])==0:
      del data[k]
  return data

path = sys.argv[1]
versions = [sys.argv[2], sys.argv[3]]

data = loadData(path,versions)
benchnames = list(sorted(list(data.keys()), key=lambda x: tuple([float(data[x]['baseline']-data[x][v])/float(data[x]['baseline']) for v in versions]) ))
#benchnames = list(sorted(list(data.keys()), key=lambda x: float(data[x]['baseline']-data[x][versions[0]])/float(data[x]['baseline']) ))

ys = []
ys2 = []
for x in benchnames:
  if np.any([data[x]['baseline']!=data[x][v] for v in versions]):
    gain = float(data[x]['baseline']-data[x][versions[0]])/float(data[x]['baseline'])
    print(x,gain)
    ys.append(gain*100.0)

    gain = float(data[x]['baseline']-data[x][versions[1]])/float(data[x]['baseline'])
    print(x,gain)
    ys2.append(gain*100.0)

print('', np.mean(ys))

xs = range(len(ys))

colors = [ '#4F9DA6', '#FFAD5A', '#FF5959']

print('Count zeros:', sum([ (1 if y==0 else 0) for y in ys]) )

fig, ax = plt.subplots(figsize=(5, 6))

ax.yaxis.grid(True) #horizontal grid
ax.xaxis.grid(False) #horizontal grid

plt.ylabel('Reduction (%)')


plt.fill_between(xs,ys2,color=colors[2])
plt.fill_between(xs,ys,color=colors[0])
plt.plot(xs,ys,color=colors[0],alpha=0.7)
plt.plot(xs,ys2,color=colors[2],alpha=0.7)
#plt.scatter(xs,ys2,linewidths=0.2,alpha=0.7,color='red')


plt.xlim(- 0.005*len(xs),len(xs)+0.005*len(xs))

minY = min([min(ys),min(ys2)])
maxY = max([max(ys),max(ys2)])
plt.ylim(minY - 0.01*minY , maxY + maxY*0.01)



#plt.show()
plt.savefig('percentage-reduction.pdf')
