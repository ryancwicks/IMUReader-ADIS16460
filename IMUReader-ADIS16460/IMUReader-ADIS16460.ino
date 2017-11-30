/**
 * Sketch for reading from a ADIS16460 and sending the data topside 
 * 
 */
#include <SPI.h>

//Pin Definitions
enum PIN_DEFS : uint8_t
{
  RESET_B = 23,
  SCLK = 13,
  DOUT = 11,
  DIN = 12,
  CS = 10,
  DATA_READY = 21,
  SYNC = 22
};

//Structure for containing Gyro Data
struct IMUData
{
  unsigned long cap_time;
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
  int16_t acc_x;
  int16_t acc_y;
  int16_t acc_z;
};

//Globals
volatile bool dataReadyFlag (false);
volatile IMUData data {0, 0, 0, 0, 0, 0, 0};
// set up the speed, mode and endianness of each device
SPISettings settings(900000, MSBFIRST, SPI_MODE3); 

//Function Definitions
void DataReady ();
void ReadIMU ( );

void setup() {
  // Set up pin modes
  pinMode (RESET_B, OUTPUT);
  pinMode (DATA_READY, INPUT);
  pinMode (SYNC, INPUT);
  pinMode (CS, OUTPUT);
  
  //Set startup values
  digitalWrite (RESET_B, LOW);
  digitalWrite (CS, HIGH);

  //Set Up Interrupts
  attachInterrupt(digitalPinToInterrupt(DATA_READY), DataReady, RISING);

  //Set up Serial
  Serial.begin (230400);
  Serial.println ( "#Gyro Units: 0.005 degrees/second/LSB");
  Serial.println ( "#Acceleration Units: 0.25 mg/LSB" );
  Serial.println ( "#Time (us), gyro x, gyro y, gyro z, acc x, acc y, acc z");

  SPI.begin();

  //begin capture
  digitalWrite (RESET_B, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (dataReadyFlag  )
  {
    dataReadyFlag = false;
    ReadIMU ();
    Serial.print ( data.cap_time );
    Serial.print ( "," );
    Serial.print ( data.gyro_x );
    Serial.print ( "," );
    Serial.print ( data.gyro_y );
    Serial.print ( "," );
    Serial.print ( data.gyro_z );
    Serial.print ( "," );
    Serial.print ( data.acc_x );
    Serial.print ( "," );
    Serial.print ( data.acc_y );
    Serial.print ( "," );
    Serial.println (data.acc_z );
    
  }

}

void DataReady ()
{
  data.cap_time = millis();
  dataReadyFlag = true;
}

void ReadIMU (  )
{
  SPI.beginTransaction ( settings );
  digitalWrite (CS, LOW);

  //Initiate Bulk Transfer
  SPI.transfer16 ( 0x3E00 );

  int16_t diag = SPI.transfer16(0);
  data.gyro_x = SPI.transfer16(0);
  data.gyro_y = SPI.transfer16(0);
  data.gyro_z = SPI.transfer16(0);
  data.acc_x = SPI.transfer16(0);
  data.acc_y = SPI.transfer16(0);
  data.acc_z = SPI.transfer16(0);
  int16_t temp = SPI.transfer16(0);
  int16_t smp_ctrl = SPI.transfer16(0);
  int16_t checksum = SPI.transfer16(0);

  digitalWrite (CS, HIGH);
  SPI.endTransaction ();
}

