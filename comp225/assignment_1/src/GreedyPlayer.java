import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;

/**
 * GreedyPlayer derived from Player.
 * The computer will play the role of the player.
 * This algorithm will choose the highest number with the lowest amount of
 * divisors.
 * @author Nigel
 *
 */
public class GreedyPlayer implements Player {

	@Override
	public int chooseNum(TreeSet<Integer> avail) {

		Map<Integer, Integer> divisorCount = new HashMap<Integer,Integer>();

		//Count how many divisors each number has
		for (int i : avail){
			for (int j : avail){
				//We cant have it divide by itself or anything smaller 
				if (i <= j){
					break;
				}
				
				//We have found a divisor
				if (i % j == 0){
					if (divisorCount.containsKey(i)){
						//It already has some divisors
						divisorCount.put(i, divisorCount.get(i) + 1);
					}
					else{
						//First divisor found for key, add it to our map
						divisorCount.put(i, 1);
					}
				}
			}
		}
		
		int lowestValue = 0;
		int highestKey = 0;
		//Find the lowest amount of divisors
		for (int i = avail.size(); i > 0; i--){
			if (divisorCount.containsValue(i)){
				lowestValue = i;
			}
		}
		//Find the highest number with the lowest amount of divisors
		for (int i : divisorCount.keySet()){
			if (divisorCount.get(i) == lowestValue){
				if (i > highestKey){
					highestKey = i;
				}
			}
		}
		
		//Return the highest number with the lowest amount of divisors
		return highestKey;
	}
}
