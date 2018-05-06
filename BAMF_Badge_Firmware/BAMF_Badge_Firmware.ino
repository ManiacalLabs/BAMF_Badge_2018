#include "SimonButton.h"
#include "util.h"
#include "rf.h"

// Pins for Adafruit 32u4 RFM69HCW Feather

#define BTN_R 10
#define BTN_G 12
#define BTN_B 9
#define BTN_Y 11

#define LED_R 18 //A0
#define LED_G 19 //A1
#define LED_B 20 //A2
#define LED_Y 21 //A3

#define NOTE_R 523 // C5
#define NOTE_G 659 // E5
#define NOTE_B 784 // G5
#define NOTE_Y 440 // B5

#define NOTE_FAIL 69 //G1
#define NOTE_START 1047 //C6

#define RAND_SEED_PIN 4 //A4

#define SEQ_LEN 32
#define SEQ_STR_LEN SEQ_LEN + 1

#define MODE_DEMO 0
#define MODE_PLAY 1
#define MODE_PLAY_RECV 2

#define SEQ_ON_LEN 500
#define SEQ_BTWN_ON 200

#define PLAY_HOLD_TIME 1200

byte _mode = MODE_DEMO;

char order[] = "RGBY";


//define buttons
SimonButton btns[] = {
  SimonButton(BTN_R, LED_R, NOTE_R, TONE_PIN),
  SimonButton(BTN_G, LED_G, NOTE_G, TONE_PIN),
  SimonButton(BTN_B, LED_B, NOTE_B, TONE_PIN),
  SimonButton(BTN_Y, LED_Y, NOTE_Y, TONE_PIN)
};

char seq_str[SEQ_STR_LEN];
char play_seq_str[SEQ_STR_LEN];
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

bool btn_states[4] = {false, false, false, false};
char btn_state_str[5] = {0,0,0,0,0};
bool check_all(){
  btn_states[0] = btns[0].check();
  btn_states[1] = btns[1].check();
  btn_states[2] = btns[2].check();
  btn_states[3] = btns[3].check();

  btn_state_str[0] = (btn_states[0] ? 'R' : '_');
  btn_state_str[1] = (btn_states[1] ? 'G' : '_');
  btn_state_str[2] = (btn_states[2] ? 'B' : '_');
  btn_state_str[3] = (btn_states[3] ? 'Y' : '_');

  return (btn_states[0] | btn_states[1] | btn_states[2] | btn_states[3]);
}

bool read_all(){
  bool result = false;
  result |= btns[0].read();
  result |= btns[1].read();
  result |= btns[2].read();
  result |= btns[3].read();
  return result;
}

void do_start_play() {
  all_on();
  play_tone_ms(NOTE_START, 500);

  while(read_all()){ delay(5); }

  stop_tone();
  all_off();
  delay(250);

  all_on();
  play_tone(NOTE_START);
  delay(500);
  all_off();
  delay(250);

  all_on();
  play_tone(NOTE_START);
  delay(500);
  all_off();
  delay(250);

  all_on();
  play_tone(NOTE_START);
  delay(500);
  all_off();

  delay(1000);
}

void check_play_hold() {
  read_all();
  if(btns[0].check_hold(PLAY_HOLD_TIME) && btns[1].check_hold(PLAY_HOLD_TIME)) {
    init_play();
    _mode = MODE_PLAY;

    do_start_play();
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
  memset(seq_str, 0, SEQ_STR_LEN);
  memset(play_seq_str, 0, SEQ_STR_LEN);
  play_seq_pos = seq_pos = 0;

  randomSeed(analogRead(RAND_SEED_PIN));
  for(int i=0; i<SEQ_LEN; i++) {
    seq_str[i] = order[ random(0, 4)];
  }

  send(seq_str, SEQ_LEN); //Send play sequence
  Serial.println("Begin Play!");
}

void play() {
  static byte i;
  static byte b;
  for(i=0; i<=seq_pos; i++) {
    switch(seq_str[i]) {
      case 'R':
        b = 0;
        break;
      case 'G':
        b = 1;
        break;
      case 'B':
        b = 2;
        break;
      case 'Y':
        b = 3;
        break;
      default:
        b = 0;
        break;
    }
    delay(SEQ_BTWN_ON);
    btns[b].on();
    delay(SEQ_ON_LEN);
    btns[b].off();
  }

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
      play_seq_str[play_seq_pos] = order[press];

      if(array_cmp(seq_str, play_seq_str, play_seq_pos+1, play_seq_pos+1))
      {
        if(play_seq_pos >= seq_pos) {
          result = true;
          break; //success with full sequence, exit
        }
      }
      else {
        result = false;
        break; // already failed, exit immediately
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
      play_tone(NOTE_FAIL);
      btns[0].on(false);
      btns[1].on(false);
      btns[2].on(false);
      btns[3].on(false);
      delay(500);
      stop_tone();
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

  rf_setup();
}

void loop() {
  // check_all();
  // return;

  switch(_mode) {
    case MODE_DEMO:
      demo();
      break;
    case MODE_PLAY:
    case MODE_PLAY_RECV:
      play();
      break;
  }

  char recv_buf[RF_MSG_LEN + 1];
  uint8_t len = RF_MSG_LEN;

  memset(recv_buf, 0, RF_MSG_LEN + 1);

  if(recv(recv_buf, &len)) {
    if(len >= SEQ_LEN){
      Serial.print("RECV: ");
      Serial.println(recv_buf);
      memset(seq_str, 0, SEQ_STR_LEN);
      memcpy(seq_str, recv_buf, SEQ_LEN);
      _mode = MODE_PLAY_RECV;
      play_seq_pos = seq_pos = 0;

      do_start_play();
    }
  }
}