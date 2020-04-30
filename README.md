# Advanced-Algorithms

## Dataset Generation

#### Pre-Requisites

It is required to exist under ```graph-generator``` directory an XML configuration file following the syntax:

Root tag must be called ```generator```

Each set of graph (i.e. graphs that share some characteristics) are described by tag ```random``` and they must have name specified in attribute ```name```.

Under this tag must be two other tags: ```nodes``` that specify the number of generated nodes, and ```probability``` that specify the probability of a given edge to be generated.

Under tag ```nodes``` it can be a tag ```node``` that must contain an integer specifying the number of nodes in the graph. In its place, it can be specified a range of values using tag ```range```. In this last case a begin and an end value must be specified using tags ```begin``` and ```end``` respectivily.

Tag ```probabilities``` must contain either a tag ```probability``` or a tag ```range```. Tag ```probability``` must contain a float that specifies the probalility of a given edge be generated (it must be between 0 and 1). Tag ```range``` must contain other 3 tags inside: ```begin``` that specify the begin of a range (must be between 0 and 1),  ``end`` that specify the end of the range (must be between 0 and 1), and a ```step``` that is step the probability is incremented in the range.

For clarity, it has provided an example of this file, named ```example-config.xml``` under ```graph-generator``` directory.

#### Generation

Once the ``config.xml`` file is written according to the description provided, under the CMake output directory, run the following command:

```
$ make gengraph
```

This will create under CMake output directory a directory tree, with root ```generated_graphs/```. The graphs generated will be located under the folder with the name of the algorithm used for its generation.

#### Naming Convension

The files are named following the convesion:

```
<grah_name>_<number_of_nodes>_<probability>.txt
```

#### File Format

The first line of the generated file is the graph's number of nodes.

Each of the following lines corresponde to an egde, from ``u`` to ``v``, separeted by a space.

This file uses LF as end of line sequence.

## Execution

## Data Structures
  
  There were implemented 3 different data structures to test the computation of these measures on graphs:
   - Adjacency List
   - Adjacency Matrix
   - Compressed Sparse Rows

## Measures
- The size of the minimum cut of the graph
- The clustering coefficient of a graph
