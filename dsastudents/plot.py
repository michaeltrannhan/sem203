import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

slisttime = pd.read_csv('slisttime.csv')
#print(slisttime.iloc[0:3])

slisttime = slisttime.to_numpy()

plt.figure(figsize=(15,8))
plt.scatter(slisttime[:, 0],  slisttime[:,1], c='r', marker='d', alpha=0.9, label='add(0, *)')
plt.scatter(slisttime[:, 0],  slisttime[:,2], c='g', marker='s', alpha=0.9, label='add(*)')
plt.scatter(slisttime[:, 0],  slisttime[:,3], c='b', marker='o', alpha=0.9, label='add(k, *)')
plt.scatter(slisttime[:, 0],  slisttime[:,4], c='m', marker='<', alpha=0.9, label='removeAt(0)')
plt.scatter(slisttime[:, 0],  slisttime[:,5], c='y', marker='v', alpha=0.9, label='removeAt(n-1)')
plt.scatter(slisttime[:, 0],  slisttime[:,6], c='c', marker='>', alpha=0.9, label='removeAt(k)')
plt.scatter(slisttime[:, 0],  slisttime[:,7], c='navy', marker='^', alpha=0.9, label='get(k)')
plt.legend()
plt.title('Computation time of some methods of SLinkedList')
plt.xlabel('number of items (n)')
plt.ylabel('msec')
plt.savefig('slinkedlist.png')
plt.show()