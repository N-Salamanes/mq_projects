//Holds the barrier properties

//Number of dimensions the array holding the barriers should have
final int N_DIMENSIONS = 2;
final int N_BARRIERS = 15;

//Sets this so we dont have magic numbers, all barrier x pos are stored in 0, all y stored in 1
final int BARRIER_X = 0;
final int BARRIER_Y = 1;

//Barrier width and height
float fBarrierWidth;
float fBarrierHeight;

//Our two-dimensions array which holds the positions of all the barriers
float[][] BARRIERS;

//Barrier colours
int iBarrierR;
int iBarrierG;
int iBarrierB;

//The number we are going to seed into the random number generator (this helps randomise the blocks)
int iSeedRandom;

//Holds the amount of barriers are actually food (30% is 4.5, 4 or 5 barriers are food)
int iFood;

//Food colours
int iFoodR;
int iFoodG;
int iFoodB;

//Initially sets up the barriers
void barrierSetup()
{
  fBarrierWidth = BLOCK_WIDTH;
  fBarrierHeight = BLOCK_HEIGHT;

  iBarrierR = 255;
  iBarrierG = 0;
  iBarrierB = 0;

  iFoodR = 0;
  iFoodG = 255;
  iFoodB = 0;

  //Need a random number either 4 or 5. (the last function overload in random() is not included, so put 6 there)
  iFood = (int)random(4, 6);

  //This will help randomise the rand function, seeding the maximum value of int
  iSeedRandom = (int)random(2147483647);

  //Gives our barrier new positions
  barrierRefresh();
}

//Gives the barriers new positions
void barrierRefresh()
{
  //Sets our barriers array size and declares it as new
  BARRIERS = new float[N_DIMENSIONS][N_BARRIERS];

  //Randomises food amount
  iFood = (int)random(4, 6);

  //Gives the barriers position
  for (int i = 0; i < N_BARRIERS; i++)
  {
    //This will control wether a unique barrier is created
    boolean bSet = false;

    //While a unique number has not been generated
    while (bSet == false)
    {
      //This checks wether the x and y co-ordinates have been already generated
      boolean bFoundXY = false;

      //X between 4 and BLOCKS_TO_MOVE so that blocks won't spawn at the very left of the screen, give it a bit of buffer
      float fXrandom = (int)random(4, BLOCK_TO_MOVE);
      //Y between 0 and BLOCK_LANES so that blocks can spawn from top to bottom
      float fYrandom = (int)random(0, BLOCK_LANES);

      //Check to see if our newly generated numbers have already been put in the array
      for (int j = 0; j < BARRIERS[BARRIER_X].length; j++)
      {
        //if X and Y are found in the same block
        if ((BARRIERS[BARRIER_X][j] == fXrandom) && (BARRIERS[BARRIER_Y][j] == fYrandom))
        {
          //Newly random numbers are not unique this time
          bFoundXY = true;

          //increment random seed and seed it (helps randomise the blocks)
          iSeedRandom++;
          randomSeed(iSeedRandom);
        }
      }

      //If our number has not been found in the array, put it into our array
      if (bFoundXY == false)
      {
        //Set our current random numbers into our barriers array
        BARRIERS[BARRIER_X][i] = fXrandom;
        BARRIERS[BARRIER_Y][i] = fYrandom;

        //set bSet to true so we can move onto generating the next barrier positions
        bSet = true;
      }
    }
  }
  
  //Once we have generated unique barriers lets multiply them by the block dimensions
  //We need to do this because the random X and Y co-ordinates are generated from the BLOCK_TO_MOVE and BLOCK_LANES
  //Which makes this more generic programming and scales if the screen size or lanes were to be changed
  for (int i = 0; i < N_BARRIERS; i++)
  {
    BARRIERS[BARRIER_X][i] *= fBarrierWidth;
    BARRIERS[BARRIER_Y][i] *= fBarrierHeight;
  }
}

//Draws the barrier
void barrierDraw()
{

  //No border around the barriers
  noStroke();

  //Draw the barriers
  for (int i = 0; i < N_BARRIERS; i++)
  {
    //The colour of our barriers
    fill(iBarrierR, iBarrierB, iBarrierG);

    //If the number of block is in our food range, make it green
    if (i < iFood)
    {
      fill(iFoodR, iFoodG, iFoodB);
    }

    //Draw the barrier
    rect(BARRIERS[BARRIER_X][i], BARRIERS[BARRIER_Y][i], fBarrierWidth, fBarrierHeight);
  }
}

