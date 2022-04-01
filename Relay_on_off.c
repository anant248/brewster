#define NumControlPins 8

int StartPin = 2;
int ControlPins[NumControlPins];

int LED = 13;

void setup() {

  for (int i = 0; i < NumControlPins; i++)
  {
    ControlPins[i] = i + StartPin;
  }
  for (int i = 0; i < NumControlPins; i++) {
    pinMode(ControlPins[i], OUTPUT);
    digitalWrite(ControlPins[i], LOW);
  }
}

void loop() {

  transfer_to_fermenter();
  fermentation_hold();
  fermentation_to_carbonation();
  carbonation_hold();
  carbonation_to_serve();
  
}

// helper functions //

// used to transfer wort from input to first keg (fermenter)
void transfer_to_fermenter() {
  // close all other valves
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, HIGH); // OFF
  digitalWrite(8, LOW);
  
  // open valves needed for flow to fermenter
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW); // active low: ON
  digitalWrite(9, HIGH); // activate pump for 10 minutes
  delay (10000);
  
}

// used to keep the CO2 escape valve open during fermentation
void fermentation_hold() {
  // close all other valves
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH); // OFF
  digitalWrite(7, HIGH); // OFF
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  
  // open valves needed for CO2 escape in fermentation keg
  digitalWrite(2, HIGH); // keep CO2 valve open for 1 week
  delay (10000) ;
  
}

// used to open valves to allow CO2 to transfer fluid from fermentation keg to carbonation keg
void fermentation_to_carbonation() {
  // close all other valves
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH); // OFF
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  
  // open valves needed for fluid transfer from keg 1 to filter to keg 2
  digitalWrite(7, LOW); // ON
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH); // fluid trasnfer between two kegs will take 15 minutes
  delay (10000);
    
}

// used to carbonate the wort in the carbonation keg
void carbonation_hold() {
  // close all other valves
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH); // OFF
  digitalWrite(7, HIGH); // OFF
  digitalWrite(9, LOW);
  
  // open valve needed to move high pressure CO2 into keg 2
  digitalWrite(8, HIGH); // carbonation will take a few days
  delay (10000);
}

// used to trasnfer the final beer from the carbonation keg to the final output
void carbonation_to_serve() {
  // close all other valves
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH); // OFF
  digitalWrite(7, HIGH); // OFF
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  
  // open valve needed to move the beer from keg 2 to output serve
  digitalWrite(5, HIGH);
  digitalWrite(3, HIGH); // beer output pour will take 10 minutes
  delay (10000);
  
}
