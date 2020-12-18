
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
  int count = 0;

  iterate current over others
    if current:alive then count = count+1;

  if alive && (count < 2 || count > 3) then alive = false;
  if !alive && count == 3 then alive = true;
}

int black = 0;
int white = 0xFFFFFF;

mapper {
  if alive then return(white); else return(black);
}

function glider(int row, int col) {
  cell [row, col]
    iterate nbr over [N, E, SW, S, SE]
      nbr:alive = true;
}

initialiser one_glider {
  glider(height / 2, width / 2);
}

initialiser four_gliders {
  glider(height / 4, width / 4);
  glider(3 * height / 4, width / 4);
  glider(height / 4, 3 * width / 4);
  glider(3 * height / 4, 3 * width / 4);
}

initialiser glider_gun {
  cell [100, 124] alive = true;
  cell [101, 122] alive = true;
  cell [101, 124] alive = true;
  cell [102, 112] alive = true;
  cell [102, 113] alive = true;
  cell [102, 120] alive = true;
  cell [102, 121] alive = true;
  cell [102, 134] alive = true;
  cell [102, 135] alive = true;
  cell [103, 111] alive = true;
  cell [103, 115] alive = true;
  cell [103, 120] alive = true;
  cell [103, 121] alive = true;
  cell [103, 134] alive = true;
  cell [103, 135] alive = true;
  cell [104, 100] alive = true;
  cell [104, 101] alive = true;
  cell [104, 110] alive = true;
  cell [104, 116] alive = true;
  cell [104, 120] alive = true;
  cell [104, 121] alive = true;
  cell [105, 100] alive = true;
  cell [105, 101] alive = true;
  cell [105, 110] alive = true;
  cell [105, 114] alive = true;
  cell [105, 116] alive = true;
  cell [105, 117] alive = true;
  cell [105, 122] alive = true;
  cell [105, 124] alive = true;
  cell [106, 110] alive = true;
  cell [106, 116] alive = true;
  cell [106, 124] alive = true;
  cell [107, 111] alive = true;
  cell [107, 115] alive = true;
  cell [108, 112] alive = true;
  cell [108, 113] alive = true;
}

initialiser infinite_a {
  cell [100, 106] alive = true;
  cell [101, 104] alive = true;
  cell [101, 106] alive = true;
  cell [101, 107] alive = true;
  cell [102, 104] alive = true;
  cell [102, 106] alive = true;
  cell [103, 104] alive = true;
  cell [104, 102] alive = true;
  cell [105, 100] alive = true;
  cell [105, 102] alive = true;
}

initialiser acorn {
  cell [100, 101] alive = true;
  cell [101, 103] alive = true;
  cell [102, 100] alive = true;
  cell [102, 101] alive = true;
  cell [102, 104] alive = true;
  cell [102, 105] alive = true;
  cell [102, 106] alive = true;
}

initialiser random {
  for i = 0 to (width-1) {
    for j = 0 to (height-1) {
      cell [i, j] {
        if (rnd(2) == 1) then
          alive = true;
        else
          alive = false;
      }
    }
  }
}
