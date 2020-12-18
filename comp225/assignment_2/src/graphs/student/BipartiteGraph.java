package graphs.student;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.Map.Entry;

public class BipartiteGraph {
	//iterator for the graph
	private Iterator<Map.Entry<String, Vertex>> gIt;
	//number of edges in the graph
	private int numEdges;
	//list of document names which have been read from the directory
	List<String> namesOfDocs;

	/*
	 * START: graph representation
	 */

	//internal graph
	private TreeMap<String, Vertex> m;
	
	/*
	 * END: graph representation
	 */
	
	/*
	 * START: auxiliary functions
	 */
	
	/**
	 * 
	 * @return an iterator for the internal graph
	 */
	public Iterator<Map.Entry<String, Vertex>> Iter(){
		Iterator<Map.Entry<String, Vertex>> oIt = m.entrySet().iterator();
		return oIt;
	}
	
	/**
	 * 
	 * @return a list of file names which have been read from the given directory
	 */
	public List<String> getNamesOfDocs(){
		return namesOfDocs;
	}
	
	/**
	 * Sets directed edges between vertices and stores them in the TreeMap m
	 * @param eList Vector<Edge> list containing edges between vertices containing document names & words
	 */
	public void setDirected(Vector<Edge> eList) {
		// Instantiates a directed graph based on a list of edges
		m.clear();
		numEdges = eList.size();
		
		Iterator<Edge> eIt = eList.iterator();
		while (eIt.hasNext()) { // iterate through edges
			Edge curEdge = eIt.next();
			String key1 = curEdge.getFirst();
			String key2 = curEdge.getSecond();
			// Insert both vertices in the edge
			if (!m.containsKey(key1)) {
				Vertex v = new Vertex(key1);
				m.put(key1, v);
			}
			if (!m.containsKey(key2)) {
				Vertex v = new Vertex(key2);
				m.put(key2, v);
			}
			// Put second vertex in neighbour list of first vertex
			m.get(key1).incNum();
			m.get(key1).addAdjAndInc(key2);
		}
	}
	
	/*
	 * END: auxiliary functions
	 */
	
	/*
	 * START: required functions
	 */
		
	/**
	 * Constructor for BipartiteGraph class
	 */
	public BipartiteGraph() {
		//initialize required variables/objects
		m = new TreeMap<String, Vertex>();
		numEdges = 0;
		namesOfDocs = new ArrayList<String>();
	}
	
	/**
	 * PRE: - <br>
	 * POST: instantiates a bipartite graph based on the list of edges; edges represent word-document pairs <br>
	 * @param eList Vector<Edge> list containing edges between vertices containing document names & words
	 */
	public void setGraph(Vector<Edge> eList) {
		
		//we use a set so that we can store unique values (for the file names)
		Set<String> docNames = new HashSet<String>();
		
		// Instantiates an undirected graph based on a list of edges
		Vector<Edge> eList2 = (Vector<Edge>) eList.clone();
		
		Iterator<Edge> eIt = eList.iterator();
		// Extends list by reversing edges and adding them,
		// to get both directions (i.e. have symmetric adjacency lists)
		while (eIt.hasNext()) {
			Edge curEdge = eIt.next();
			eList2.add(new Edge(curEdge.getSecond(), curEdge.getFirst()));
			
			//add the document name to our docNames list
			docNames.add(curEdge.getSecond());
		}
		
		//since we have directions both ways, we can pass this through the directed function
		this.setDirected(eList2);
		
		//we divide number of edges by 2 because there are two vertices for one edge
		numEdges /= 2;
		
		//add all unique names to the document names array list
		namesOfDocs.addAll(docNames);
	}
	
	/**
	 * 
	 * @return returns number of vertices (both word and doc) in the graph
	 */
	public Integer numVertices() {		
		return m.size();
	}
	
	/**
	 * 
	 * @return returns number of edges in the graph
	 */
	public Integer numEdges() {
		return numEdges - namesOfDocs.size();
	}
	
	/**
	 * 
	 * @return returns number of word types in the graph (i.e. ignoring duplicate words)
	 */
	public Integer numWordTypes() {
		//we need to minus the number of documents because they are included in the total vertices
		return m.size() - namesOfDocs.size();
	}
	
	/**
	 * 
	 * @return returns number of word tokens in the graph (i.e. including duplicate words)
	 */
	public Integer numWordTokens() {
		//count which holds how many words there are (including duplicates)
		int count = 0;
		
		gIt = m.entrySet().iterator();
		
		//go through all vertices 
		while (gIt.hasNext()) {
			if (!namesOfDocs.contains(gIt)){
				Entry<String, Vertex> pairs = gIt.next();
				count += pairs.getValue().getNum();
			}
		}
		
		return count / 2;
	}
	
