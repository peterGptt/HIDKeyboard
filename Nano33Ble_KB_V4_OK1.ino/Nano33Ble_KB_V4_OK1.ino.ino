  #include "Nano33BleHID.h"
  #include "signal_utils.h"
  
  /* -------------------------------------------------------------------------- */
  

Nano33BleKeyboard bleKb("KB");

// Tracking index for the end of the writing animation ticker.
int sTickerIndex = -1;

static const char kSentence[] = "hello HELLO";
static const int kNumTickerSteps = 4;

// How long it takes for the sentence to be written.
static const int kSentenceDurationMilliseconds = 4029;
//static const int kSentenceDurationMilliseconds = 1024;
// How long it takes before the sentence is rewritten.
static const int kSentenceDelayMilliseconds = 1977;

// How long one writing animation will run.
static const int kSentenceTotalTimeMilliseconds = kSentenceDurationMilliseconds + kSentenceDelayMilliseconds;

// Safeguard to terminate this mess of an app before going crazy.
static const int kTotalRuntime = 8 * kSentenceTotalTimeMilliseconds;

// Builtin LED animation delays when disconnect.
static const int kLedBeaconDelayMilliseconds = 1185;
static const int kLedErrorDelayMilliseconds = kLedBeaconDelayMilliseconds / 10;

// Builtin LED intensity when connected.
static const int kLedConnectedIntensity = 30;

unsigned long t = 0;

/* -------------------------------------------------------------------------- */

/** Utility struct to send a text through the Keyboard HID for a given time. */
struct SentenceWriter {
  std::string sentence;
  int current_index;
  unsigned long duration_ms;

  SentenceWriter(const char* str, unsigned long duration_ms)
    : sentence(str)
    , current_index(-1)
    , duration_ms(duration_ms)
  {}

  void write(HIDKeyboardService &kb, uint8_t c)
  {
    kb.sendCharacter(c);
  }
} stringWriter(kSentence, kSentenceDurationMilliseconds);

  /* -------------------------------------------------------------------------- */
int f1 = 0;
int f2 = 0;
int f3 = 0;
int f4 = 0;
int S = 0;
int A = A1;
  void setup()
  {
    // General setup.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(A, INPUT);

    Serial.begin(9600);
  
    // Initialize both BLE and the HID.
    bleKb.initialize();
  
    // Launch the event queue that will manage both BLE events and the loop.
    // After this call the main thread will be halted.
    MbedBleHID_RunEventThread();

  }

  void loop()
  {
    
  // When disconnected, we animate the builtin LED to indicate the device state.
  if (bleKb.connected() == false) {
    animateLED(LED_BUILTIN, (bleKb.has_error()) ? kLedErrorDelayMilliseconds
               : kLedBeaconDelayMilliseconds);//呼吸燈
    return;
  }
  
   analogWrite(LED_BUILTIN, kLedConnectedIntensity);
   auto *kb = bleKb.hid();
   digitalWrite(4, HIGH);

    boolean pin2State;
    boolean button4;      
    pin2State = digitalRead(4);      
    delay(10);     
    if (digitalRead(4) == pin2State)    
    {
      button4 = digitalRead(4); 
    } 
  if (!button4 && f4 == 0) {           
       stringWriter.write(*kb, 'o');
       f4 = 1;
  }else if(button4 && f4 == 1 ){
       stringWriter.write(*kb, 'i');
       f4 = 0;
    } else{
      } 
    float pin3State;
    float buttonA;     
    pin3State =0;
    pin3State = analogRead(A);     
    delay(10);     
    if (analogRead(A)<500 && pin3State<500)  
    {
      buttonA = 1; 
      
    }else{
      buttonA = 0;
        } 
      if (buttonA==1 && f3 == 0) {
        stringWriter.write(*kb, 'h');
        f3 = 1;
      }else if(buttonA==0 && f3 == 1){
        stringWriter.write(*kb, 'l');
        f3 = 0;
      } else{
        } 
  int button2 = digitalRead(2);
  Serial.println(button2);
  //Serial.print("");
        if ( !button2 && f2 == 0) {
        stringWriter.write(*kb, 's');
        f2 = 1;
      }else if(button2 && f2 == 1){
        stringWriter.write(*kb, 'e');
        f2 = 0;
      } else{
        }
  }
