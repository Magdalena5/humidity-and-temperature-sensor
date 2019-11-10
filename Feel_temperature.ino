#include "dht.h"
#define DHTPIN 5 // Analog Pin sensor is connected to
 
dht DHT;

double R=0; //relative humidity %
double T=0; //temperature in Ceslius
double Tcelsius=0; //temperature in Ceslius
double HI0=0; //heat index in Celsius
double HI1=0; //heat index in Celsius


//The formula below approximates the heat index in degrees Fahrenheit, for uncertainty for heat index ±1.3 °F (0.7 °C)
const double c01= -42.379;
const double c02=2.04901523;
const double c03=10.14333127;
const double c04=-0.22475541;
const double c05=-6.83783*pow(10,-3);
const double c06=-5.481717*pow(10,-2);
const double c07=1.22874*pow(10,-3);
const double c08=8.5282*pow(10,-4);
const double c09=-1.99*pow(10,-6);

//The formula below approximates the heat index in degrees Fahrenheit, for uncertainty for heat index ±3 °F (1.7 °C)
//if temperature is btween 21-46 °C and humidity is between 0%-80% and heat index is lower than 66 °C
const double c1= 0.363445176;
const double c2= 0.988622465;
const double c3= 4.777114035;
const double c4= -0.114037667;
const double c5= -8.50208*pow(10,-4);
const double c6= -2.0716198*pow(10,-2);
const double c7= 6.876778*pow(10,-4);
const double c8= 2.74954*pow(10,-4);
const double c9= 0;

//A further alternate for uncertainty for heat index ±3 °F (1.7 °C) is this:
const double c21= 16.923;
const double c22= 0.18521;
const double c23= 5.37941;
const double c24= -0.100254;
const double c25= 9.41695*pow(10,-3);
const double c26= 7.28898*pow(10,-3);
const double c27= 3.45372*pow(10,-4);
const double c28= -8.15971*pow(10,-4);
const double c29= 1.02102*pow(10,-5);
const double c210= -3.8646*pow(10,-5);
const double c211= 2.91583*pow(10,-5);
const double c212= 1.42721*pow(10,-6);
const double c213= 1.97483*pow(10,-7);
const double c214= -2.18429*pow(10,-8);
const double c215= 8.43296*pow(10,-10);
const double c216= -4.81975*pow(10,-11);



void setup(){
 
  Serial.begin(9600);
  delay(500);         //Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);       //Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
    //Start of Program 
    //read the PIN
    DHT.read11(DHTPIN);

    //Reead Humidity in % and temperature which is calculate from Fahrenheit to Celsius 
    R=DHT.humidity; 
    T=(DHT.temperature*9/5)+32;
    //Print Humidity in % and Celsius
    Serial.print("Current humidity: ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    
    Serial.print("temperature: ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    //Calculate heat index in Celsius, when uncertainty heat index is 0.7°C
    HI0=((c01 + c02*T+c03*R +c04*T*R+c05*T*T+c06*R*R+c07*T*T*R+c08*T*R*R+c09*T*T*R*R)-32)*5/9;

    //Print Feel temperature in Celsius, when uncertainty heat index is 0.7°C
    Serial.print("Temperature feel by, when uncertainty heat index is 0.7°C: ");
    Serial.print(HI0);
    Serial.println("C  ");


    //Calculate heat index in Celsius, when uncertainty heat index is 1.7C
    if(R<=0.80 and (T>=21 and T<=46)){
    HI1=((c1 + c2*T+c3*R +c4*T*R+c5*T*T+c6*R*R+c7*T*T*R+c8*T*R*R+c9*T*T*R*R)-32)*5/9;
    }
    else{
    HI1=((c21 + c22*T+c23*R +c24*T*R+c25*T*T+c26*R*R+c27*T*T*R+c28*T*R*R+c29*T*T*R*R+c210*pow(T,3)+c211*pow(R,3)+
    c212*pow(T,3)*R+c213*T*pow(R,3)+c214*pow(T,3)*pow(R,2)+c215*pow(T,2)*pow(R,3)+c216*pow(T,3)*pow(R,3))-32)*5/9;
    }
    
    //Print Feel temperature in Celsius, when uncertainty heat index is 1.7°C
    Serial.print("Temperature feel people, when uncertainty heat index is 1.7°C: ");
    Serial.print(HI1);
    Serial.println("C  ");
    delay(5000);          //Wait 5 seconds before accessing sensor again.

 
}
