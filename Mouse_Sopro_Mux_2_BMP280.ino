
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Mouse.h>

// Definições para o filtro 
#define N_1 99
#define N_INV 0.01

// Margem de trabalho
#define DELTA_SOPRO 1000

// Canais do Mux
#define CSN2 1
#define CSN1 7
#define CSN0 0

/**
 * PROTOTIPOS DAS FUNÇÕES 
*/
void selCanal(uint8_t canal);

// Cliques normais
void testClickBtnRight();
void testClickBtnLeft();

// Cliques presos
void testBtnLeftHold();
void testBtnRightHold();


// Sensores de Pressão
Adafruit_BMP280 BMP[3];


/**
 * VARIÁVEIS GLOBAIS
*/
static float media0;    
static float media1;
static float media2;

float pressure0 = 0;
float pressure1 = 0;
float pressure2 = 0; 

static float  xDistance = 0;
static float  yDistance = 0;
int range = 10;  

// Definições para a alavanca
const int analogico1  = A1;
const int analogico2  = A0;
const int StickButton = 10;

// Definições do botão esquerdo do Mouse 
bool leftBtnState;
bool lastLeftBtnState;
  
bool rightBtnState;
bool lastRightBtnState; 

bool rightBtnHoldState;
bool lastRightBtnHoldState;

bool leftBtnHoldState;
bool lastLeftBtnHoldState;

void setup()
{
  pinMode(analogico1, INPUT);
  pinMode(analogico2, INPUT);
  pinMode(StickButton, INPUT_PULLUP);
  
  pressure0 = 0;
  pressure1 = 0;
  pressure2 = 0;
    
  media0 = 0;
  media1 = 0;
  media2 = 0;

  leftBtnState = false;
  lastLeftBtnState = false;

  rightBtnState = false;
  lastRightBtnState = false;

  rightBtnHoldState = false;
  lastRightBtnHoldState = false;

  leftBtnHoldState = false;
  lastLeftBtnHoldState = false;

  
  /** TODO: Verificar porquê Mouse.begin() 
   *  se ativado  neste ponto do código a comunicação fica instável
   */

  //Mouse.begin();
  
    
  // Utiliza a a segunda serial para depuração 
  Serial1.begin(57600);
  Serial1.println("Iniciando a Configuração");

  // Seta para 100kHz
  /**
   * TODO: Verificar se é efetiva essa linha, no osciloscópio e no código.
   * Se realmente é configurado o I2C para trabalhar em 100kHz
  */ 
  Wire.setClock(100000); 

  // Seleciona o canal CSN0 do mux e inicializa o sensor BMP 
  selCanal(CSN0);
  BMP[0].begin(0x76);
  delay(20);
  Serial1.print("MUX Canal: "); Serial1.print(CSN0);Serial1.print(" : "); Serial1.println("Sensor 0 Ok");
  
  // Seleciona o canal CSN0 do mux e inicializa o sensor BMP 
  selCanal(CSN1);
  BMP[1].begin(0x76);
  delay(20);
  Serial1.print("MUX Canal: "); Serial1.print(CSN1);Serial1.print(" : "); Serial1.println("Sensor 1 Ok");
 
 // Seleciona o canal CSN0 do mux e inicializa o sensor BMP 
  selCanal(CSN2);
  BMP[2].begin(0x76);
  delay(20);
  Serial1.print("MUX Canal: "); Serial1.print(CSN2);Serial1.print(" : ");Serial1.println("Sensor 2 Ok");

  /**
   * Realiza a calibração dos sensores BMP280.
  */

  Serial1.print("Iniciando a calibração do sensor 0 ");Serial1.print(" Canal: ");Serial1.print(CSN0);Serial1.print(" ");
  selCanal(CSN0);
  for ( int i = 0 ; i < 1100; i++){
    pressure0 = BMP[0].readPressure();
    media0 = (pressure0 +  N_1 * media0) * N_INV;
  }
  Serial1.print("média encontrada: "); Serial1.println(media0);
  
  
  Serial1.print("Iniciando a calibração do sensor 1 ");Serial1.print(" Canal: ");Serial1.print(CSN1);Serial1.print(" ");
  selCanal(CSN1);
  for ( int i = 0 ; i < 1100; i++){
    pressure1 = BMP[1].readPressure();
    media1 = (pressure1 +  N_1 * media1) * N_INV;
  }
  Serial1.print("média encontrada: "); Serial1.println(media1);

  
  Serial1.print("Iniciando a calibração do sensor 2 ");Serial1.print(" Canal: ");Serial1.print(CSN2);Serial1.print(" ");
  selCanal(CSN2);
  for ( int i = 0 ; i < 1100; i++){
    pressure2 = BMP[2].readPressure();
    media2 = (pressure2 +  N_1 * media2) * N_INV;
  }
  Serial1.print("média encontrada: "); Serial1.println(media2);

  Serial1.println("Configurações e Calibrações concluídas!!!");
}
 
