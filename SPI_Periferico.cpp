// C++ code
// Peripheral
#define TASK 0

#define SPI_SCK_PIN  13
#define SPI_MISO_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_CS_PIN   10

#define START_DELAY 50 // Delay antes del loop()

#define FIRST_CHAR '0'
#define LAST_CHAR  '9'

char dataSend = FIRST_CHAR;

int clkState = LOW;

void resetClock(void)
{
  clkState = LOW;
}


int getClockTransition(void)
{
  int transition = -1;
  int currentClkVal = LOW;
  
  #if TASK >= 3
  //Paso 3.1
  //Lea el estado del pin del reloj del Controlador
  currentClkVal = digitalRead( ); //Nombre del pin
  //--------------------------------------
  #endif 
  
  if (clkState != currentClkVal)
  {
    clkState = !clkState;
    transition = clkState;
  }
  
  return transition;
}

char sendRecvByte(char dataSend)
{
  int bit;
  int clkTransition;
  char dataRecv; 
  
  int dataSendBitIndex = 0; //Indice del bit que se esta enviando
  int dataRecvBitIndex = 0; //Indice del bit que se esta recibiendo

  #if TASK >= 3
  resetClock();
  Serial.println("Detectando señal de reloj");
  
  #if TASK >= 4
  //Paso 4.1
  //Guarde en bit el bit numero n de dataSend
  //bitRead(x, n) donde x es la variable y n es el indice del bit que se esta enviando
  bit = bitRead(, );
  //Escriba el bit que se esta enviando en el pin del puerto MISO
  //digitalWrite(p, b) donde p es el nombre del puerto y b es el bit que se esta enviando
  digitalWrite(, );
  //--------------------------------------
  #endif 
  dataSendBitIndex++;
  
  while (1)
  {
    clkTransition = getClockTransition();
    if (clkTransition == HIGH)
    {
      Serial.println("CLK ALTO");
      
  #if TASK >= 4
      //Paso 4.2
      //Guarde en bit el bit que se esta recibiendo del puerto MOSI
      //Escriba el nombre del pin
      bit = digitalRead(); //Variable donde se guarda el bit recibido
      // bitWrite(x, n, b) donde: 
      // x es la variable donde se guarda el dato recibido
      // n es el indice del bit que se esta recibiendo
      // b es el bit que se esta recibiendo
      bitWrite(, , );
      //--------------------------------------
  #endif 
      dataRecvBitIndex++;
    }
    else if (clkTransition == LOW)
    {
      Serial.println("CLK BAJO");
      
  #if TASK >= 4
      //Paso 4.3
      //Guarde en bit el bit numero n de dataSend
      //bitRead(x, n) donde x es la variable y n es el indice del bit que se esta enviando
      bit = bitRead(, );
      //Escriba el bit que se esta enviando en el pin del puerto MISO
      //digitalWrite(p, b) donde p es el nombre del puerto y b es el bit que se esta enviando
      digitalWrite(, );
      //--------------------------------------
  #endif 
      dataSendBitIndex++;
    }
    
    if ((dataSendBitIndex == 8) && (dataRecvBitIndex == 8))
    {
      break;
    }
  }
  #endif 
  
  return dataRecv;
}


void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hola soy el Periferico");
  
  #if TASK >= 1
  //Paso 1.1
  //Defina si los pines del SPI Periferico son INPUT o OUTPUT
  //Escriba INPUT o OUTPUT 
  pinMode(SPI_SCK_PIN,  );
  pinMode(SPI_MISO_PIN, );
  pinMode(SPI_MOSI_PIN, );
  pinMode(SPI_CS_PIN,   );
  //---------------------------------------------
  
  //Paso 1.2
  //Defina el estado inicial de los pines del SPI Periferico
  //Escriba HIGH o LOW
  digitalWrite(SPI_MISO_PIN, );
  
  Serial.println("Pins del SPI Periferico inicializados");
  Serial.print("SCK: ");
  Serial.println(SPI_SCK_PIN);
  Serial.print("MISO: ");
  Serial.println(SPI_MISO_PIN);
  Serial.print("MOSI: ");
  Serial.println(SPI_MOSI_PIN);
  Serial.print("CS: ");
  Serial.println(SPI_CS_PIN);
  //---------------------------------------------
  #endif
  delay(START_DELAY);
  Serial.println();
}

void loop(void)
{
  char dataRecv = '?';
  
#if TASK >= 2
  
  //Paso 2.1
  //Espere hasta que que el controlador lo haya seleccionado
  //Defina la condicion de espera 
  //En que estado esta el Chip Select cuando el periferico no ha sido seleccionado?
  while (digitalRead( ) == ) //Condicion de espera
  {
    ;
  }
  Serial.println("Fui seleccionado");
  //---------------------------------------------
  #endif 

  dataRecv = sendRecvByte(dataSend);

  #if TASK >= 2
  //Paso 2.2
  //Espere hasta que que el controlador lo haya deseleccionado
  //Defina la condicion de espera
  //En que estado esta el Chip Select cuando el periferico ha sido seleccionado?
  while (digitalRead( ) == ) //Condicion de espera
  {
    ;
  }
  Serial.println("No fui seleccionado");
  //---------------------------------------------
  #endif 
  
  #if TASK >= 4
  Serial.print("Dato enviado:     ");
  Serial.println(dataSend);
  Serial.print("Dato recibido: ");
  Serial.println(dataRecv);
  
  dataSend++;
  if (dataSend == (LAST_CHAR + 1))
  {
    dataSend = FIRST_CHAR;
  }
  #endif
  
  #if TASK >= 2
  Serial.println();
  #endif 
}