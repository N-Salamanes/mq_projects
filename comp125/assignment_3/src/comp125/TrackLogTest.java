package comp125;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.Test;  

public class TrackLogTest {

	@Test
	public void testCreateTrackLogDir() throws IOException {
		// test that we can make a tracklog from a directory full of
		// csv files
		final String directory = "data";
		TrackLog tl = new TrackLog(directory);
		
		// this is rather a weak test but since we can't rely on
		// the order of values a fuller test would be more complex
		// so we'll rely on later tests of sort to verify that
		// all required elements are being read in ok
		assertEquals(22, tl.size());
		
	}

	@Test
	public void testCreateEmptyTrackLog() {
		TrackLog tl = new TrackLog();
		
		assertEquals(0, tl.size());
		
	}
	
	@Test
	public void testToString() {
		//Lets add in some strings which 'should' be found
		String[] sContains = {"bobbin-head.csv", 
				  			  "horsley-park.csv",
				  			  "dundas.csv",
				  			  "heffron.csv",
				  			  "homebush.csv"};
		
		final String directory = "data";
		
		try {
			//create a track log
			TrackLog tl = new TrackLog(directory);
			
			for (int i = 0; i < sContains.length; i++){
				if (tl.toString().contains(sContains[i])){
					assertTrue(true);
				}
				else{
					fail("TrackLog does not contain all strings!");
				}
			}
		}
		catch (IOException e) {
			
		}
	}

	@Test
	public void testSortDistance() {
		final String directory = "data";
		
		try {
			//create a track log
			TrackLog tl = new TrackLog(directory);

			//distance should be in ascending order
			tl.sortDistance();
			
			//go through and see if its in ascending order by checking each element i with i + 1
			for (int i = 0; i < tl.size() - 1; i++){
				if (tl.get(i).getDistance() > tl.get(i + 1).getDistance()){
					//its not in ascending order, fail
					fail("It's not sorted!");
				}
				else{
					assertTrue(true);
				}
			}
		}
		catch (IOException e) {
			
		}
	}

	@Test
	public void testSortTimestamp() {
		final String directory = "data";
		
		try {
			//create a track log
			TrackLog tl = new TrackLog(directory);

			//distance should be in ascending order
			tl.sortTimestamp();
			
			//go through and see if its in ascending order by checking each element i with i + 1
			for (int i = 0; i < tl.size() - 1; i++){
				if (tl.get(i).getTimestamp().compareTo(tl.get(i + 1).getTimestamp()) > 0){
					//its not in ascending order, fail
					fail("It's not sorted!");
				}
				else{
					assertTrue(true);
				}
			}
		}
		catch (IOException e) {
			
		}
		
		
	}

}
