package comp125;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.Test;

public class TrackTest {

    /* 
     * Create a track from a csv file contianing waypoints
     */
    @Test
    public void test_create_track_waypoint_csv() throws IOException, GPSException {
        
        Track tr = new Track("data/small-sample.csv");
        assertEquals(20, tr.size());
        
        /* longer track is truncated to 1000 waypoints */
        Track tr2 = new Track("data/sample.csv");
        assertEquals(1000, tr2.size());
    }
    
    @Test(expected=GPSException.class)
    public void test_create_track_waypoint_csv_bad() throws GPSException, IOException {
        
        Track tr = new Track("data/badly-formed.csv");
        
    }
    
    @Test(expected=IOException.class)
    public void test_create_track_waypoint_no_file() throws GPSException, IOException {
        
        Track tr = new Track("data/file-not-there.txt");
        
    }
    
    @Test
    public void test_track_getters() throws IOException, GPSException {
        
        Track tr = new Track("data/small-sample.csv");
        assertEquals("data/small-sample.csv", tr.getFilename());
        assertEquals(0.2043, tr.getDistance(), 0.001);
        assertEquals("2014-08-22T20:22:26Z", tr.getTimestamp());
        assertEquals(2.6, tr.getElevationGain(), 0.001);
        
        
        Track tr2 = new Track("data/sample.csv");
        assertEquals("data/sample.csv", tr2.getFilename());
        assertEquals(16.605, tr2.getDistance(), 0.001);
        assertEquals("2014-08-22T20:18:23Z", tr2.getTimestamp());
        assertEquals(122.4, tr2.getElevationGain(), 0.001);
        
    }
    
    @Test
    public void test_add_to_track() throws  IOException, GPSException  {
        
        Track tr = new Track("data/small-sample.csv");
        assertEquals(20, tr.size());
        
        Waypoint wp =  new Waypoint("2014-08-22T20:22:28Z, -33.7972680, 151.0454740,  -28.6");
        tr.add(wp);
        assertEquals(21, tr.size());
    }
    
    @Test
    public void test_closest_to() throws IOException, GPSException {
        
        Track tr = new Track("data/small-sample.csv");
        Waypoint wp1 = new Waypoint("2014-08-22T20:22:28Z, -33.7972580, 151.0454540,  -28.6");

        Waypoint wp2 = tr.closestTo(wp1);
        
        assertEquals(-33.7972680, wp2.getLatitude(), 0.00000001);
        assertEquals(151.0454740, wp2.getLongitude(), 0.00000001);

    }
    
    @Test
    public void test_to_string() throws IOException, GPSException {
        
        Track tr = new Track("data/small-sample.csv");

        String description = tr.toString();
        
        assertTrue(description.contains("data/small-sample.csv"));     /* filename */
        assertTrue(description.contains("0.204"));				  /* distance */
        assertTrue(description.contains("2.6"));				  /* elevation gain */
        assertTrue(description.contains("2014-08-22T20:22:26Z")); /* date */
    }  
    
    
    
}
