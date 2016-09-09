#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            17
#define NUMPIXELS      10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int lecturaX = 0; //lectura eje(x) por 10
int lecturaY = 0; //lectura eje(7) por 10
int gradosX = 0; //lectura del acelerometro en grados de 0
int gradosY = 0; 
int noventa = 90; //referencia grados ideales
int promedioX = 0;
int promedioY = 0;
int hipo = 0;
int intervalo = 5;
int treinta = 30;
int angulo = 0;
int delayHipo;
int i;
int sUno = 90;
int sDos = 90;
int sTres = 90;
int random1, random2, random3;

Servo myservoUno;
Servo myservoDos;
Servo myservoTres;



void setup() {
  
   pixels.begin();
   Serial.begin(9600);
  myservoUno.attach(2);
  myservoDos.attach(10);
  myservoTres.attach(12);
  CircuitPlayground.begin();

}

void loop() {
  pixels.show();


 //     if (sUno > 180){sUno = 180;}
   //   if (sUno < 0){sUno = 0;}
    //  if (sDos > 180){sDos = 180;}
   //   if (sDos < 0){sDos = 0;}
   //   if (sTres > 180){sTres = 180;}
   //   if (sTres < 0){sTres = 0;}

    if (sUno > 270){        //sUno<2700
      if(sDos < sTres){
        sDos = sDos + 1;
        sUno = sUno - 1;
      }
      else if (sDos > sTres){
        sTres = sTres + 1;
        sUno = sUno-1;
      }
      else if (sDos == sTres){
        sDos = sDos+1;
        sTres = sTres+1;
        sUno = sUno -2;
      }}
    if (sDos > 270){        //sDos<270
      if(sUno < sTres){
        sUno = sUno+1;
        sDos = sDos-1;
      }
      else if (sUno > sTres){
        sTres = sTres+1;
        sDos = sDos-1;
      }
      else if (sUno == sTres){
        sUno = sUno+1;
        sTres = sTres+1;
        sDos = sDos -2;
      }}
if (sTres > 270){          //sTres<270
      if(sUno < sDos){
        sUno = sUno+1;
        sTres = sTres-1;
      }
      else if (sUno > sDos){
        sDos = sDos+1;
        sTres = sTres-1;
      }
      else if (sUno == sDos){
        sUno = sUno+1;
        sDos = sDos+1;
        sTres = sTres -2;
      }}


      if (sUno < -90){            //sUno>-90
        if(sDos < sTres){
          sTres = sTres -1;
          sUno = sUno+1;
        }
        else if(sDos > sTres){
          sDos = sDos-1;
          sUno = sUno+1;
        }
        else if(sDos == sTres){
          sDos = sDos-1;
          sTres = sTres-1;
          sUno = sUno+2;
        }
      }

        if (sDos < -90){            //sDos>-90
        if(sUno < sTres){
          sTres = sTres -1;
          sDos = sDos+1;
        }
        else if(sUno > sTres){
          sUno = sUno-1;
          sDos = sDos+1;
        }
        else if(sUno == sTres){
          sUno = sUno-1;
          sTres = sTres-1;
          sDos = sDos+2;
        }
      }


      if (sTres < -90){            //sTres>-90
        if(sDos < sUno){
          sUno = sUno -1;
          sTres = sTres+1;
        }
        else if(sDos > sUno){
          sDos = sDos-1;
          sTres = sTres+1;
        }
        else if(sDos == sUno){
          sDos = sDos-1;
          sUno = sUno-1;
          sTres = sTres+2;
        }
      }


    
      
      myservoUno.write(sUno);
      myservoDos.write(sDos);
      myservoTres.write(sTres);
      
      Serial.print(sUno);Serial.print(',');
      Serial.print(sDos);Serial.print(',');
      Serial.print(sTres);Serial.print(',');
      
 // sUno, sDos, sTres, gradosX, gradosY, promedioX, promedioY, hipo, angulo
      
  lecturaX = CircuitPlayground.motionX()*10;                          //lectura eje X, pasa a grados 0/180
  gradosX = map(lecturaX, -100, 100, 0, 180);
  Serial.print(gradosX);Serial.print(',');

  lecturaY = CircuitPlayground.motionY()*10;                         //lectura eje Y, pasa a grados 0/180
  gradosY = map(lecturaY, -100, 100, 180, 0);
  Serial.print(gradosY);Serial.print(',');

  promedioX = (abs(gradosX - 90));
 Serial.print(promedioX);Serial.print(',');

  promedioY = (abs(gradosY - 90));
 Serial.print(promedioY);Serial.print(',');

  hipo = sqrt(pow(promedioX, 2)+pow(promedioY, 2));
  Serial.print(hipo);Serial.print(',');

  angulo = (promedioY * 100 / hipo);
  Serial.println(angulo);

delayHipo = map(hipo, 0, 90, 2000, 0);
delayMicroseconds(delayHipo);

while (CircuitPlayground.leftButton()||CircuitPlayground.rightButton()){
  sUno = 90;
  sDos = 90;
  sTres = 90;
  for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(2,2,2));
  }
  pixels.setPixelColor(0, pixels.Color(2,2,2));pixels.setPixelColor(9, pixels.Color(2,2,2));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(2,2,2));
  }
  pixels.show();
  delay(1000);
}
if (!CircuitPlayground.slideSwitch()){
  for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(2,2,2));
  }
  pixels.setPixelColor(0, pixels.Color(2,2,2));pixels.setPixelColor(9, pixels.Color(2,2,2));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(2,2,2));
  }
  pixels.show();
}
if (CircuitPlayground.slideSwitch()){
if (hipo > 6){
if (gradosX < noventa && gradosY >= noventa){         // 9/12 NO
  if (angulo > 50 && angulo < 85){                    // NO 45
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
    
    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  pixels.setPixelColor(0, pixels.Color(0,1,5));pixels.setPixelColor(9, pixels.Color(0,1,5));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }
      sDos = sDos + 1;
      sTres = sTres - 1;
      
  }
  
  else if(abs(gradosX - 90) > abs(gradosY - 90)){      // NON 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  pixels.setPixelColor(0, pixels.Color(0,1,5));pixels.setPixelColor(9, pixels.Color(0,1,5));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }

      sDos = sDos + 1;
      sTres = sTres - 1;
  }
  else if(abs(gradosX - 90) < abs(gradosY - 90)){       // ONO 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }
  pixels.setPixelColor(0, pixels.Color(1,5,0));pixels.setPixelColor(9, pixels.Color(1,5,0));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }

      sUno = sUno + 1;
      sTres = sTres - 1;
  }
}

