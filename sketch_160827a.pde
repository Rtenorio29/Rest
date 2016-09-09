import processing.serial.*;
Serial port;
String data;
int sUno, sDos, sTres, gradosX, gradosY, promedioX, promedioY, hipo, angulo;
float hipo2, sUno2, sDos2, sTres3;

void setup() {
  println(Serial.list());
  port = new Serial(this, "COM11", 9600);
  port.bufferUntil('\n');
  
  size(800, 800);
  noSmooth();
  fill(126);
  background(102);
  
}

void draw() {
  strokeWeight(1);
  float bX=map(gradosX, 180, 0, 700, 100);
  float bY=map(gradosY, 0, 180, 700, 100);
  float hipo2=map(hipo, 0, 90, 0, 600);
 float sDos2=map(sDos, -90, 270, 0 , 300);
 float sUno2=map(sUno, -90, 270, 0 , 300);
 float sTres2=map(sTres, -90, 270, 0 , 300);
background(102);
fill(150);
ellipse(400, 400, 600, 600);


noStroke();
  if (hipo < 6) {
  fill(255, 200);
}
if (hipo >= 6) {
  fill(255, 220, 0, 100);
}
  ellipse(400, 400, hipo2, hipo2);
  
  
stroke(50);
  line(400, 400, 659, 250);
  line(400, 400, 141, 250);
  line(100, 400, 700, 400);
  line(400, 400, 400, 700);
  line(250, 659, 550, 141);
  line(550, 659, 250, 141);
stroke(255);
  line(400, 400, 659, 550);
  line(400, 400, 141, 550);
  line(400, 400, 400, 100);
  

fill(100, 127);
  ellipse(400+sTres2*0.866, 400+0.5*sTres2, 30, 30); //sTres
  ellipse(400-sUno2*0.866, 400+0.5*sUno2, 30, 30); //sUno
  ellipse(400, 400-sDos2, 30, 30); //sDos
  
noFill();
strokeWeight(3);
stroke(255, 75, 0, 150);
  ellipse(400, 400, 75*2, 75*2);
stroke(0, 150, 255, 150);
  ellipse(400, 400, 225*2, 225*2);
strokeWeight(1);

stroke(255, 60);
ellipse(400, 400, 150*2, 150*2);
  
  
  stroke(0,255,0);
  line(400-25, 400, 400+25, 400); //cruz vertical
  line(400, 400-25, 400, 400+25); //cruz horizontal
noStroke();
  fill(220, 127);
  ellipse(bY, bX, 60, 60);
  line(bY-10, bX, bY+10, bX);
  line(bY, bX-10, bY, bX+10); 
}

void serialEvent(Serial port) {
  data = port.readString();
  String[] list = split(data, ',');
  if (list.length==9) {
    sUno=int(list[0]);
    sDos=int(list[1]);
    sTres=int(list[2]);
    gradosX=int(list[3]);
    gradosY=int(list[4]);
    promedioX=int(list[5]);
    promedioY=int(list[6]);
    hipo=int(list[7]);
    angulo=int(list[8]);
  }
}