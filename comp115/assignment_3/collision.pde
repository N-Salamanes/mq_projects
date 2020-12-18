//Holds collision properties

boolean bSquareCollision(float a_fX1, float a_fY1, float a_fWidth1, float a_fHeight1, 
float a_fX2, float a_fY2, float a_fWidth2, float a_fHeight2)
{
  //If the right side of object 1 is greater than the left side of object 2
  //and
  //If the left side of object 1 is less than the right side of object 2
  if ((a_fX1 + a_fWidth1 > a_fX2) && (a_fX1 < a_fX2 + a_fWidth2)) 
  {
    //The two are within X collision

    //If the top of object 1 is less than the bottom of object 2
    //and
    //If the bottom of object 1 is greater than the top of object 2
    if ((a_fY1 < a_fY2 + a_fHeight2) && (a_fY1 + a_fHeight1 > a_fY2))
    {
      //We have collision!
      return true;
    }
  }

  //Return false;
  return false;
}

void checkCollisionBarrier()
{
  for (int i = 0; i < N_BARRIERS; i++)
  {
    //Call our collision function using the fish and barrier as function overloads
    boolean bHit = bSquareCollision(fFishPosX, fFishPosY, fFishWidth, fFishHeight, BARRIERS[BARRIER_X][i], BARRIERS[BARRIER_Y][i], fBarrierWidth, fBarrierHeight);

    //If we have collided with a block
    if (bHit == true)
    {
      //If it is food
      if (i < iFood)
      {
        //Add one to the score
        scoreAdd(1);

        //Put this barrier off the screen (just so we can't see it and the fish can not run into it (It will come back in barrierRefresh
        BARRIERS[BARRIER_X][i] = -fBarrierWidth;
        BARRIERS[BARRIER_Y][i] = -fBarrierHeight;
      }
      else
      {
        //Must be a barrier!
        //Reset the fish
        fishReset();

        //Take away points since the user hit a barrier
        scoreMinus();
      }
    }
  }
}

