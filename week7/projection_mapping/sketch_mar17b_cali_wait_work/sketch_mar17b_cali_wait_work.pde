import processing.serial.*;
Serial myPort; // Create object from Serial class

boolean cali_inprogress, cali_end;
boolean horizontal_comp, vertical_comp;
boolean wait_s=false;
;
int cali_phase;
int final_phase_v, final_phase_h;

int return_pos_h[]=new int[4];
int return_pos_v[]=new int[4];
PVector v_list[]=new PVector [4];

void draw_rect(PVector p1, PVector p2, PVector p3, PVector p4) {
  int lines_num=5;
  line(p1.x, p1.y, p2.x, p2.y);
  line(p2.x, p2.y, p3.x, p3.y);
  line(p3.x, p3.y, p4.x, p4.y);
  line(p4.x, p4.y, p1.x, p1.y);
  for (int i=1;i<=lines_num;i++) {
    line(map(i, 0, lines_num+1, p1.x, p4.x), map(i, 0, lines_num+1, p1.y, p4.y), map(i, 0, lines_num+1, p2.x, p3.x), map(i, 0, lines_num+1, p2.y, p3.y));
    line(map(i, 0, lines_num+1, p1.x, p2.x), map(i, 0, lines_num+1, p1.y, p2.y), map(i, 0, lines_num+1, p4.x, p3.x), map(i, 0, lines_num+1, p4.y, p3.y));
  }
}
//int test_value=0x2aa;

void setup() {
  //  test_value=567;
  String portName = "COM14";
  myPort = new Serial(this, portName, 9600, 'N', 8, 1);
  myPort.bufferUntil('\n');
  size(800, 600);
  for (int i=0;i<4;i++) {
    v_list[i] = new PVector();
  }
  frameRate(10);
}

void draw() {
  noStroke();
  if (!wait_s) {
    if (cali_inprogress) {
      if (cali_phase>=0) {
        if (cali_end) {
          myPort.write('S');
          if (!horizontal_comp) {
            cali_end=false;
            wait_s=true;
          }
          else {
            cali_inprogress=false;
            frameRate(10);
          }
        }
        else {
          if ((cali_phase&1)==0) {
            background(255);
            fill(0);
            noStroke();
            int phase_real=cali_phase>>1;
            if (!horizontal_comp) {
              for (float i=0;i<(1<<phase_real);i++) {
                rect(i*(((float)width)/(1<<phase_real)), 0, ((float)width)/(1<<(phase_real+1)), height);
              }
              if ((1<<phase_real)>=width) {
                cali_end=true;
                final_phase_h=phase_real;
              }
            }
            else {
              for (float i=0;i<(1<<phase_real);i++) {
                rect(0, i*(((float)height)/(1<<phase_real)), width, ((float)height)/(1<<(phase_real+1)));
              }
              if ((1<<phase_real)>=height) {
                cali_end=true;
                final_phase_v=phase_real;
              }
            }
          }
          else {
            myPort.write('G');
            wait_s=true;
          }
        }
      }
      cali_phase++;
    }
    else {
      background(0);
      for (int i=0;i<4;i++) {
        if (horizontal_comp) {
          stroke(20); 
          float h_pos=return_pos_h[i]*((float(width))/(1<<final_phase_h));
          v_list[i].x=h_pos;
          line (h_pos, 0, h_pos, height);
        }
        if (vertical_comp) {
          stroke(20); 
          float v_pos=return_pos_v[i]*((float(height))/(1<<final_phase_v));
          v_list[i].y=v_pos;
          line (0, v_pos, width, v_pos);
        }
      }
      if (horizontal_comp && vertical_comp){
        stroke(255);
        draw_rect(v_list[0], v_list[1], v_list[3], v_list[2]);
      }
    }
  }
  //test=!test;
}

void keyPressed()
{
  if ( key == ' ') {
    frameRate(20);
    cali_inprogress=true;
    cali_end=false;
    cali_phase=0;
    myPort.write('R');
    println("cali");
    horizontal_comp=false;
    vertical_comp=false;
  }
}

void serialEvent(Serial p) {
  String inString = (myPort.readString());

  if (inString.trim().equals("D") || inString.trim().equals("d") ) {
    //println ("GO");
    wait_s=false;
  }
  else {
    try
    {
      String[] raw_data=splitTokens(inString.trim(), ",");
      if (!horizontal_comp) {
        for (int i=0;i<4;i++) {
          return_pos_h[i]=Integer.parseInt(raw_data[i]);
        }
        horizontal_comp=true;
        cali_phase=0;
        myPort.write('R');
      }
      else if (!vertical_comp) {
        for (int i=0;i<4;i++) {
          return_pos_v[i]=Integer.parseInt(raw_data[i]);
        }
        vertical_comp=true;
      }
      wait_s=false;
    }
    catch (NumberFormatException nfe)
    {
      println("NumberFormatException");
    }
    // return_pos=
    print(inString);
  }
}

