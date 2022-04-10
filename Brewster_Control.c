#define HIGH  1
#define LOW  0
#define NumSolenoids 8 // number of solenoids
int StartPin = 2; // first pin used on arduino, all pins should be used increasingly and sequentially
int RelayNum[NumSolenoids+1]; // Array to convert solenoid # to pin #
int Motor = StartPin + NumSolenoids; // Motor is connected to first pin above last solenoid pin
int RelayOffState [NumSolenoids + 1]; // Array to define when relays are off
int RelayOnState [NumSolenoids + 1]; // Array to define when relays are off

/*
   RELAY CONFIGURATION:

   RELAY 0 = Primary Fluid Container to Pump Solenoid
   RELAY 1 = Low Pressure Input Solenoid
   RELAY 2 = Spunding Valve Output Solenoid
   RELAY 3 = Filter to Keg 2 Solenoid
   RELAY 4 = High Pressure Input Solenoid
   RELAY 5 = Additive Fluid to Pump Solenoid
   RELAY 6 = Keg 1 Open Output Solenoid
   RELAY 7 = Keg 2 Open Output Solenoid
   RELAY 8 = Pump
*/

void setup() {

  // Define OFF & ON states of relay (active high vs active low)
  for (int i = 0; i < NumSolenoids; i++) {
    RelayOffState [i] = HIGH;
    RelayOnState [i] = LOW;
  }
  RelayOffState [NumSolenoids] = LOW; // Motor uses only active HIGH relay
  RelayOnState [NumSolenoids] = HIGH; // Motor uses only active HIGH relay

  //Define relay control pins by relay #
  for (int i = 0; i <= NumSolenoids; i++)
  {
    RelayNum[i] = i + StartPin;
  }

  //define control pins as output, and set to OFF
  for (int i = 0; i < NumSolenoids; i++) {
    pinMode(RelayNum[i], OUTPUT);
    digitalWrite(RelayNum[i], HIGH);
  }
  pinMode(Motor, OUTPUT);
  digitalWrite(Motor, LOW);
}



void loop() {

delay (1000);
Stage_1 (8000);
Stage_2 (8000);
Stage_3 (5000);
Stage_4 (20000);
Stage_5 (3000);
Stage_6 (3000);
Stage_7 (20000);
exit (0);

}


int Stage_1(int t) { //transfer liquid from container to first keg
  RelayOn(6); // Allow open flow to prevent pressure build up
  delay(5000);
  RelayOn(0); // Allow flow from container
  RelayOn(8); // Activate Motor

  delay(t); // how long to pump for

  RelayOff(8); // turn off pump
  RelayOff(0); // Close valves
  RelayOff(6);

  delay(1000);
  
}


int Stage_2(int t) { //Insert Additives
  RelayOn(6); // Allow open flow to prevent pressure build up
  RelayOn(5); // Allow flow from additive container
  RelayOn(8); // Activate Motor

  delay(t); // how long to pump for

  RelayOff(8); // turn off pump
  RelayOff(5); // Close valves
  RelayOff(6);

  delay(1000);
}

int Stage_3(int t) { //Active Fermentation

  RelayOn(1); // Simulate CO2 build up with low pressure CO2
  RelayOn(7);

  delay (4000);

  RelayOff(1); // Close CO2 Valve
  RelayOff(7);
  
  RelayOn(2); // Open Spunding Valve

  delay(t); // how long to ferment for

  RelayOff(2); // Close Valve

  delay(1000);
}

int Stage_4(int t) { //Transfer Fermented Beer to 2nd Keg Through Filter
  RelayOn(3); // Open Filter Valve
  RelayOn(7); // Allow flow output from container
  RelayOn(1); // Activate Low Pressure CO2

  delay(t); // how long to pump for
  delay(t);

  RelayOff(1); // turn off CO2
  RelayOff(7); // Close valves
  RelayOff(3);

  delay(1000);
}

int Stage_5(int t) { //Carbonate
  
  RelayOn(4); // Activate High Pressure CO2

  delay(t); // how long to pump for

  RelayOff(4); // turn off CO2

  delay(1000);
}

int Stage_6(int t) { //Depressurize
  
  RelayOn(7); // Open 2nd Keg Output Valve

  delay(t); // how long to depressurize for

  RelayOff(7); // Close Valve

  delay(1000);
}

int Stage_7(int t) { //Serving Pressure
  
  RelayOn(1); // Activate Low Pressure CO2
  RelayOn(3); // Allow pressure into keg 2

  delay(t); // how long to serve for

  RelayOff(1); // Close Valve
  RelayOff(3);

  delay(1000);
}



int RelayOff (int Relay) {
  digitalWrite (RelayNum[Relay], RelayOffState[Relay]);
}

int RelayOn (int Relay) {
  digitalWrite (RelayNum[Relay], RelayOnState[Relay]);
}
