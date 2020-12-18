//Holds the fish properties

//Fish width/height
float fFishWidth;
float fFishHeight;

//Fish x and y coordinates
float fFishPosX;
float fFishPosY;

//Fish colour components
int iFishR;
int iFishG;
int iFishB;

//Eye position & Eye diameter
float fEyePosX;
float fEyePosY;
float fEyeDiameter;

//Eye colour components
int iFishEyeR;
int iFishEyeG;
int iFishEyeB;

//The speed at which the fish should swim across the screen
float fFishVelocityX;

//Function to set up the fish
void fishSetup()
{
  //Change this later (temporary position of the fish)
  fFishPosX = BLOCK_WIDTH * 2;
  fFishPosY = BLOCK_HEIGHT * 1;

  fFishHeight = BLOCK_HEIGHT;
  fFishWidth = BLOCK_WIDTH;

  iFishR = 0;
  iFishG = 0;
  iFishB = 255;

  fEyePosX = fFishPosX + (fFishWidth / 2.0f);
  fEyePosY = fFishPosY + (fFishHeight / 2.0f);
  fEyeDiameter = 10.0f;

  iFishEyeR = 0;
  iFishEyeG = 255;
  iFishEyeB = 0;

  fFishVelocityX = 2.0f;
}

void fishReset()
{
  //Puts the fishes x position back to 0 (keeping y the same)
  fFishPosX = 0.0f;

  //Give barriers new positions
  barrierRefresh();
}

//Captures the user input
void fishInput()
{
  if (key == CODED)
  {
    if (keyCode == UP)
    {
      //If UP key is pressed move the fish UP the screen if the fish will not go above the screen
      if (fFishPosY > 0)
      {
        fFishPosY -= fFishHeight;
      }
    }
    if (keyCode == DOWN)
    {
      //if DOWN key is pressed move the fish DOWN the screen if the fish will not go below the screen
      if (fFishPosY + fFishHeight < iScreenY)
      {
        fFishPosY += fFishHeight;
      }
    }
  }
}

//Function to update the fish
void fishUpdate()
{
  //Makes the fish swim across the screen (the x-axis)
  fFishPosX += fFishVelocityX;

  //Checks to see if the fish has reached the end of the screen, if so restart it
  //Including the fFishWidth so that the spiky tail is included
  if (fFishPosX - fFishWidth > iScreenX)
  {
    //Calls the fish reset function
    fishReset();
    
    //Add points to our score since we made it to the right of the screen without hitting barriers
    scoreAdd(3);
  }

  //Updates the fish eye position
  fEyePosX = fFishPosX + (fFishWidth / 2.0f);
  fEyePosY = fFishPosY + (fFishHeight / 2.0f);
}

//Function to draw the fish
void fishDraw()
{
  //Makes the next few objects have no stroke
  noStroke();

  //Draw the body of the fish
  fill(iFishR, iFishG, iFishB);
  rect(fFishPosX, fFishPosY, fFishWidth, fFishHeight);

  //Draw the eye of the fish
  fill(iFishEyeR, iFishEyeG, iFishEyeB);
  ellipse(fEyePosX, fEyePosY, fEyeDiameter, fEyeDiameter);

  //Bring back the stroke so we can draw the lines
  stroke(0);

  //Draw the fishes tail
  for (float fIncrement = fFishPosY; fIncrement <= fFishPosY + fFishHeight; fIncrement += (fFishHeight / 4.0f))
  {
    line(fFishPosX - fFishWidth, fIncrement, fFishPosX, fFishPosY + (fFishHeight / 2.0f));
  }
}