void loop() {
  pressure0 = 0;
  pressure1 = 0;
  pressure2 = 0;
  
  xDistance = 0;
  yDistance = 0;
  
  selCanal(CSN0);
  pressure0 = BMP[0].readPressure();
  delay(5);
  
  selCanal(CSN1);
  pressure1 = BMP[1].readPressure();
  delay(5);
  
  selCanal(CSN2);
  pressure2 = BMP[2].readPressure();
  delay(5);


  recalculaMedia();

  testClickBtnRight(); 
  testClickBtnLeft();
  
  testBtnLeftHold(); 

  lerMovimentoJoystick();
  
  Serial1.print("Sensor 0: ");Serial1.print("Mux: ");Serial1.print(CSN0); Serial1.print(" ");Serial1.print(pressure0); Serial1.print(" media0 "); Serial1.print(media0);Serial1.println("");
  Serial1.print("Sensor 1: ");Serial1.print("Mux: ");Serial1.print(CSN1); Serial1.print(" ");Serial1.print(pressure1); Serial1.print(" media1 "); Serial1.print(media1);Serial1.println("");
  Serial1.print("Sensor 2: ");Serial1.print("Mux: ");Serial1.print(CSN2); Serial1.print(" ");Serial1.print(pressure2); Serial1.print(" media2 "); Serial1.print(media2);Serial1.println("");
  
}


void recalculaMedia()
{
   if ( pressure0 > media0 - DELTA_SOPRO && pressure0 < media0 + DELTA_SOPRO)
  {
    media0  = (pressure0 +  N_1 * media0) * N_INV;
  }

  if ( pressure1 > media1 - DELTA_SOPRO && pressure1 < media1 + DELTA_SOPRO)
  {
    media1  = (pressure1 +  N_1 * media1) * N_INV;
  }

  if ( pressure2 > media2 - DELTA_SOPRO && pressure2 < media2 + DELTA_SOPRO)
  {
    media2  = (pressure2 +  N_1 * media2) * N_INV;
  }

}
void testClickBtnLeft()
{
  leftBtnState = ( pressure1 > media1 + DELTA_SOPRO+500);
  if (leftBtnState != lastLeftBtnState )
  {
    if (leftBtnState)
    {
      Serial1.println("LEFT click");
      //Mouse.press(MOUSE_LEFT);
      Mouse.click(MOUSE_LEFT);
    }
    else
    {
      Serial1.println("release LEFT");
      //Mouse.release();
    }
  }
  lastLeftBtnState = leftBtnState;
}

void testClickBtnRight()
{
 rightBtnState = ( pressure1 < media1 - DELTA_SOPRO-500);
  if (rightBtnState != lastRightBtnState )
  { 
    if (rightBtnState)
    {
      Serial1.println("right click");
      Mouse.click(MOUSE_RIGHT);
    }
    else
    {
      Serial1.println("release right");
     // Mouse.release();
    }
  }
  lastRightBtnState = rightBtnState;  
}
void testBtnRightHold()
{
  rightBtnHoldState = ( pressure2 < media2 - DELTA_SOPRO);
  if (rightBtnHoldState != lastRightBtnHoldState )
  { 
    if (rightBtnHoldState)
    {
      if (!Mouse.isPressed(MOUSE_RIGHT))
      {
        Mouse.press(MOUSE_RIGHT);
        Serial1.println("RIGHT_HOLD PRESS ");
      }
      else
      {
        Mouse.release(MOUSE_RIGHT);
        Serial1.println("RIGHT_HOLD RELEASE");
      }
    }
  }
  lastRightBtnHoldState = rightBtnHoldState;    
}
void testBtnLeftHold()
{
  leftBtnHoldState = ( pressure2 > media2 + DELTA_SOPRO);
  if (leftBtnHoldState != lastLeftBtnHoldState )
  { 
    if (leftBtnHoldState)
    {
      
      if (!Mouse.isPressed(MOUSE_LEFT))
      {
        Mouse.press(MOUSE_LEFT);
        Serial1.println("LEFT_HOLD PRESS ");
      }
      else
      {
        Mouse.release(MOUSE_LEFT);
        Serial1.println("LEFT_HOLD RELEASE");
      }
    }
  }
  lastLeftBtnHoldState = leftBtnHoldState;  
}
void lerMovimentoJoystick()
{
  // Movimentos do Joystick
  if (analogRead(analogico1) > (515 + 20)) {
    xDistance = map(analogRead(analogico1), 535, 1024, 0 , (-range));
  }

  if (analogRead(analogico1) <= (515 - 20)) {
    xDistance = map(analogRead(analogico1), 495, 0, 0, range);
  }

  if (analogRead(analogico2) > (515 + 30)) {
    yDistance = map(analogRead(analogico2), 535, 1024, 0 , (-range));
  }

  if (analogRead(analogico2) <= (515 - 30)) {
    yDistance = map(analogRead(analogico2), 495, 0, 0, range);
  }

  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }
}
void selCanal(uint8_t canal)
{
  Wire.beginTransmission(0x70);
  Wire.write(1 << canal);
  Wire.endTransmission(); 
  delay(3);
}
