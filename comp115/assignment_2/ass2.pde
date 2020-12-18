//Nigel Salamanes
//Date 05/05/2014
//Assignment Two: Swimmy Fish Part Two
//Fish swims across the screen.  Click to make new fish appear
//Control fish using UP/DOWN, obeys 30% of the time
//Animated Fish, Scoring, Placement, Bubbles!

//External declarations//

int iScreenX = 500; //Screen width
int iScreenY = 400; //screen height

float fFishPosX; //fish position x
float fFishPosY; //fish position y
float fFishWidth; //fish width
float fFishHeight; //fish height

float fFishEyePosX; //fish eye position x
float fFishEyePosY; //fish eye position y
float fFishEyeWidth; //fish eye width
float fFishEyeHeight; //fish eye height

float fFishTailX1, fFishTailY1, //fishes tail coordinates, 3 points x,y
fFishTailX2, fFishTailY2, 
fFishTailX3, fFishTailY3;


float fChangeYThreshold = 0.0f; //this is the amount that will change the fishes Y position up/down
float   fFishPositionYChange; //this will change the fishes position up or down
boolean bFishSwitch; //switch to control whether or not to draw fish or not
float fFishTailIncrement = 0.0f; //how much should the left two points of the fin increment by (animation)
boolean bFishTailSwitch = true; //controls wether to animate the left two points towards the right or towards the left

//variables to hold the colour of the fish and their increments
float fRed;
float fRedIncrement;
float fGreen;
float fGreenIncrement;
float fBlue;
float fBlueIncrement;

//variables to hold the colour of the fin and their increments
float fFinRed;
float fFinRedIncrement;
float fFinGreen;
float fFinGreenIncrement;
float fFinBlue;
float fFinBlueIncrement;

boolean bBubbles; //switch which controls if we currently are drawing bubbles on the screen

float fBubblesAmount; //the amount of bubbles which are generated at a time
float fBubblesPosX; //the position of the bubbles (the lowest one)
float fBubblesPosY; //the position of the bubbles (the lowest one)


//holds the score
int iScore;

//initialise function
void setup()
{
  //Set the screen size
  size(iScreenX, iScreenY);

  //sets our switch to true so that it will execute straight away
  bFishSwitch = true;

  //initialises and sets dimensions and position for fish body
  fFishPosX = 0.0f;
  fFishPosY = iScreenY / 2.0f;
  fFishWidth = 70.0f;
  fFishHeight = 45.0f;

  //initialises and sets dimensions and position for fish eye
  fFishEyePosX = 0.0f;
  fFishEyePosY = 0.0f;
  fFishEyeWidth = 5.0f;
  fFishEyeHeight = 5.0f;

  //initialises and sets dimensions and position for fish tail
  fFishTailX1 = fFishPosX - (fFishWidth / 4.0f) - (fFishWidth / 10.0f);
  fFishTailY1 = fFishPosY;
  fFishTailX2 = fFishTailX1 - 20.0f;
  fFishTailY2 = fFishTailY1 + 15.0f;
  fFishTailX3 = fFishTailX1 - 20.0f;
  fFishTailY3 = fFishTailY1 - 15.0f;

  //initalises and sets colours and increments for fish
  fRed = random(0, 255);
  fGreen = random(0, 255);
  fBlue = random(0, 255);
  fRedIncrement = 1.0f;
  fGreenIncrement = 1.0f;
  fBlueIncrement = 1.0f;

  //initalises and sets colours and increments for fin
  fFinRed = random(0, 255);
  fFinGreen = random(0, 255);
  fFinBlue = random(0, 255);
  fFinRedIncrement = 1.0f;
  fFinGreenIncrement = 1.0f;
  fFinBlueIncrement = 1.0f;

  //initalises and sets the variable for changing the fish position
  fFishPositionYChange = 0.0f;

  //initalises the score which sets it to 0
  iScore = 0;

  bBubbles = false;
}


//continuous draw loop
void draw()
{
  //set the background colour
  background(0, 191, 255);

  //draws the barrier on the right hand side and checks collision
  Barrier();

  //displays the score
  DisplayScore();

  //condition statement to see if we are going to be drawing a fish or not. execute if true
  if (bFishSwitch == true)
  {
    FishCheckBoundary();
    FishMovement();
    FishAnimate();
    FishDraw();
    Bubbles();
  }

  //call these functions so that the bubbles will move and draw
  BubblesMovement();
  BubblesDraw();
}


//function when mouse is pressed and released
void mousePressed()
{
  //if the mouse is pressed on the left side of the screen
  if (mouseX < (iScreenX / 2))
  {
    //set our switch to true which allows the fish to be created, drawn and updated
    bFishSwitch = true;

    //stores our mouse x and y positions and sets it for the initial position for our fish
    fFishPosX = mouseX;
    fFishPosY = mouseY;

    //gives the new fish new colours
    fRed = random(0, 255);
    fGreen = random(0, 255);
    fBlue = random(0, 255);
  }
}