	/**
	 * 
	 * @param w word to count
	 * @return returns the number of times word w occurs across all documents
	 */
	public Integer numTimesWordOccurs(String w) {
		//if word exists in context
		if (m.containsKey(w)){
			//return it
			return m.get(w).getNum();
		}
		
		//if it hits here, word does not exist
		return 0;
	}
	
	/**
	 * 
	 * @param d corresponds to a vertex in the graph
	 * @return returns number of different words (i.e. word types) that occur in document d
	 */
	public Integer numWordTypesInDoc(String d) {
		//if document exists in context
		if (m.containsKey(d)){
			//return the number of words
			return m.get(d).getAdjs().size();
		}
		
		//if it hits here, document does not exist
		return 0;
	}

	/**
	 * 
	 * @param d corresponds to a vertex in the graph
	 * @return returns number of total words (i.e. including duplicates) that occur in document d
	 */
	public Integer numWordTokensInDoc(String d) {
		//if d exists in context
		if (m.containsKey(d)){
			//return number of total words
			return m.get(d).getNum();
		}
		
		//if it hits here, it does not exist
		return 0;
	}

	/**
	 * 
	 * @param w corresponds to a vertex in the graph
	 * @return returns number of documents word w occurs in
	 */
	public Integer numDocsWordOccursIn(String w) {
		//if w exists in context
		if (m.containsKey(w)){
			//return number of documents w occurs in
			return m.get(w).getAdjs().size();
		}
		
		//if it hits here, it does not exist
		return 0;
	}

	/**
	 * 
	 * @param w corresponds to a vertex(word) in the graph
	 * @param d corresponds to a vertex(doc) in the graph
	 * @return returns number of times word w occurs in doc d
	 */
	public Integer numTimesWordOccursInDoc(String w, String d) {
		//if document d exists
		if (m.containsKey(d)){
			//if word w exists in d
			if (m.get(d).getAdjs().containsKey(w)){
				//return number of times w occurs in d
				return m.get(d).getAdjs().get(w).intValue();
			}
		}
		
		//if it hits here, it does not exist
		return 0;
	}

	/**
	 * 
	 * @return returns the words that only occur in single documents the returned 
	 * list should be ordered alphabetically and should contain no duplicates
	 */
	public ArrayList<String> listOfWordsInSingleDocs() {
		//arraylist which we will return alphabetically
		ArrayList<String> words = new ArrayList<String>();
		
		//holds unique words (using set because it contains unique values)
		Set<String> solowords = new HashSet<String>();
		
		gIt = m.entrySet().iterator();
		
		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			
			//skip over checking document vertices
			if (!namesOfDocs.contains(pairs.getKey())){
				if (pairs.getValue().getNum() == 1){
					//we have a unique word
					solowords.add(pairs.getKey());
				}
			}
		}
		
		//add all words to our arrayList
		words.addAll(solowords);
		
		//sort alphabetically
		java.util.Collections.sort(words);
		
