#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

#define RF69_FREQ 915.0

#define RFM69_CS      8
#define RFM69_INT     7
#define RFM69_RST     4
#define LED           13

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);
RHReliableDatagram rfman(rf69, 0);

void rf_setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rfman.init()) {
    Serial.println("RFM69 radio init failed");
    // while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  // uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  //                   0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  // rf69.setEncryptionKey(key);

  // pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

void send(char *c, uint8_t l) {
    Serial.print("Send: ");
    Serial.println(c);

    rfman.sendtoWait(c, l, RH_BROADCAST_ADDRESS);
}

#define RF_MSG_LEN 64
bool recv(char * buf, uint8_t * len) {
    return rfman.recvfromAck(buf, len);
}