//FIN NO

else if (gradosX <= noventa && gradosY < noventa){     //12/3 NE
  if (angulo > 50 && angulo < 85){                   // NE 45
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }


  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }
  pixels.setPixelColor(0, pixels.Color(0,1,5));pixels.setPixelColor(9, pixels.Color(0,1,5));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }

      sUno = sUno - 1;
      sDos = sDos + 1;
  }
  else if(abs(gradosX) < abs(gradosY) ){
    for(int i=0;i<NUMPIXELS;i++){                     //NEN 90            
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }
  pixels.setPixelColor(0, pixels.Color(0,1,5));pixels.setPixelColor(9, pixels.Color(0,1,5));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  
      sUno = sUno - 1;
      sDos = sDos + 1;
  }
  else if(abs(gradosX) > abs(gradosY)){               // ENE 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

  for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }
  pixels.setPixelColor(0, pixels.Color(1,5,0));pixels.setPixelColor(9, pixels.Color(1,5,0));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }

      sUno = sUno - 1;
      sTres = sTres + 1;
  }
}

//FIN NE


else if (gradosX > noventa && gradosY <= noventa){     //3/6 SE
  if (angulo > 50 && angulo < 85){                     // SE 45
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  pixels.setPixelColor(0, pixels.Color(5,0,1));pixels.setPixelColor(9, pixels.Color(5,0,1));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }
  
      sDos = sDos - 1;
      sTres = sTres + 1;
  }
  else if(abs(gradosX - 90) > abs(gradosY - 90)){      // SES 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  pixels.setPixelColor(0, pixels.Color(5,0,1));pixels.setPixelColor(9, pixels.Color(5,0,1));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }

    
      sDos = sDos - 1;
      sTres = sTres + 1;
  }
  else if(abs(gradosX - 90) < abs(gradosY - 90)){     // ESE 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }
  pixels.setPixelColor(0, pixels.Color(1,5,0));pixels.setPixelColor(9, pixels.Color(1,5,0));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }

      sUno = sUno - 1;
      sTres = sTres + 1;
  }
}

//FIN SE

else if (gradosX >= noventa && gradosY > noventa){       //6/9 SO
  if (angulo > 50 && angulo < 85){
  for(int i=0;i<NUMPIXELS;i++){                       // SO 45
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }
  pixels.setPixelColor(0, pixels.Color(5,0,1));pixels.setPixelColor(9, pixels.Color(5,0,1));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  
      sUno = sUno + 1;
      sDos = sDos - 1;
  }
  else if(abs(gradosX) > abs(gradosY)){           //  SOS 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }
  pixels.setPixelColor(0, pixels.Color(5,0,1));pixels.setPixelColor(9, pixels.Color(5,0,1));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }

      sUno = sUno + 1;
      sDos = sDos - 1;
  }
  else if(abs(gradosX) < abs(gradosY)){           // OSO 90
    for(int i=0;i<NUMPIXELS;i++){                       
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    }

    for(i=2; i<=4; i++){
    pixels.setPixelColor(i, pixels.Color(0,1,5));
  }
  pixels.setPixelColor(0, pixels.Color(1,5,0));pixels.setPixelColor(9, pixels.Color(1,5,0));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(5,0,1));
  }

      sUno = sUno + 1;
      sTres = sTres - 1;
  }

//FIN SO


}
}
else{
delay(50);
for(i=2; i<=4; i++){
  
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }
  pixels.setPixelColor(0, pixels.Color(1,5,0));pixels.setPixelColor(9, pixels.Color(1,5,0));
  for(i=5; i<=7; i++){
    pixels.setPixelColor(i, pixels.Color(1,5,0));
  }

}
} //slideswitch
} //voidloop
