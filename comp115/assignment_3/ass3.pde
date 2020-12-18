//Nigel Salamanes
//Assignment 03

//The water components
int iWaterR = 89;
int iWaterG = 181;
int iWaterB = 188;

void setup()
{
  //Set up the window
  size(iScreenX, iScreenY);
  
  //Set up the scoring system
  scoreSetup();
  
  //Set up the barrier
  barrierSetup();
  
  //Set up the fish
  fishSetup();
}

void draw()
{
  //Draws the background
  background(iWaterR, iWaterG, iWaterB);
  
  barrierDraw();
  
  //Updates the fish
  fishUpdate();
  
  //Checks collision
  checkCollisionBarrier();
  
  //Draws the fish
  fishDraw();
  
  //Draws the score to the screen
  scoreDraw();
}

void keyPressed()
{
  //Calls our fish input function which handles the checks
  fishInput();
}
