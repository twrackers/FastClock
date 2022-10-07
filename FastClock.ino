#include <Streaming.h>
#include <SPI.h>

//#define SEEED_ETH_1
#define SEEED_ETH_2
//#define ENC28J60

#if defined(SEEED_ETH_1)
  #include <Ethernet.h>
  #include <EthernetUdp.h>
#elif defined(SEEED_ETH_2)
  #include <EthernetV2_0.h>
  #include <EthernetUdpV2_0.h>
  #define W5200_CS (10)
  #define SDCARD_CS (4)
#elif defined(ENC28J60)
  #include <UIPEthernet.h>
#else
  #error Must define SEEED_ETH_1, SEEED_ETH_2, or ENC28J60
#endif

#include <ArtNet.h>

#include "DigitalClock.h"
#include "TimePiece.h"
#include "ColorSpace.h"
#include "Sunlight.h"

#define CLOCKS 3
#define CLOCK_BASE_ADDR 0x70

#define LIGHTS 4
#define COLORS 3
#define CHANNELS (LIGHTS * COLORS)

DigitalClock* clockFace[CLOCKS];
TimePiece clock(24, 12);

ArtNet dmx(CHANNELS);

byte mac[] = {
  0x01, 0x23, 0x45, 0x67, 0x89, 0x20
};
IPAddress ipLocal(10, 0, 0, 120);
IPAddress ipRemote(10, 0, 0, 121);
IPAddress ipBroadcast(255, 255, 255, 255);
unsigned int portLocal = 0x1937;
unsigned int portRemote = 0x1936;  // Art-Net port
unsigned int portBroadcast = 0x1955;

EthernetUDP udp;
size_t pktBufferSize;
byte* pktBuffer;

byte bcCounter;

byte channels[LIGHTS][COLORS];

float hue = 0.0;

void setup()
{
#if defined(SDCARD_CS)
  // If v2 Ethernet shield, disable SD card.
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);
#endif

  Serial.begin(115200);
  
  Ethernet.begin(mac, ipLocal);
  udp.begin(portLocal);
  
  pktBufferSize = dmx.getBufferSize();
  pktBuffer = dmx.getBuffer();

  bcCounter = 0;

  for (byte i = 0; i < CLOCKS; ++i) {
    clockFace[i] = new DigitalClock((CLOCK_BASE_ADDR + i), clock);
//    Serial << "Clock @ address 0x" << _HEX(CLOCK_BASE_ADDR + i)
//      << (clockFace[i]->isConnected() ? " is " : " is not ")
//      << "connected." << endl;
  }

  clock.run();
}

const float skyAngles[LIGHTS] = {
  120.0, 150.0, 210.0, 240.0
};

void loop()
{
  if (clock.update()) {
    
    if (clock.tic()) {
      for (byte c = 0; c < CLOCKS; ++c) {
        clockFace[c]->showTime();
      }
    }

    float sunAngle = SunAngle(clock.read());
    for (byte l = 0; l < LIGHTS; ++l) {
      ColorRGB rgb = skyColor(sunAngle, skyAngles[l]);
      channels[l][0] = (byte) (rgb.r * 255.0);
      channels[l][1] = (byte) (rgb.g * 255.0);
      channels[l][2] = (byte) (rgb.b * 255.0);
    }
    dmx.encode((byte*) channels);
    udp.beginPacket(ipRemote, portRemote);
    udp.write(pktBuffer, pktBufferSize);
    udp.endPacket();

    byte bc[4];
    clock.read(bc[0], bc[1], bc[2]);
    bc[3] = bcCounter++;
    udp.beginPacket(ipBroadcast, portBroadcast);
    udp.write(bc, sizeof bc);
    udp.endPacket();
    
//    Serial << clock.read() << ' ';
//    for (byte i = 0; i < pktBufferSize; ++i) {
//      Serial << _HEX(pktBuffer[i]) << ' ';
//    }
//    Serial << endl;
  }
}
