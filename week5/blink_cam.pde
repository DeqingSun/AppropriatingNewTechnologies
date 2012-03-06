import processing.serial.*;
import processing.video.*;

Capture cam;
boolean take_pic=false;
boolean en_take_pic=false;

Serial myPort;        // The serial port
int xPos = 320;         // horizontal position of the graph
int last_value=999;
int fall_accu=0;
int fall_accu_last=0;
int rise_accu=0;

int capture_count=0;

PImage last_img;

void setup () {
  size(640, 240);        
  frameRate(15);
  // List all the available serial ports

  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, "COM14", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  String[] cameras = Capture.list();

  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } 
  else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(cameras[i]);
    }
  }
  cam = new Capture(this, 640, 480, cameras[0]);
  cam.start();
  background(0);
}

void draw () {
  if (cam.available() == true) {
    cam.read();
    image(cam, 0, 0, 320, 240);
    if (take_pic) {
     // cam.save(capture_count+".jpg");
      last_img.save(capture_count+".jpg");
      capture_count++;
      //  if (i==0) {
      take_pic=false;
      //  }
    }
  }
  PImage image_pass=cam;
  try{
  last_img=(PImage) image_pass.clone();
  }catch(CloneNotSupportedException e){
    
  }
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    int inByte = int(inString); 
    float disp_value = map(inByte, 0, 1023, 0, height);
    if (last_value-inByte>=2) {
      fall_accu+=1;
      rise_accu=0;
    }
    if (last_value-inByte<=-2) {
      fall_accu=0;
      rise_accu=+1;
    }
    if (fall_accu_last>3 && fall_accu==0) {
      stroke(255, 0, 0);
      line(xPos, 0, xPos, height - disp_value);
      if (en_take_pic){
        take_pic=true;
      }
    }

    fall_accu_last=fall_accu;

    last_value=inByte;

    // draw the line:
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - disp_value);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 320;
      fill(0);
      noStroke();
      rect(320, 0, 320, 240);
      background(0);
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }
  }
}

void keyPressed() {
  if (key == ' ') {
    en_take_pic=true;
  }
}

