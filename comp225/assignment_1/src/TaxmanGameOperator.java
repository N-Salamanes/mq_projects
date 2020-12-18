import java.util.Scanner;


public class TaxmanGameOperator {
	/** TaxmanGameOperator receives a Player object, which will be used to
	    make the decisions in the game. It runs the whole game from start to end,
	    displaying progress as it goes.
	**/
	public TaxmanGameOperator(Player player) {
		
		// get upper limit from system input
		int upper = 0;
		boolean valid = false;
		
		Scanner in = new Scanner(System.in);

		while (valid == false){
			System.out.print("What is the upper limit? (Must choose number >= 2)");
			
			if (in.hasNextInt() == true){
				upper = in.nextInt();
				if (upper >= 2){
					valid = true;
				}
			}
			else{
				in.next();
			}
		}
		
		// create the taxman object
		Taxman txm = new Taxman(upper);
		
		// keep getting and applying choices until the game is over
		while (!txm.gameOver()) {
			int chosen = player.chooseNum(txm.getAvailableNumbers());
			System.out.println("\nPlayer chose " + chosen);
			if (!txm.choose(chosen))
				System.out.println("Invalid choice!");
			txm.displayGameState();
		}
		
	}
}
