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

initialiser forTest1 {

  for i = 0 to (width-1){
  }
  
  for i = 0 to (height-1){
  
  }
  
}

int black = 0;
int white = 0xFFFFFF;

mapper {
  if alive then return(white); else return(black);
}




