
public class Main {
	public static void main(String[] args) {
		
		// Change the below line to use a NaivePlayer or a GreedyPlayer or an OptimalPlayer
		// This is how you can test your different Player classes
		
		//InputPlayer
		Player player1 = new InputPlayer();
		new TaxmanGameOperator(player1);
		
		//NaivePlayer
		Player player2 = new NaivePlayer();
		new TaxmanGameOperator(player2);
		
		//GreedyPlayer
		Player player3 = new GreedyPlayer();
		new TaxmanGameOperator(player3);
		
		//OptimalPlayer
		Player player4 = new OptimalPlayer();
		new TaxmanGameOperator(player4);
	}
}
