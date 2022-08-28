void setup()
{
    for (int i = 2; i < 14; i++)
    {
        pinMode(i, OUTPUT);
    }
    Serial.begin(115200);
}

// the loop function runs over and over again forever
String incomingByte = "";
double ap;
double voltage, voltage_sum;
int counter = 0;
long long last, now;
void loop()
{
    last = millis();
    counter = 0;
    voltage_sum = 0.0;
    if (Serial.available() > 0)
    {
        incomingByte = Serial.readString();
        Serial.print("I received: ");
        Serial.println(incomingByte);
        if (incomingByte == "s\n")
        {
            solar_mode();
        }
        else if (incomingByte == "p\n")
        {
            public_elec_mode();
        }
    }

    do
    {
        now = millis();
        // voltage = analogRead(A2);
        // voltage = analogRead(A2) * 0.0198333333333333;
        voltage = analogRead(A2) * analogRead(A2) * (-0.000000585) + analogRead(A2) * 0.020823;
        voltage_sum += voltage;
        counter++;
    } while (now - last < 1000);
    power_check(voltage_sum, counter);
    voltage = voltage_sum / counter;
    Serial.println("solar panel voltage : " + String(voltage) + "V");
    // delay(1500);
}

void normal_mode(int B_voltage, int counter)
{
    // Serial.println("normal electricity mode is ON");
    if (B_voltage / counter >= 9.0)
    {
        Battery_100_Percent();
    }
    else if (B_voltage / counter >= 7.0)
    {
        Battery_75_Percent();
    }
    else if (B_voltage / counter >= 5.0)
    {
        Battery_50_Percent();
    }
    else if (B_voltage / counter >= 3.0)
    {
        public_elec_mode();
        Serial.println("Battery power < 25%");
        Serial.println("Preserving power for emergency");
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(10, LOW);
        digitalWrite(13, LOW);
    }
}

void emergency_mode(double B_voltage, int counter)
{
    if (B_voltage / counter >= 9.0)
    {
        Battery_100_Percent();
    }
    else if (B_voltage / counter >= 7.0)
    {
        Battery_75_Percent();
    }
    else if (B_voltage / counter >= 5.0)
    {
        Battery_50_Percent();
    }
    else if (B_voltage / counter >= 3.0)
    {
        Battery_25_Percent();
    }
}
void solar_mode()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    Serial.println("solar_mode is ON");
}

void public_elec_mode()
{
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("public_elec_mode is ON");
}

void power_check(double B_voltage, int counter)
{
    // check if the public electricity is available
    double voltage = analogRead(A0) * analogRead(A0) * (-0.000000585) + analogRead(A0) * 0.020823;
    if (voltage < 2)
    {
        emergency_mode(B_voltage, counter);
    }
    else
    {
        normal_mode(B_voltage, counter);
    }
}

void Battery_25_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power < 25%");
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
}
void Battery_50_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power 25% ~ 50%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
}
void Battery_75_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Battery is ON");
    Serial.println("Battery power 50% ~ 75%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
}
void Battery_100_Percent()
{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    Serial.println("Battery is ON");
    Serial.println("Battery power 75% ~ 100%");
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(13, HIGH);
}