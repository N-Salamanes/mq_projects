//Nigel Salamanes
//Date 15/03/2014
//Assignment One: Swimmy Fish Part One
//Fish swims across the screen.  Click to make new fish appear

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

boolean bFishSwitch; //switch to control whether or not to draw fish or not


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
  fFishEyeWidth = 10.0f;
  fFishEyeHeight = 10.0f;

  //initialises and sets dimensions and position for fish tail
  fFishTailX1 = fFishPosX - (fFishWidth / 4.0f) - (fFishWidth / 10.0f);
  fFishTailY1 = fFishPosY;
  fFishTailX2 = fFishTailX1 - 20.0f;
  fFishTailY2 = fFishTailY1 + 15.0f;
  fFishTailX3 = fFishTailX1 - 20.0f;
  fFishTailY3 = fFishTailY1 - 15.0f;
}


//continuous draw loop
void draw()
{
  //set the background colour
  background(0, 191, 255);

  //condition statement to see if we are going to be drawing a fish or not. execute if true
  if (bFishSwitch == true)
  {
    FishCheckBoundary();
    FishMovement();
    FishDraw();
  }
}


//function when mouse is pressed and released
void mousePressed()
{
  //set our switch to true which allows the fish to be created, drawn and updated
  bFishSwitch = true;

  //stores our mouse x and y positions and sets it for the initial position for our fish
  fFishPosX = mouseX;
  fFishPosY = mouseY;
}

//checks to see if the fish is off the screen
void FishCheckBoundary()
{
  //if the fish is off the screen, disable our fish switch
  if (fFishPosX > iScreenX + fFishWidth)
  {
    bFishSwitch = false;
  }
}

//updates the movement of the fish
void FishMovement()
{
  //make the fish swim towards the right, increasing its x axis
  fFishPosX += 1.0f;

  //update the fish eye so it follows with the body
  fFishEyePosX = fFishPosX + (fFishWidth / 4.0f) + (fFishWidth / 10.0f);
  fFishEyePosY = fFishPosY - (fFishHeight / 7.5f);

  //update all the x/y coordinates for the tail. its parented position is based of the center of the fishes body
  fFishTailX1 = fFishPosX - (fFishWidth / 4.0f) - (fFishWidth / 10.0f);
  fFishTailY1 = fFishPosY;
  fFishTailX2 = fFishTailX1 - 20.0f;
  fFishTailY2 = fFishTailY1 + 15.0f;
  fFishTailX3 = fFishTailX1 - 20.0f;
  fFishTailY3 = fFishTailY1 - 15.0f;
}


//draw the fish to the screen
void FishDraw()
{
  //set no stroke
  noStroke();

  //set the fill colour
  fill(255, 165, 0);

  //draw the main body of the fish
  ellipse(fFishPosX, fFishPosY, fFishWidth, fFishHeight);

  //draw the tail of the fish
  triangle(fFishTailX1, fFishTailY1, fFishTailX2, fFishTailY2, fFishTailX3, fFishTailY3);

  //change our fill colour for the eye
  fill(0, 0, 0);

  //draw the eye of the fish
  ellipse(fFishEyePosX, fFishEyePosY, fFishEyeWidth, fFishEyeHeight);
}

