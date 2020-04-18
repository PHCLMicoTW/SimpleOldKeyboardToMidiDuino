const int row1 = 5;
const int row2 = 6;
const int row3 = 7;
const int row4 = 8;
const int row5 = 4;
const int row6 = 3;
const int row7 = 2;
const int row8 = 1;

const int Scan1 = 11;
const int Scan2 = 12;
const int Scan3 = 13;

int LastScan = B00000111;

// For 54 Key keybroad
uint8_t keyToMidiMap[56];
boolean keyPressed[56];
int noteVelocity = 127;

void setup() {
	
	for (int i = 0; i < 7; i++) {
		keyToMidiMap[i * 8 + 0] = 48 + i * 8;
		keyToMidiMap[i * 8 + 1] = 41 + i * 8;
		keyToMidiMap[i * 8 + 2] = 42 + i * 8;
		keyToMidiMap[i * 8 + 3] = 43 + i * 8;
		keyToMidiMap[i * 8 + 4] = 44 + i * 8;
		keyToMidiMap[i * 8 + 5] = 45 + i * 8;
		keyToMidiMap[i * 8 + 6] = 46 + i * 8;
		keyToMidiMap[i * 8 + 7] = 47 + i * 8;
	}

	pinMode(Scan1, INPUT);
	pinMode(Scan2, INPUT);
	pinMode(Scan3, INPUT);

	pinMode(row1, INPUT);
	pinMode(row2, INPUT);
	pinMode(row3, INPUT);
	pinMode(row4, INPUT);
	pinMode(row5, INPUT);
	pinMode(row6, INPUT);
	pinMode(row7, INPUT);
	pinMode(row8, INPUT);

    Serial.begin(31250);
	
	delay(500);
}

int col = 0;

void loop() {
	int ScanNow = digitalRead(Scan1) * 4 + digitalRead(Scan2) * 2 + digitalRead(Scan1) * 1;
	while(ScanNow == LastScan){ ScanNow = digitalRead(Scan1) * 4 + digitalRead(Scan2) * 2 + digitalRead(Scan1) * 1; }
	if(digitalRead(Scan1) == 1) col = 0; else col++; LastScan = ScanNow;
	
	Serial.write("Reading...");
	
	int KeyInput[] = { digitalRead(row1), digitalRead(row2), digitalRead(row3), digitalRead(row4), digitalRead(row5), digitalRead(row6), digitalRead(row7), digitalRead(row8) };

	for (int i = 0; i < 8; i++) {
		int NowCol = col + i * 8;
		if (KeyInput[i] != 0 && !keyPressed[NowCol]) {
			keyPressed[NowCol] = true;
			noteOn(0x91, keyToMidiMap[NowCol], noteVelocity);
		}
		if (KeyInput[i] == 0 && keyPressed[NowCol]) {
			keyPressed[NowCol] = false;
			noteOn(0x91, keyToMidiMap[NowCol], 0);
		}
	}
}


void noteOn(int cmd, int pitch, int velocity) {
  	Serial.write(cmd);
	Serial.write(pitch);
	Serial.write(velocity);
}