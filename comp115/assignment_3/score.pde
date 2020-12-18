//Holds the properties for the score system

//Holds the score which is printed on the screen
int iScore;

//The text colour
int iTextR;
int iTextG;
int iTextB;

//The text co-ordinates
float fTextX;
float fTextY;

//The increment amounts that should be added to the score if either the line or food is collected
int iFishLineAdd;
int iFishFoodAdd;

//Sets up our score
void scoreSetup()
{
  iScore = 0;

  iTextR = 128;
  iTextG = 128;
  iTextB = 128;

  fTextX = 30.0f;
  fTextY = 40.0f;

  iFishLineAdd = 3;
  iFishFoodAdd = 1;
}

//Add to our score
void scoreAdd(int a_iAdd)
{
  iScore += a_iAdd;
}

//Take points away from our score
void scoreMinus()
{
  iScore -= 3;
}

//Draws the score to the screen
void scoreDraw()
{
  //Sets our text size
  textSize(24);

  //Sets the colour of the text
  fill(iTextR, iTextG, iTextB);

  //Displays the text to the screen
  text("Score: " + iScore, fTextX, fTextY);
}

