const uint16_t inputLength = 512;
int ss = 0;
int bHold = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
if ( Serial.available() > 0 )
{
  static char input[inputLength];
  static uint16_t i;
  char c = Serial.read();

  if ( c != '\r' && c != '\n' && i < inputLength - 1)
    input[i++] = c;

  else
  {
    input[i] = '\0';
    i = 0;

    uint16_t array[80];
    uint16_t j = 0;

    if ( !strncmp(input, "ss", 2) )
    {
      char* p = input + 2;
      while ( (p = strchr(p, ' ')) != NULL )
        array[j++] = strtol(p, &p, 10); //

      for ( uint8_t i = 0; i < j; i++ )
      {
        ss = array[i];
        Serial.println(ss);
      }
    }

    if ( !strncmp(input, "bHold", 5) )
    {
      char* p = input + 5;
      while ( (p = strchr(p, ' ')) != NULL )
        array[j++] = strtol(p, &p, 10);

      for ( uint8_t i = 0; i < j; i++ )
      {
       bHold = array[i];
       Serial.println(bHold);
      }
    }

    if ( !strncmp(input, "Whos There", 10) )
    {
      Serial.print("me");
    }
    if ( !strncmp(input, "hello", 5) )
    {
      Serial.print("hi");
    }
    if ( !strncmp(input, "sa", 2) )
    {
      Serial.print("  ss= ");
      Serial.print(ss);

      Serial.print("  bHold= ");
      Serial.print(bHold);

      Serial.println(" ");
      Serial.println("==============================");
    }
  }
}
}
