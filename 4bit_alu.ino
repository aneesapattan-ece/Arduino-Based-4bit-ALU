int A0pin = 2;
int A1pin = 3;
int A2pin = 4;
int A3pin = 5;

int B0pin = 6;
int B1pin = 7;
int B2pin = 8;
int B3pin = 9;

int OP0 = 10;
int OP1 = 11;

int OUT0 = 12;
int OUT1 = 13;
int OUT2 = A0;
int OUT3 = A1;

void setup()
{
  pinMode(A0pin, INPUT_PULLUP);
  pinMode(A1pin, INPUT_PULLUP);
  pinMode(A2pin, INPUT_PULLUP);
  pinMode(A3pin, INPUT_PULLUP);

  pinMode(B0pin, INPUT_PULLUP);
  pinMode(B1pin, INPUT_PULLUP);
  pinMode(B2pin, INPUT_PULLUP);
  pinMode(B3pin, INPUT_PULLUP);

  pinMode(OP0, INPUT_PULLUP);
  pinMode(OP1, INPUT_PULLUP);

  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
}

void loop()
{
  // READ SWITCHES

  int a0 = !digitalRead(A0pin);
  int a1 = !digitalRead(A1pin);
  int a2 = !digitalRead(A2pin);
  int a3 = !digitalRead(A3pin);

  int b0 = !digitalRead(B0pin);
  int b1 = !digitalRead(B1pin);
  int b2 = !digitalRead(B2pin);
  int b3 = !digitalRead(B3pin);

  // BUILD 4-BIT NUMBERS

  int A = a0 + (a1 * 2) + (a2 * 4) + (a3 * 8);
  int B = b0 + (b1 * 2) + (b2 * 4) + (b3 * 8);

  // OPERATION SELECT

  int op1 = !digitalRead(OP1);
  int op0 = !digitalRead(OP0);

  int result = 0;

  // OPERATIONS

  if(op1 == 0 && op0 == 0)
  {
    // ADD
    result = A + B;
  }

  else if(op1 == 0 && op0 == 1)
  {
    // SUB
    result = A - B;

    if(result < 0)
    {
      result = 0;
    }
  }

  else if(op1 == 1 && op0 == 0)
  {
    // AND
    result = A & B;
  }

  else if(op1 == 1 && op0 == 1)
  {
    // OR
    result = A | B;
  }

  // KEEP 4 BITS

  result = result & 0B1111;

  // OUTPUT LEDs
  // LEFT → RIGHT = MSB → LSB

  digitalWrite(OUT0, bitRead(result, 3));
  digitalWrite(OUT1, bitRead(result, 2));
  digitalWrite(OUT2, bitRead(result, 1));
  digitalWrite(OUT3, bitRead(result, 0));
}