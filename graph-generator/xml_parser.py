import os

def get_range(range_xml):
	if (len(range_xml) != 3):
		raise SyntaxError("Tag: " + range_xml.tag + " must have strictly 2 elements: \'begin\', \'end\' and \'step\'")
	
	begin = range_xml.find("begin").text
	end = range_xml.find("end").text
	step = range_xml.find("step").text

	return tuple(range(int(begin), int(end), int(step)))

def get_nodes(graph):
	if (len(graph) != 2):
		raise SyntaxError("Tag: " + graph.tag + " must have strictly 2 elements: \'nodes\' and \'probabilities\'")

	nodes = graph.find("nodes")
	
	if (len(nodes) != 1):
		raise SyntaxError("Tag: " + nodes.tag + " must have only one element: either range or node")

	child = nodes[0]

	if (child.tag == "range"):
		return get_range(child)
	elif (child.tag == "node"):
		return (int(child.text),)
	else:
		raise SyntaxError("Tag: " + child.tag + " must be either range or node")

def get_probability_range(range_xml):
	if (len(range_xml) != 3):
		raise SyntaxError("Tag: " + range_xml.tag + " must have strictly 3 elements: begin, end, and step")

	begin = range_xml.find("begin").text
	end = range_xml.find("end").text
	step = range_xml.find("step").text

	return ( float(begin), float(end), float(step) )

def get_probabilities(graph):
	if (len(graph) != 2):
		raise SyntaxError("Tag: " + graph.tag + " must have strictly 2 elements: \'nodes\' and \'probabilities\'")

	probabilities = graph.find("probabilities")

	if (len(probabilities) != 1):
		raise SyntaxError("Tag: " + graph.tag + " must jave onlu one element: either range or probability")

	child = probabilities[0]

	if (child.tag == "range"):
		return get_probability_range(child)
	elif (child.tag == "probability"):
		return tuple([float(child.text)])
	else:
		raise SyntaxError("Tag: " + child.tag + " must be either range or probability") 

def get_graph_params(graph):
	result = {}

	result["name"] = graph.attrib["name"]
	result["nodes"] = get_nodes(graph)
	result["probabilities"] = get_probabilities(graph)

	return result