//function when key is pressed
void keyPressed()
{
  //this will generate a number between 0 and 100.  this will determine wether 30% of the time to disobey going up if up is pressed and vice verca
  float iRandom = random(0, 100);

  if (key == CODED)
  {
    //if up is pressed
    if (keyCode == UP)
    {
      //if our random number generated is over 30
      if (iRandom > 30)
      {
        fChangeYThreshold = random(20, 59);
      }
      //else go opposite
      else
      {
        fChangeYThreshold = -random(20, 59);
      }
    }
    //if down is pressed
    if (keyCode == DOWN)
    {
      //if our random number generate is over 30
      if (iRandom > 30)
      {
        fChangeYThreshold = -random(20, 59);
      }
      //else go opposite
      else
      {
        fChangeYThreshold = random(20, 59);
      }
    }
  }
}


//function to display score
void DisplayScore()
{
  //draws score to the screen at x = 50, y = 50 using iScore variable
  text(iScore, 50, 50);
}

//checks to see if the fish is off the screen
void FishCheckBoundary()
{
  //if the fish is off the screen, disable our fish switch
  if (fFishPosX > iScreenX + fFishWidth)
  {
    //increase the score
    iScore++;
    //set drawing the fish to false
    bFishSwitch = false;
  }
}

//updates the movement of the fish
void FishMovement()
{
  //make the fish swim towards the right, increasing its x axis
  fFishPosX += 1.0f;

  //modify the fish y position depending on if we need to change the y position because of key presses
  fFishPosY += fFishPositionYChange;

  //update the fish eye so it follows with the body
  fFishEyePosX = fFishPosX + (fFishWidth / 4.0f) + (fFishWidth / 10.0f);
  fFishEyePosY = fFishPosY - (fFishHeight / 7.5f);

  //update all the x/y coordinates for the tail. its parented position is based of the center of the fishes body
  // -20.0f is the offset from first point in triangle.  +/- 15.0f is above/below offset from the first point in triangle
  fFishTailX1 = fFishPosX - (fFishWidth / 4.0f) - (fFishWidth / 10.0f);
  fFishTailY1 = fFishPosY;
  fFishTailX2 = fFishTailX1 - 25.0f + fFishTailIncrement;
  fFishTailY2 = fFishTailY1 + 15.0f;
  fFishTailX3 = fFishTailX1 - 25.0f + fFishTailIncrement;
  fFishTailY3 = fFishTailY1 - 15.0f;


  //this will modify the fishes y axis up or down depending on if a key has been pressed and the threshold has not been met
  if (fChangeYThreshold > 0.0f)
  {
    //sets the Y change to -1.0f so it will go up
    fFishPositionYChange = -1.0f;
    //takes 1.0f off the threshold so we know how much further we have to move the fish
    fChangeYThreshold -= 1.0f;
    //if the threshold has been met, set everything back to 0
    if (fChangeYThreshold < 0.0f)
    {
      fFishPositionYChange = 0.0f;
      fChangeYThreshold = 0.0f;
    }
  }
  if (fChangeYThreshold < 0.0f)
  {
    //sets the Y change to 1.0f so it will go down
    fFishPositionYChange = 1.0f;
    //takes 1.0f off the threshold so we know how much further we have to move the fish
    fChangeYThreshold += 1.0f;
    //if the threshold has been met, set everything back to 0
    if (fChangeYThreshold > 0.0f)
    {
      fFishPositionYChange = 0.0f;
      fChangeYThreshold = 0.0f;
    }
  }
}



//function which animates the fish tail
void FishAnimate()
{
  //if bFishTailSwitch is true, increment the two left points in the triangle towards the right
  if (bFishTailSwitch == true)
  {
    fFishTailIncrement += 1.0f;

    //if its reached our threshold, set our boolean to false
    if (fFishTailIncrement >= 10.0f)
    {
      bFishTailSwitch = false;
    }
  }
  else
  {
    //decrement the two left points in the triangle towards the left
    fFishTailIncrement -= 1.0f;

    //if its reached our threshold switch our boolean to true
    if (fFishTailIncrement <= 0.0f)
    {
      bFishTailSwitch = true;
    }
  }

//animates red body portion
  fRed += fRedIncrement;
  if (fRed > 255)
  {
    fRedIncrement = -1.0f;
  }
  if (fRed < 0)
  {
    fRedIncrement = 1.0f;
  }

  //animates green body portion
  fGreen += fGreenIncrement;
  if (fGreen > 255)
  {
    fGreenIncrement = -1.0f;
  }
  if (fRed < 0)
  {
    fGreenIncrement = 1.0f;
  }

  //animates blue body portion
  fBlue += fBlueIncrement;
  if (fBlue > 255)
  {
    fBlueIncrement = -1.0f;
  }
  if (fBlue < 0)
  {
    fBlueIncrement = 1.0f;
  }

  //animates red fin portion
  fFinRed += fFinRedIncrement;
  if (fFinRed > 255)
  {
    fFinRedIncrement = -1.0f;
  }
  if (fFinRed < 0)
  {
    fFinRedIncrement = 1.0f;
  }

  //animates green portion
  fFinGreen += fFinGreenIncrement;
  if (fFinGreen > 255)
  {
    fFinGreenIncrement = -1.0f;
  }
  if (fFinRed < 0)
  {
    fFinGreenIncrement = 1.0f;
  }

  //animates blue portion
  fFinBlue += fFinBlueIncrement;
  if (fFinBlue > 255)
  {
    fFinBlueIncrement = -1.0f;
  }
  if (fFinBlue < 0)
  {
    fFinBlueIncrement = 1.0f;
  }
}


