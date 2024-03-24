int rbPinLeft = A1;
int gPinLeft = A0;
int swPin=5;

int RBGRLeft = 9;
int RBGBLeft = 7;
int RBGGLeft = 8;

int RBGRRight = 13;
int RBGBRight = 12;
int RBGGRight = 11;

int RLeft = 4;
int GLeft = 3;
int BLeft = 2;

bool print=false;

int count[] = {0, 0, 0}; //R, G, B

int red = 0;
int blue = 0;
int green = 0;

bool stop = false;

void setup()
{
  pinMode(RBGRLeft,OUTPUT); //Left RGB red LED
  pinMode(RBGBLeft,OUTPUT); //Left RGB green LED
  pinMode(RBGGLeft,OUTPUT); //Left RGB blue LED

  pinMode(RBGRRight,OUTPUT); //Right RGB red LED
  pinMode(RBGBRight,OUTPUT); //Right RGB green LED
  pinMode(RBGGRight,OUTPUT); //Right RGB blue LED
  
  pinMode(RLeft,OUTPUT); //Left red LED
  pinMode(GLeft,OUTPUT); //Left green LED
  pinMode(BLeft,OUTPUT); //Left blue LED

  pinMode(5, INPUT_PULLUP);  //set the SW pin, left joystick
  Serial.begin(9600);
}

void loop()
{
  //0 to 1023
  int RB = analogRead(rbPinLeft);
  int G = analogRead(gPinLeft);
  int swPinRead= digitalRead(swPin);
  actualColor(red,blue,green);

  bool random=false;

  if (!random){
    red = random(10);
    blue = random(10);
    green = random(10);
    random=true;
  }

  if (swPinRead == 1 && !stop){
    if (RB > 1010 && G < 700 && G > 200)
    {
      digitalWrite(RLeft,HIGH);
      delay(500);
      count[0]++;
      digitalWrite(RLeft,LOW);
      Serial.print("\n RED");
    }
    if (RB < 10 && G < 700 && G > 200)
    {
      digitalWrite(BLeft,HIGH);
      delay(500);
      count[2]++;
      digitalWrite(BLeft,LOW);
      Serial.print("\n BLUE");
    }
    if (G < 10 && RB < 700 && RB > 200)
    {
      digitalWrite(GLeft,HIGH);
      delay(500);
      count[1]++;
      digitalWrite(GLeft,LOW);
      Serial.print("\n GREEN");
    }

    checkCounts(count);
    guessColor(count);
  }
  else
  {
    checkGuess(count,red,blue,green);
    stop = true;
  }

}

void guessColor (int count[])
{
  analogWrite(RBGRLeft, count[0] * 20);   
  analogWrite(RBGGLeft, count[1] * 20); 
  analogWrite(RBGBLeft, count[2] * 20); 
  delay(100);
}

void actualColor(int red, int blue, int green){
  analogWrite(RBGRRight, red * 20);   
  analogWrite(RBGGRight, blue * 20); 
  analogWrite(RBGBRight, green * 20);
}

void checkCounts (int count[])
{
  for (int i = 0; i < 3; i++)
  {
    if (count[i] >= 11)
    {
      count[i] = 0;
    }
  } 

return count;
}

void checkGuess(int count[], int red, int blue, int green){
  if (red == count[0]){
    digitalWrite(RLeft,HIGH);
  }
  if (blue == count[2]){
    digitalWrite(BLeft,HIGH);
  }
  if (green == count[1]){
    digitalWrite(GLeft,HIGH);
  }

 if (!print){
  Serial.println("\nCorrect Combination: ");
  Serial.print("Red: ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue: ");
  Serial.println(blue);

  Serial.println("Your guess: ");
  Serial.print("Red: ");
  Serial.println(count[0]);
  Serial.print("Green: ");
  Serial.println(count[1]);
  Serial.print("Blue: ");
  Serial.println(count[2]);
  print = true;
 }
}