		return words;
	}

	/**
	 * 
	 * @return returns the words (out of all word types) that only occur in single documents
	 */
	public Double propnOfWordsInSingleDocs() {
		return (double) listOfWordsInSingleDocs().size() / numWordTypes();
	}
	
	/**
	 * 
	 * @return returns the most frequent word if there is more than one with maximum frequency, 
	 * return the first alphabetically
	 */
	public String mostFreqWordToken() {
		//storing the most frequent word
		String word = "";
		
		gIt = m.entrySet().iterator();
		
		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			
			//skip over document names
			if (!namesOfDocs.contains(pairs.getKey())){
				//set the first word
				if (word == ""){
					word = pairs.getKey();
				}
				
				//if the frequency is the same, compare alphabetically
				if (pairs.getValue().getNum() == m.get(word).getNum()){
					//if it precedes, store it
					if (pairs.getKey().compareTo(word) < 0){
						//if key is before current word, store it
						word = pairs.getKey();
					}
				}
				//otherwise just store the greater frequency
				else if (pairs.getValue().getNum() > m.get(word).getNum()){
					word = pairs.getKey();
				}
			}
		}
		
		return word;
	}

	/**
	 * 
	 * @return returns the word that occurs in the largest number of documents if there is more
	 * than one with maximum frequency, return the first alphabetically
	 */
	public String wordInMostDocs() {
		//storing the word used in most documents
		String word = "";
		
		gIt = m.entrySet().iterator();
		
		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			
			//skip over document name vertices
			if (!namesOfDocs.contains(pairs.getKey())){
				//set the first word
				if (word == ""){
					word = pairs.getKey();
				}
				
				//if the frequency is the same, compare alphabetically
				if (pairs.getValue().getAdjs().size() == m.get(word).getAdjs().size()){
					if (pairs.getKey().compareTo(word) < 0){
						//if key is before current word, store it
						word = pairs.getKey();
					}
				}
				//otherwise just store the greater frequency
				else if (pairs.getValue().getAdjs().size() > m.get(word).getAdjs().size()){
					word = pairs.getKey();
				}
			}
		}
		
		return word;
	}
	
	/*
	 * END: required functions
	 */
	
	/*
	 * START: suggested functions
	 */
	
	public Vertex getVertex(String s, String t) {
		// Used for accessing vertex to e.g. add neighbours
		// t should be either "word" or "doc"
		
		// TODO
		return null;
	}
	
	public NavigableSet<String> getVertexSet(String t) {
		// Returns ordered set of all vertices in the graph
		// t should be either "word" or "doc"
		
		// TODO
		return null;
	}
	
	public void addVertex(String s, String t) {
		// Adds a new vertex s to the graph
		// t should be either "word" or "doc"
		
		// TODO
	}
	
	public void deleteVertex(String s, String t) {
		// Deletes a vertex n from the graph
		// t should be either "word" or "doc"
		
		// TODO
		
	}
	public void deleteVertex(String n){
		if (m.containsKey(n)){
			//remove the key from Treemap
			m.remove(n);
			
			//now lets remove it from the list of neighbours
			gIt = m.entrySet().iterator();
			while (gIt.hasNext()){
				Entry<String, Vertex> pairs = gIt.next();
				pairs.getValue().getAdjs().remove(n);
			}
		}
		
	}
	public String getFirstVertexID(String t) {
		// Returns first vertex ID in TreeMap ordering
		// e.g. for starting a traversal
		// t should be either "word" or "doc"
		
		// TODO
		return null;
	}
	
	public boolean containsVertex(String s, String t) {
		// Checks if s is a vertex in the graph
		// t should be either "word" or "doc"
		
		// TODO
		return false;
	}

	public void print() {
		gIt = m.entrySet().iterator();
		
		System.out.println("Number of nodes is " + m.size());
		System.out.println("Number of edges is " + numEdges());

		while (gIt.hasNext()) {
			Entry<String, Vertex> pairs = gIt.next();
			pairs.getValue().print();
		}		
		System.out.println();
	}

	/*
	 * END: suggested functions
	 */
	
	/*
	 * START: given functions
	 */
		
	public void setDefault () {
		// the sample set of edges (word-document pairs) from the specs
		
		Vector<Edge> eList = new Vector<Edge>();
		
		eList.add(new Edge("the","d1"));
		eList.add(new Edge("purple","d1"));
		eList.add(new Edge("and","d1"));		
		eList.add(new Edge("green","d1"));
		eList.add(new Edge("cat","d1"));
		eList.add(new Edge("was","d1"));
		eList.add(new Edge("angry","d1"));
		eList.add(new Edge("cat","d1"));
		eList.add(new Edge("i","d2"));
		eList.add(new Edge("heard","d2"));
		eList.add(new Edge("that","d2"));
		eList.add(new Edge("purple","d2"));
		eList.add(new Edge("and","d2"));		
		eList.add(new Edge("green","d2"));
		eList.add(new Edge("cat","d2"));
		eList.add(new Edge("is","d2"));
		eList.add(new Edge("angry","d2"));
		eList.add(new Edge("and","d2"));		
		eList.add(new Edge("green","d2"));
		eList.add(new Edge("all","d3"));
		eList.add(new Edge("cat","d3"));
		eList.add(new Edge("are","d3"));
		eList.add(new Edge("my","d3"));
		eList.add(new Edge("best","d3"));
		eList.add(new Edge("friend","d3"));
		
		this.setGraph(eList);
	}

	public Vector<Edge> readFromDirectory (String dirInName) throws IOException {
		// reads all documents from directory dirInName
		// returns vector of word-document pairs (e.g. the-d1)

		Vector<Edge> eList = new Vector<Edge>();

		File folder = new File(dirInName);
		for (File fileEntry : folder.listFiles()) {
			if (fileEntry.isFile()) {
				BufferedReader fIn = new BufferedReader(new FileReader(fileEntry));
				String s;
				String w;

				String docFileName = fileEntry.getName(); 
				String docName = docFileName.substring(0, docFileName.lastIndexOf('.'));
						
				while ((s = fIn.readLine()) != null) {
					java.util.StringTokenizer line = new java.util.StringTokenizer(s);
					while (line.hasMoreTokens()) {
						w = line.nextToken();
						eList.add(new Edge(w, docName));
					}
				}
				fIn.close();
			}
		}
		return eList;
	}

	/*
	 * END: given functions
	 */
	
	public static void main(String[] args) {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;

		String inName = "C:\\Users\\Nigel\\Desktop\\in1";
		// replace this with your directory path
		
		try {
			eList = g.readFromDirectory(inName);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		g.print();
	}
}
