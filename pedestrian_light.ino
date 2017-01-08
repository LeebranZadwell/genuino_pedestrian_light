/*
 * pedestrian_light.ino
 * 
 * Acts like a pedestrian controller light.
 * For those unfamiliar, this means the green light
 * blinks until someone hits the light - then a kinda
 * random time after the light is solid green, then yellow, and finally red.
 * 
 * https://clsimplex.com
 * Levon Zadravec-Powell
 * 
 * Legal stuff: Completely free software. As is. We promise/guarantee nothing.
 * By reading this sentence you owe us 5 dollars (CAD naturally). 10 dollars, actually.
 * 
 * This has some default values.
 * Change these depending on where you hook up your LEDs!
 * 
 * The reason we use const int GREEN_ANODE_PIN is because you can
 * customize this program to work with whatever breadboard arrangement you've
 * put together. Notice how there are no numbers for pins in the program.
 * You declare them in the constants. This makes the program more flexible,
 * which is a very good thing!
 */
const int GREEN_ANODE_PIN  = 4;
const int YELLOW_ANODE_PIN = 3;
const int RED_ANODE_PIN    = 2;
const int BUTTON_INPUT_PIN = 5;

int switch_state = 0;
int pressed      = 0;
int loops        = 0;

void setup() {
  pinMode(GREEN_ANODE_PIN,  OUTPUT);
  pinMode(YELLOW_ANODE_PIN, OUTPUT);
  pinMode(RED_ANODE_PIN,    OUTPUT);
  pinMode(BUTTON_INPUT_PIN, INPUT);
  pinMode(LED_BUILTIN,      OUTPUT);

  // We will use the built-in LED to help tell us if the machine knows we pressed the button.
  digitalWrite(LED_BUILTIN, LOW); // Default is off.
}

/**
 * This loop controls:
 * 1. The blinking green light
 * 2. Has the button been pushed?
 * 3. The new pattern once the button has been pushed.
 * 
 * Notice how it really doesn't matter how many times the
 * button has been pushed! You can push it a million times and
 * it will not speed it up!
 */
void loop() {
  switch_state = digitalRead(5);
  
  if ( switch_state == HIGH && pressed == 0 ) {
    pressed = 1;
    digitalWrite(LED_BUILTIN, HIGH); // This provides some feedback so we can tell it is active.
  }
  
  // Blinking green light
  delay(800);
  digitalWrite(GREEN_ANODE_PIN,HIGH);
  delay(800);
  digitalWrite(GREEN_ANODE_PIN,LOW);
  // End of blinking green light

  /* 
   * This is a bit fancy. 
   * 1. Is the button pressed?
   * 2. How many times has the light blinked green?
   * 
   * The reason we use loops % 3 == 0 is so the light
   * doesn't immediately change.
   * 
   * In real life, it can appear somewhat random.
   */
  if ( pressed == 1 && loops % 3 == 0 ) {
    pressed = 0;
    loops   = 0;
    
    digitalWrite(GREEN_ANODE_PIN,HIGH);
    delay(3000);
    digitalWrite(GREEN_ANODE_PIN,LOW);
    digitalWrite(YELLOW_ANODE_PIN,HIGH);
    delay(2000);
    digitalWrite(YELLOW_ANODE_PIN,LOW);
    digitalWrite(RED_ANODE_PIN,HIGH);
    delay(4000);
    digitalWrite(RED_ANODE_PIN,LOW);
    digitalWrite(LED_BUILTIN, LOW); // Turn user feedback off.
  }

  /*
   * We check the button a press a second time
   * so you don't have to hold the button down
   * for the machine to realize you have it pressed.
   */
  if ( switch_state == HIGH && pressed == 0 ) {
    pressed = 1;
    digitalWrite(LED_BUILTIN, HIGH); // This provides some feedback so we can tell it is active.
  }
  
  loops++;
}
