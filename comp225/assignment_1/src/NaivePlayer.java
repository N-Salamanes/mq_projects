import java.util.Iterator;
import java.util.TreeSet;

/**
 * NaivePlayer derived from interface: Player.
 * The computer will play the role of the player.  Using this strategy,
 * the highest available number will always be chosen.  This will repeat till
 * the game is over.
 * @author Nigel
 *
 */
public class NaivePlayer implements Player {
		
	//TreeSet which contains the previously chosen numbers
	TreeSet<Integer> prevChosen = new TreeSet<Integer>();
	
	@Override
	public int chooseNum(TreeSet<Integer> avail) {
		// Implement a Naive strategy for choosing which number the
		// player will take. return which number you choose for this turn.
		
		//Go through the available choices in descending order (so we start at the largest number)
		Iterator<Integer> iter = avail.descendingIterator();
		
		int i = iter.next();
		
		//Find a number which we previous have not chosen yet
		while(prevChosen.contains(i)){
			i = iter.next();
		}
		
		//Add our chosen number to the list of chosen numbers
		prevChosen.add(i);
		
		//Return the chosen number
		return i;
	}
}
