package graphs.student;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.NavigableSet;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;
import java.util.Vector;
import java.util.TreeSet;

import org.apache.commons.math3.distribution.PoissonDistribution;


public class UnipartiteGraph {
	//iterator for the graph
	private Iterator<Map.Entry<String, Vertex>> gIt;
	
	/*
	 * START: graph representation
	 */
		//internal graph
		private TreeMap<String, Vertex> m;
	/*
	 * END: graph representation
	 */
	
	/*
	 * START: required functions
	 */

	/**
	 * Constructor
	 */
	public UnipartiteGraph() {
		//initialize
		m = new TreeMap<String, Vertex>();
	}

	/**
	 * 
	 * @param bpg instantiates the unipartite graph based on a bipartite graph of words and docs;
	 * creates vertices and edges, with edge weights the word similarity z_ab
	 */
	public void setGraph(BipartiteGraph bpg) {
		//edges to add
		Vector<Edge> eList = new Vector<Edge>();
		
		//iterator going through all of the items
		Iterator<Entry<String, Vertex>> allIter = bpg.Iter();
		
		while(allIter.hasNext()){
			Entry<String, Vertex> all = allIter.next();
			
			//skip going through the document vertices e.g: d1, d2, d3
			if (!bpg.namesOfDocs.contains(all.getKey())){

				//iterator going through the adj's of "all" 
				Iterator<String> adjIter = all.getValue().getAdjs().iterator();
				
				//adjs should be d1, d2, etc, etc
				while (adjIter.hasNext()){
					String adj = adjIter.next();
					
					//loop depending on how many times all(current word) appears in adj(d1, d2)
					for (int i = 0; i < bpg.numTimesWordOccursInDoc(all.getKey(), adj); i++){
						
						//now we need to the documents d1, d2, ..
						Iterator<Entry<String, Vertex>> docsIter = bpg.Iter();
						while(docsIter.hasNext()){
							Entry<String,Vertex> docs = docsIter.next();
							//find vertices of d1, d2, .. AND match adj(d1,d2,..) with matching doc
							if (bpg.namesOfDocs.contains(docs.getKey()) && docs.getKey() == adj){
								if (docs.getKey() == adj){
									//iterator going through docs
									Iterator<String> wordsIter = docs.getValue().getAdjs().iterator();
									while (wordsIter.hasNext()){
										String word = wordsIter.next();
										if (!all.getKey().equals(word)){
											eList.add(new Edge(all.getKey(), word));
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
		//add the edges in reverse so its an undirected graph
		Vector<Edge> eList2 = (Vector<Edge>) eList.clone();
		Iterator<Edge> eIt = eList.iterator();
		while (eIt.hasNext()) {
			Edge curEdge = eIt.next();
			eList2.add(new Edge(curEdge.getSecond(), curEdge.getFirst()));
		}
		
		for (Edge e : eList2){
			String key1 = e.getFirst();
			String key2 = e.getSecond();
			
			if (!m.containsKey(key1)) {
				Vertex v = new Vertex(key1);
				m.put(key1, v);
			}
			if (!m.containsKey(key2)) {
				Vertex v = new Vertex(key2);
				m.put(key2, v);
			}
			
			//calculate weights
			int weight = 0;
			for (String s : bpg.namesOfDocs){
				int weightAdjs = bpg.numTimesWordOccursInDoc(key2, s);
				int weightParent = bpg.numTimesWordOccursInDoc(key1, s);
				
				weight += weightAdjs * weightParent;
			}
			
			//set the corresponding weight
			m.get(key1).addAdjWithVal(key2, (double)weight);

		}
		
		//Update degree/weights
		for (Edge e : eList2){
			String key1 = e.getFirst();
			String key2 = e.getSecond();
			m.get(key1).setNum(m.get(key1).getAdjs().size());
		}
	}

	/**
	 * 
	 * @param a correspond to vertices in the graph
	 * @param b correspond to vertices in the graph
	 * @return the weight of the edge between vertices corresponding to words a and b
	 */
	public Double getEdgeWeight(String a, String b) {
		gIt = m.entrySet().iterator();
		
		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			
			if (pairs.getKey().equals(a)){
				return pairs.getValue().getAdjs().get(b).doubleValue();
			}
			
		}
		return 0.0;
	}

	/**
	 * 
	 * @param a correspond to vertices in the graph
	 * @param b correspond to vertices in the graph
	 * @param val sets the weight of the edge between vertices corresponding to words a and b to be val
	 */
	public void setEdgeWeight(String a, String b, Double val) {
		m.get(a).addAdjWithVal(b, val);
	}
	
	/**
	 * PRE: stopFileName is the name of a file containing stopwords <br>
	 * POST: as the regular setGraph(), but stopwords do not become vertices
	 * @param bpg  BipartiteGraph
	 * @param stopFileName text file which contains the stop words
	 */
	public void setGraphMinusStopwords(BipartiteGraph bpg, String stopFileName) {
		//delete the vertices of specificed words
		try {
			Vector<String> list = readStopWordList(stopFileName);
			
			for (String s : list){
				bpg.deleteVertex(s);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//now create the new graph
		this.setGraph(bpg);
	}

	/**
	 * POST: as the regular setGraph(), but sets the edge weights to be the values
	 * under the null model <z_ab> = s_a * s_b * L_C^2 + \sum_d L_d^2
	 * @param bpg BipartiteGraph
	 */
	public void setNullGraph(BipartiteGraph bpg) {
		
	}


	public void filterNoise(UnipartiteGraph nullGraph, Double p) {
		// PRE: 0 <= p <= 1
		// POST: reduce values on edges taking into account the null model graph;
		//         calculates Z_p(s_a, s_b) as per specs: the value which represents the 
		//         (1-p)-quantile of the Poisson distribution Pois_<z_ab>(z)
		
		// TODO
	}

	/**
	 * 
	 * @return returns number of vertices in the graph
	 */
	public Integer numVertices() {
		return m.size();
	}
	
	/**
	 * 
	 * @return returns number of edges in the graph
	 */
	public Integer numEdges() {
		int numEdges = 0;
		
		Iterator<Entry<String, Vertex>> iter = m.entrySet().iterator();
		while (iter.hasNext()){
			Entry<String, Vertex> current = iter.next();
			numEdges += current.getValue().getNum();
		}
		
		return numEdges / 2;
	}

	/**
	 * 
	 * @param w corresponds to a vertex in the graph
	 * @return the degree of the vertex corresponding to word w
	 */
	public Integer degreeWord(String w) {
		Iterator<Entry<String, Vertex>> iter = m.entrySet().iterator();
		while (iter.hasNext()){
			Entry<String, Vertex> current = iter.next();
			if (current.getKey().equals(w)){
				return current.getValue().getNum();
			}
		}
		
		return 0;
	}
	
	/**
	 * 
	 * @param k >= 0
	 * @return the number of vertices that have degree k
	 */
	public Integer numVerticesDegreeK(Integer k) {
		int count = 0;
		
		Iterator<Entry<String, Vertex>> iter = m.entrySet().iterator();
		while (iter.hasNext()){
			Entry<String, Vertex> current = iter.next();
			if (current.getValue().getNum() == k){
				count++;
			}
		}
		
		return count;
	}
	
	/**
	 * 
	 * @return the number of vertices that are connected to all other vertices
	 */
	public Integer numVerticesConnectedAll() {
		//since we know that if a vertex is connected to all other vertices
		//the number would be n - 1.  we can just look for such degree. 
		int count = 0;
		
		Iterator<Entry<String, Vertex>> iter = m.entrySet().iterator();
		while (iter.hasNext()){
			Entry<String, Vertex> current = iter.next();
			if (current.getValue().getNum() == numVertices() - 1){
				count++;
			}
		}
		
		return count;
	}

	/**
	 * 
	 * @return the average degree of all vertices in the graph;
	 * returns zero for the null graph
	 */
	public Double avgDegreeOfGraph() {
		if (m == null){
			return null;
		}
		
		double avg = 0;
		
		Iterator<Entry<String, Vertex>> iter = m.entrySet().iterator();
		while (iter.hasNext()){
			Entry<String, Vertex> current = iter.next();
			avg += current.getValue().getNum();
		}
		
		return avg / numVertices();
	}
	
	/**
	 * 
	 * @return returns the proportion of actual edges to maximum possible edges;
	 * returns zero for a null graph or single-vertex graph
	 */
	public Double propnPossibleEdges() {
		if (m == null || numVertices() == 1){
			return null;
		}
		
		//calculate maximum number of edges
		double maxEdges = 0.0;
		for (int i = 0; i < numVertices(); i++){
			maxEdges += i;
		}
		
		return numEdges() / maxEdges;
	}
	
	/*
	 * END: required functions
	 */
	
	/*
	 * START: suggested functions
	 */
	
	public void addVertex(String s) {
		// Adds a new vertex s to the graph
		
		// TODO
	}
	
	public void deleteVertex(String s) {
		// Deletes a vertex n from the graph
		
		
		// TODO
	}

	public void deleteEdge(String a, String b) {
		// Delete an edge between a and b if present 
		
		// TODO
	}
	
	/**
	 * Reads a text file and creates a list of words
	 * @param fInName path to the text file
	 * @return words as a Vector<String> 
	 * @throws IOException
	 */
	public Vector<String> readStopWordList (String fInName) throws IOException {
		
		Vector<String> list = new Vector<String>();
		
		BufferedReader br = new BufferedReader(new FileReader(fInName));
		
		try{
			String line = br.readLine();
			
			while (line != null){
				list.addElement(line);
				line = br.readLine();
			}
			
		}
		finally{
			br.close();
		}
		
		return list;
	}
	
	public void print() {
		gIt = m.entrySet().iterator();
		
		System.out.println("Number of nodes is " + m.size());
		System.out.println("Number of edges is " + numEdges());
		System.out.println("Word graph:");
		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			pairs.getValue().print2();
			
		}		
		System.out.println();
	}
	
	
	public static void main(String[] args) {
		BipartiteGraph bg = new BipartiteGraph();
		Vector<Edge> eList;

		String inName = "C:\\Users\\Nigel\\Desktop\\in1";
		// replace this with your directory path
		try {
			eList = bg.readFromDirectory(inName);
			bg.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		bg.print();

		UnipartiteGraph ug = new UnipartiteGraph();
		ug.setGraph(bg);
		
		String stopWordsName = "C:\\Users\\Nigel\\Desktop\\stop1.txt";
		// replace this with your directory path
		UnipartiteGraph ug2 = new UnipartiteGraph();
		ug2.setGraphMinusStopwords(bg, stopWordsName);

		UnipartiteGraph ugNull = new UnipartiteGraph();
		ugNull.setNullGraph(bg);
		ugNull.print();
		System.out.println("edge weight btw cat, angry : " + Double.toString(ugNull.getEdgeWeight("cat","angry")));

		ug.filterNoise(ugNull, 0.05);
		ug.print();
	}

}
