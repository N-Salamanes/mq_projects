// Testing empty for loop translation
//
//
//
//


int width = 200;
int height = 200;
dimension(width cyclic, height);

neighbourhood
  N = [0,1], S = [0,-1], W = [-1,0], E = [1,0],
  NE = [1,1], SE = [1,-1], SW = [-1,-1], NW = [-1,1];

state {
  boolean alive = false;
}

updater {
  
}

initialiser forTestError4 {
  int x = 0;

  for i = j to (height-1){
    x = x + 1;
  }

}

int black = 0;
int white = 0xFFFFFF;

mapper {
  if alive then return(white); else return(black);
}




