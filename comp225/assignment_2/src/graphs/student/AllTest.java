package graphs.student;

import static org.junit.Assert.*;

import java.io.IOException;
import java.util.Vector;

import org.junit.Test;


public class AllTest {

	String PATH = "C:\\Users\\Nigel\\Desktop\\in1";
	// replace this with your directory path

	@Test
	public void testNumVertices() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(19), g.numVertices());
	}

	@Test
	public void testNumEdges() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(22), g.numEdges());
	}

	@Test
	public void testNumWordTypes() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(16), g.numWordTypes());
	}

	@Test
	public void testNumWordTokens() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(25), g.numWordTokens());
	}

	@Test
	public void testNumTimesWordOccurs() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(4), g.numTimesWordOccurs("cat"));
	}

	@Test
	public void testNumWordTypesInDoc() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(7), g.numWordTypesInDoc("d1"));
	}

	@Test
	public void testNumWordTokensInDoc() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(8), g.numWordTokensInDoc("d1"));
	}

	@Test
	public void testNumDocsWordOccursIn() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(2), g.numDocsWordOccursIn("purple"));
	}

	@Test
	public void testNumTimesWordOccursInDoc() {
		BipartiteGraph g = new BipartiteGraph();
		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		assertEquals(Integer.valueOf(2), g.numTimesWordOccursInDoc("cat", "d1"));
	}

	@Test
	public void testListOfWordsInSingleDocs() {
		BipartiteGraph g = new BipartiteGraph();
		String[] soloWords = {"all", "are", "best", "friend", "heard", "i", "is", "my", "that", "the", "was"};

		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		System.out.println(g.listOfWordsInSingleDocs());
		assertArrayEquals(soloWords, g.listOfWordsInSingleDocs().toArray());
	}

	@Test
	public void testPropnOfWordsInSingleDocs() {
		BipartiteGraph g = new BipartiteGraph();
		Double ans = 0.6875;

		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		System.out.println(g.listOfWordsInSingleDocs());
		assertEquals(ans, g.propnOfWordsInSingleDocs());
	}

	@Test
	public void testMostFreqWordToken() {
		BipartiteGraph g = new BipartiteGraph();

		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		System.out.println(g.mostFreqWordToken());
		assertEquals("cat", g.mostFreqWordToken());
	}

	@Test
	public void testWordInMostDocs() {
		BipartiteGraph g = new BipartiteGraph();

		Vector<Edge> eList;
		try {
			eList = g.readFromDirectory(PATH);
			g.setGraph(eList);
		}
		catch (IOException e) {
			System.out.println("in exception: " + e);
		}
		System.out.println(g.wordInMostDocs());
		assertEquals("cat", g.wordInMostDocs());
	}

}
