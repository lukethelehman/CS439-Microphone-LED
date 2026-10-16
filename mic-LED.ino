const int sampleWindow = 50;  
const int AMP_PIN = A1;        
const int LED_PIN = 8;
unsigned int sample;
byte LED = LOW;
bool ready; 

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  unsigned long startMillis = millis(); 
  unsigned int peakToPeak = 0;   

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  sample = analogRead(AMP_PIN);

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AMP_PIN);

    if (sample > signalMax)
    {
      signalMax = sample;  // save just the max levels
    }
    if (sample < signalMin)
    {
      signalMin = sample;  // save just the min levels
    }
  }
  
  peakToPeak = signalMax - signalMin;  
  double volts = (peakToPeak * 5.0) / 1024;  
  Serial.println(volts);

  if (ready && volts > 2 ) {
    LED = !LED;
    ready = false; 
  }
  else if (volts < 1) {
    ready = true;
  }

  digitalWrite(LED_PIN, LED);

}