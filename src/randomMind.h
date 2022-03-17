#define EVERY_X_SECONDS 10

#define MIND_PROGMEM

#ifdef MIND_PROGMEM
const char mind1[] PROGMEM = "ksit";
const char mind2[] PROGMEM = "kbalance";
const char mind3[] PROGMEM = "kpee";
const char mind4[] PROGMEM = "kpu";
const char mind5[] PROGMEM = "m0 -45 1 20 0 45 0 0";
const char mind6[] PROGMEM = "kck";
const char mind7[] PROGMEM = "kjy";
const char mind8[] PROGMEM = "kvt";
const char mind9[] PROGMEM = "i0 -45 1 45";
const char mind10[] PROGMEM = "m2 0 2 -20 2 -40";
const char mind11[] PROGMEM = "o ";

const char* const mindList[] PROGMEM = {mind1, mind2, mind3, mind4, mind5, mind8, mind11,
#ifdef BITTLE
                                        mind6, mind7,
#else
                                        mind9, mind10
#endif
                                       };

#else
const char *mindList[] = {"ksit", "kbalance", "kpee", "kpu", "m0 -45 1 30 0 45 0 0", "kvt", "o ",
#ifdef BITTLE
                          "kck", "kjy",
#else
                          "M0 -45 1 10", "m2 0 2 -20 2 20"
#endif
                         };
#endif
long idleTimer;
byte randomMindListLength = sizeof(mindList) / 2;
void randomMind() {
  int randomChoice = random() % (randomMindListLength * EVERY_X_SECONDS); //on average every EVERY_X_SECONDS seconds
  if (millis() - idleTimer > 1000) {//every second throw a dice
    idleTimer = millis();
    if (randomChoice < randomMindListLength) {
#ifdef MIND_PROGMEM
      strcpy_P(newCmd, (char *)pgm_read_word(&mindList[randomChoice]));
      token = newCmd[0];
      PTL(newCmd);
      strcpy(newCmd, newCmd + 1);// this is duable only because newCmd+1 is after newCmd!
#else
      token = mindList[randomChoice][0];
      strcpy(newCmd, mindList[randomChoice] + 1);
#endif
      newCmdIdx = 5;
    }
  }
}
