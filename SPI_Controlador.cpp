// C++ code
// Controller
#define TASK 0

#define SPI_SCK_PIN  13
#define SPI_MISO_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_CS_PIN   10

#define SPI_SCK_T 100 // Periodo del reloj en ms

#define START_DELAY 500 // Delay antes del loop().
#define SEND_DELAY  500 // Delay entre envios consecutivos de bytes

#define FIRST_CHAR 'A'
#define LAST_CHAR  'Z'

char dataSend = FIRST_CHAR;

int clkState = LOW;
unsigned long prevTick = 0.0;

void resetClock(void)
{
  prevTick = millis();
  clkState = LOW;

  #if TASK >= 3
  //Paso 3.1
  //Defina el estado inicial del pin del reloj
  digitalWrite(SPI_SCK_PIN, LOW);
  //--------------------------------------
  #endif 
}

int getClockTransition(void)
{
  int transition = -1;
  
  if ((millis() - prevTick) >= SPI_SCK_T) 
  {
    clkState = !clkState;
    prevTick = millis();
    transition = clkState;
    
    #if TASK >= 3
    //Paso 3.2
    //Active el reloj igualandolo a clkState
    digitalWrite(SPI_SCK_PIN, );
    //--------------------------------------
    #endif
  }
  
  return transition;
}

char sendRecvByte(char dataSend)
{
  int bit;
  int clkTransition;
  char dataRecv = '\0'; //Variable donde se guarda el dato recibido 
  
  int dataSendBitIndex = 0; //Indice del bit que se esta enviando
  int dataRecvBitIndex = 0; //Indice del bit que se esta recibiendo
  
  #if TASK >= 3
  resetClock();
  Serial.println("CLOCK RESET");
  
  #if TASK >= 4
  //Paso 4.1
  //Guarde en bit el bit numero n de dataSend
  //bitRead(x, n) donde x es la variable y n es el indice del bit que se esta enviando
  bit = bitRead( , );
  //Escriba el bit que se esta enviando en el pin del puerto MOSI
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
      Serial.println("CLK en ALTO");
      #if TASK >= 4
      //Paso 4.2
      //Guarde en bit el bit que se esta recibiendo del puerto MISO
      //Escriba el nombre del pin
      bit = digitalRead( ); //Variable donde se guarda el bit recibido
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
      Serial.println("CLK en BAJO");
      
      #if TASK >= 4
      //Paso 4.3
      //Guarde en bit el bit numero n de dataSend
      //bitRead(x, n) donde x es la variable y n es el indice del bit que se esta enviando
      bit = bitRead(, );
      //Escriba el bit que se esta enviando en el pin del puerto MOSI
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
  
  resetClock();
  
  #else
  delay(1000);
  #endif
  
  return dataRecv;
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hola soy el Controlador");
  
  #if TASK >= 1
  //Paso 1.1
  //Defina si los pines del SPI Controlador son INPUT o OUTPUT
  //Escriba INPUT o OUTPUT 
  pinMode(SPI_SCK_PIN,  ); 
  pinMode(SPI_MISO_PIN, );
  pinMode(SPI_MOSI_PIN, );
  pinMode(SPI_CS_PIN,   );
  //---------------------------------------------
  
  //Paso 1.2
  //Defina el estado inicial de los pines del SPI Controlador
  //Escriba HIGH o LOW
  digitalWrite(SPI_SCK_PIN,  );
  digitalWrite(SPI_MOSI_PIN, );
  digitalWrite(SPI_CS_PIN,   );
  
  Serial.println("Pins del SPI Controlador inicializados");
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

void loop()
{
  char dataRecv = '?';
  
  #if TASK >= 2
  //Paso 2.1
  //Seleccione el periferico con el que se va a comunicar
  digitalWrite( , );
  Serial.println("Periferico seleccionado");
  //---------------------------------------------
  #endif
  
  dataRecv = sendRecvByte(dataSend);
  
  #if TASK >= 2
  //Paso 2.2
  //Deseleccione el periferico con el que se esta comunicando
  digitalWrite( , );
  Serial.println("Periferico deseleccionado");
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
  
  #if TASK >= 3
  Serial.println();
  #endif
  
  delay(SEND_DELAY);
}





