//draw the fish to the screen
void FishDraw()
{
  //set no stroke
  noStroke();

  //set the fill colour of the fin
  fill(fFinRed, fFinGreen, fFinBlue);

  //draw the tail of the fish
  triangle(fFishTailX1, fFishTailY1, fFishTailX2, fFishTailY2, fFishTailX3, fFishTailY3);

  //set the fill colour of the body
  fill(fRed, fGreen, fBlue);

  //draw the main body of the fish
  ellipse(fFishPosX, fFishPosY, fFishWidth, fFishHeight);

  //change our fill colour for the eye
  fill(0, 0, 0);

  //draw the eye of the fish
  ellipse(fFishEyePosX, fFishEyePosY, fFishEyeWidth, fFishEyeHeight);
}

void Barrier()
{
  //sets the variables for the barriers hit boxes
  float fTopBarrierBottom = 150.0f;
  float fBottomBarrierTop = 250.0f;
  float iBarrierThickness = 25.0f;

  //set the colour of the barrier
  fill(#483D8B);

  //sets the "left side" of the barrier
  float fBarrierStart = iScreenX - iBarrierThickness;

  //draw the barriers
  rect(fBarrierStart, 0, iScreenX, fTopBarrierBottom); //150 down the screen.  Screen Size 400, leave 100 pixel gap
  rect(fBarrierStart, fBottomBarrierTop, iScreenX, iScreenY); //250 down the screen. leaving 100 pixel gap

  //this will hold the position for the right side of the fish
  float fFishRightTip = fFishPosX + (fFishWidth/2);
  //this will hold the position of the top side of the fish
  float fFishTopTip = fFishPosY - (fFishHeight/2);
  //this will hold the position of the bottom side of the fish
  float fFishBottomTip = fFishPosY + (fFishHeight/2);

  //if the right side of the fish is within the left side of the barrier
  if (fFishRightTip > fBarrierStart)
  {
    //if its within the rest of the barrier sides we are checking
    //if so, minus the score and disable the fish
    if (fFishTopTip < fTopBarrierBottom)
    {
      if (bFishSwitch == true)
      {
        iScore--;
        bFishSwitch = false;
      }
    }
    if (fFishBottomTip > fBottomBarrierTop)
    {
      if (bFishSwitch == true)
      {
        iScore--;
        bFishSwitch = false;
      }
    }
  }
}




//initial check and setting up of bubbles
void Bubbles()
{
  //if bubbles = false, we have no bubbles on screen.  lets make some
  if (bBubbles == false)
  {
    //the amount of bubbles to generate
    fBubblesAmount = random(1, 4);

    //where to generate the bubbles x and y
    fBubblesPosX = fFishPosX + (fFishWidth / 2);
    fBubblesPosY = fFishPosY;

    //switches our boolean to true which means we will draw bubbles on the screen
    bBubbles = true;
  }
}

//movement of the bubbles
void BubblesMovement()
{
  //make the position of the bubbles so it goes up the screen
  fBubblesPosY -= 1.0f;

  //check to see if the bubbles have reached the top of the screen, if so then switch our control to false (so we can generate new ones)
  if (fBubblesPosY < 0)
  {
    bBubbles = false;
  }
}

//draws the bubbles
void BubblesDraw()
{
  //iteration of our bubbles, we set this to 0 and increments in our while loop as we draw each bubble
  int iBubblesCount = 0;

  //diameter of the bubbles
  float fBubblesDiameter = 10.0f;
  //gap between each bubble
  float fBubblesGap = 15.0f;

  //sets the fill colour and opacity
  fill(#0000FF, 100);

  //if our control is set to true lets draw bubbles
  if (bBubbles == true)
  {
    //while our bubblescount (the bubble we are currently drawing) < the amount of bubbles we want (which is randomly generated)
    while ( iBubblesCount < fBubblesAmount)
    {
      //draw the bubbles 
      ellipse(fBubblesPosX, fBubblesPosY - (iBubblesCount * fBubblesGap), fBubblesDiameter, fBubblesDiameter);

      //increase our count, it will loop again until the condition has not been met (finished drawing all the bubbles)
      iBubblesCount++;
    }
  }
}

