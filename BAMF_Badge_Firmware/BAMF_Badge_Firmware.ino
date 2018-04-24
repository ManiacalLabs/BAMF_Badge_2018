#include "SimonButton.h"
#include "util.h"

// Pins for Adafruit 32u4 RFM69HCW Feather
#define TONE_PIN 6

#define BTN_R 10
#define BTN_G 12
#define BTN_B 9
#define BTN_Y 11

#define LED_R 18 //A0
#define LED_G 19 //A1
#define LED_B 20 //A2
#define LED_Y 21 //A3

#define NOTE_R 2093 // A4
#define NOTE_G 2637 // E3
#define NOTE_B 3136 // E4
#define NOTE_Y 3961 // C#4

#define NOTE_FAIL 460 //C2

#define SEQ_LEN 6

#define MODE_DEMO 0
#define MODE_PLAY 1

#define SEQ_ON_LEN 500
#define SEQ_BTWN_ON 200

#define PLAY_HOLD_TIME 1200

byte _mode = MODE_DEMO;


//define buttons
SimonButton btns[] = {
  SimonButton(BTN_R, LED_R, NOTE_R, TONE_PIN),
  SimonButton(BTN_G, LED_G, NOTE_G, TONE_PIN),
  SimonButton(BTN_B, LED_B, NOTE_B, TONE_PIN),
  SimonButton(BTN_Y, LED_Y, NOTE_Y, TONE_PIN)
};

byte seq[SEQ_LEN];
byte play_seq[SEQ_LEN];
byte seq_pos;
byte play_seq_pos;

void all_off(){
  btns[0].off();
  btns[1].off();
  btns[2].off();
  btns[3].off();
}

void all_on(){
  btns[0].on();
  btns[1].on();
  btns[2].on();
  btns[3].on();
}

void check_all(){
  btns[0].check();
  btns[1].check();
  btns[2].check();
  btns[3].check();
}

bool read_all(){
  bool result = false;
  result |= btns[0].read();
  result |= btns[1].read();
  result |= btns[2].read();
  result |= btns[3].read();
  return result;
}

void check_play_hold() {
  Serial.println("check play");
  read_all();
  if(btns[0].check_hold(PLAY_HOLD_TIME) && btns[1].check_hold(PLAY_HOLD_TIME)) {
    init_play();
    _mode = MODE_PLAY;

    all_on();
    tone(TONE_PIN, NOTE_FAIL, 500);

    while(read_all()){ delay(5); }

    all_off();
    delay(1000);
  }
}

void demo(){
  static byte c = 0;
  all_off();
  delay(SEQ_BTWN_ON);
  // btns[random(0, 4)].on(false);
  btns[c].on(false);
  c++;
  if(c>=4){c = 0;}
  delay(SEQ_ON_LEN);

  check_play_hold();
}

void init_play() {
  memset(seq, 0, SEQ_LEN);
  memset(play_seq, 0, SEQ_LEN);
  play_seq_pos = seq_pos = 0;
  randomSeed(0);
  Serial.println("Begin Play!");
}

void play() {
  // all_off();
  Serial.println("play");

  // Add to and play sequence
  seq[seq_pos] = random(0, 4);

  static byte i;
  static byte b;
  for(i=0; i<=seq_pos; i++) {
    Serial.print(seq[i]);
    Serial.print(" ");
    delay(SEQ_BTWN_ON);
    btns[seq[i]].on();
    delay(SEQ_ON_LEN);
    btns[seq[i]].off();
  }

  Serial.println("\n");

  static long timeout;
  static int8_t press;
  static bool result;

  // wait for response
  timeout = millis();
  press = -1;
  play_seq_pos = 0;
  result = false;
  while((millis() - timeout) < 5000) {
    if(btns[0].check()) { press = 0; }
    else if(btns[1].check()) { press = 1; }
    else if(btns[2].check()) { press = 2; }
    else if(btns[3].check()) { press = 3; }

    if(press >= 0) {
      timeout = millis(); // reset timeout
      play_seq[play_seq_pos] = press;

      //if enough presses, check
      if(play_seq_pos >= seq_pos) {
        result = array_cmp(seq, play_seq, SEQ_LEN, SEQ_LEN);
        break; // exit loop, we're done
      }

      play_seq_pos++;
    }
    press = -1;
  }

  if(result){
    seq_pos++;
    if(seq_pos >= SEQ_LEN) {
      Serial.println("WIN!");
      btns[0].on(false);
      btns[1].on(false);
      btns[2].on(false);
      btns[3].on(false);
      delay(500);
      all_off();
      for(i=0; i<4; i++){
        for(b=0; b<4; b++){
          btns[b].on();
          delay(200);
          btns[b].off();
        }
      }
      delay(1000);
      _mode = MODE_DEMO;
      return;
    }
    else {
      delay(500);
    }
  }
  else{
    Serial.println("FAIL");
    for(i=0; i<4; i++){
      tone(TONE_PIN, NOTE_FAIL);
      btns[0].on(false);
      btns[1].on(false);
      btns[2].on(false);
      btns[3].on(false);
      delay(500);
      noTone(TONE_PIN);
      all_off();
      delay(250);
    }
    _mode = MODE_DEMO;
    return;
  }
}

void setup() {
  Serial.begin(115200);
  // while(!Serial){}
  init_play();
  randomSeed(analogRead(4));
}

void loop() {
  switch(_mode) {
    case MODE_DEMO:
      demo();
      break;
    case MODE_PLAY:
      play();
      break;
  }

  // check_all();
}