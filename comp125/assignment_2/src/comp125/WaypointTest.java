package comp125;

import static org.junit.Assert.*;

import org.junit.Test;

public class WaypointTest {

    
    @Test
    public void test_create_waypoint_from_string() throws GPSException {
        String line = "2014-08-22T20:18:44Z,-33.7940910,151.0470420,-2.2";
        
        Waypoint wp = new Waypoint(line);
        
        /* validate using the getter methods */
        assertEquals("2014-08-22T20:18:44Z", wp.getTimestamp());
        assertEquals(-33.7940910, wp.getLatitude(), 0.001);
        assertEquals(151.0470420, wp.getLongitude(), 0.001);
        assertEquals(-2.2, wp.getElevation(), 0.001);

    }
    
    /* 
     * Test that trying to create a waypoint with a badly formed line
     * throws the right kind of exception
     */
    @Test(expected=GPSException.class)
    public void test_create_waypoint_from_string_bad() throws GPSException {
        String line = "2014-08-22T20:18:44Z, a number, what!,  -2.2";
        
        @SuppressWarnings("unused")
        Waypoint wp = new Waypoint(line);
    }

    
    /*
     * Test the calculation of distance between two waypoints
     */
    @Test
    public void test_calcuate_distance() throws GPSException {
        Waypoint wp1 = new Waypoint("2014-08-22T20:22:28Z, -33.7972680, 151.0454740,  -28.6");
        Waypoint wp2 = new Waypoint("2014-08-22T20:22:29Z, -33.7973140, 151.0455580,  -29.2");
        Waypoint wp3 = new Waypoint("2014-08-22T20:40:43Z, -33.8311800, 151.0709390,  -61.8");
        
        // distance to itself is zero
        assertEquals(0.0, wp1.distanceTo(wp1), 0.001);
        
        // two close together waypoints
        assertEquals(0.009, wp1.distanceTo(wp2), 0.001);
        assertEquals(0.009, wp2.distanceTo(wp1), 0.001);
        
        // two further away
        assertEquals(4.446, wp1.distanceTo(wp3), 0.001);
        
    }
}
