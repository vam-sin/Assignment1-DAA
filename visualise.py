import networkx as nx 
import csv
import matplotlib.pyplot as plt 
import sys
import time


colors = ['g', 'r', 'c', 'b',  'm', 'y', 'k']
color_map = dict()
start_time = time.time()
g = nx.DiGraph() 

with open(sys.argv[1], 'r') as datafile:
	data = csv.reader(datafile, delimiter = " ")
	count = 0
	for row in data:
		nodes = []
		for point in row:
			if point != "":
				nodes.append(int(point))
				g.add_node(int(point))
				color_map[int(point)] = colors[count%7]
		count+=1

with open(sys.argv[2], 'r') as datafile:
	data = csv.reader(datafile, delimiter = " ")
	flag = True
	for row in data:
		if flag:
			flag = False
		else:
			g.add_edge(int(row[0]), int(row[1]))
print("Input done.")
pos = nx.spring_layout(g)

for n in g.nodes():
    g.nodes[n]['color'] = color_map[n]

colors = [node[1]['color'] for node in g.nodes(data=True)]
nx.draw_networkx(g, pos, with_labels=False, node_color=colors)
plt.savefig('foo.png')
end_time = time.time()
print("Execution time: ", end_time - start_time) 
