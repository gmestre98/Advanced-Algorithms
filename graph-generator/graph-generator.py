import networkx as nx
import xml.etree.ElementTree as ET
import os

import xml_parser

ROOT_DIRECTORY = "build" + os.path.sep + "generated_graphs"

def generate_np_random_graph(number_of_nodes, probability, name):
	if (not isinstance(number_of_nodes, int) or not isinstance(probability, float)) or not isinstance(name, str):
		raise ValueError

	if (number_of_nodes < 0):
		raise ValueError("Number of Edges cannot be negative!")

	if (probability < 0 or probability > 1):
		raise ValueError("Probability must be between 0 and 1")

	file_name = ROOT_DIRECTORY + os.path.sep + "gn_random_graphs" + os.path.sep + name + "_" +str(number_of_nodes) + "_" + str(int(probability * 100)) + ".txt"
	
	if (not os.path.exists(ROOT_DIRECTORY)):
		os.mkdir(ROOT_DIRECTORY)
		
	if (not os.path.exists(ROOT_DIRECTORY + os.path.sep + "gn_random_graphs")):
		os.mkdir(ROOT_DIRECTORY + os.path.sep + "gn_random_graphs")
	
	graph = nx.gnp_random_graph(number_of_nodes, probability)

	file = open(file_name, 'w')

	file.write(str(number_of_nodes) + "\n")

	for edge in graph.edges:
		file.write(str(edge[0]) + " " + str(edge[1]) + "\n")

	file.close()

def generate(graph):
	nodes = graph["nodes"]
	probabilities = graph["probabilities"]
	name = graph["name"]

	for n in nodes:
		if (len(probabilities) == 1):
			generate_np_random_graph(n, probabilities[0], name)
		elif (len(probabilities) == 3):
			p = probabilities[0]
			end = probabilities[1]
			step = probabilities[2]

			if (not isinstance(step, float)):
				raise ValueError("Probability step must be a float")

			if (step < 0.0 or step > 1.0):
				raise ValueError("Probability step must be between 0 and 1")

			while (p <= end):
				generate_np_random_graph(n, p, name)
				p += step

def main():
	xml_tree = ET.parse("graph-generator" + os.path.sep + "config.xml")

	root = xml_tree.getroot()

	for graph in root:
		generate(xml_parser.get_graph_params(graph))

if __name__ == "__main__":
	main()