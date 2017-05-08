int led = 9;
int b1 = 6;
int b2 = 7;

int eb1 = 0;
int eb2 = 0;
int eb3 = 0;
unsigned long b1t;
unsigned long b2t;
unsigned long b3t;

int estado = 0;
unsigned long ultimo = 0;
unsigned long agora;
unsigned long piscar = 1000;


void setup()
{
  pinMode(led, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
}

// the loop routine runs over and over again forever:

void loop()
{

  digitalWrite(led, estado);
  agora = millis();


  int b1p = digitalRead(b1);
  int b2p = digitalRead(b2);


  if (agora >= ultimo + piscar)
  {
      ultimo = agora;
      estado = !estado;
  }

  if (agora >= b1t + 200 && b1p == HIGH)
    	eb1 = 0;

  if (agora >= b2t + 200 && b2p == HIGH)
    	eb2 = 0;

  if (agora >= b3t + 400 && eb1 == 1 && eb2 ==1)
  {
    piscar = 0;
   	eb3 = 0;
  }

  if (b1p == LOW && b2p == LOW && eb3 == 0)
  {
    eb3 = 1;
    b3t = millis();
  }

  //else eb3 = 0;

  if (b1p == LOW && eb1 == 0)
  {
    eb1 = 1;
    b1t = millis();

   	if (piscar > 100 && piscar != 0)
  		piscar -= 300;
  }

  if (b2p == LOW && eb2 == 0)
  {
    eb2 = 1;
    b2t = millis();

   	if (piscar < 1900 && piscar != 0)
  		piscar += 300;
  }
}

