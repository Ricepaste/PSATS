void setup()
{
    // int
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        String incomingByte = Serial.readString();
        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte);
        digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(1000);                     // wait for a second
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
        delay(1000);                     // wait for a second
    }
}
