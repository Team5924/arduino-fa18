#include <PS4USB.h>
#include <Servo.h>

USB Usb;
PS4USB PS4(&Usb);

// Takes a float and returns 0 if it is between -dead_zone and dead_zone or returns the same value otherwise
float deadband(float value, float dead_zone) {
  if(value > -dead_zone && value < dead_zone) {
    return 0.0f;
  }
  return value;
}

// Returns the position of the left analog stick in the X axis from -1.0 to 1.0
float get_left_stick_x() {
  if(PS4.connected()) {
    return deadband(((float)PS4.getAnalogHat(LeftHatX) - 127.0f) / 127.5f, 0.1f);
  } else {
    return 0.0f;
  }
}

// Returns the position of the left analog stick in the Y axis from -1.0 to 1.0
float get_left_stick_y() {
  if(PS4.connected()) {
    return deadband(((float)PS4.getAnalogHat(LeftHatY) - 127.0f) / -127.5f, 0.1f);
  } else {
    return 0.0f;
  }
}

// Returns the position of the right analog stick in the X axis from -1.0 to 1.0
float get_right_stick_x() {
  if(PS4.connected()) {
    return deadband(((float)PS4.getAnalogHat(RightHatX) - 127.0f) / 127.5f, 0.1f);
  } else {
    return 0.0f;
  }
}

// Returns the position of the right analog stick in the Y axis from -1.0 to 1.0
float get_right_stick_y() {
  if(PS4.connected()) {
    return deadband(((float)PS4.getAnalogHat(RightHatY) - 127.0f) / -127.5f, 0.1f);
  } else {
    return 0.0f;
  }
}

const int MOTOR_PINS[] = {3, 5, 6, 9, 10, 11, 13};
Servo MOTOR_OBJECTS[sizeof(MOTOR_PINS) / sizeof(MOTOR_PINS[0])] = {};

// Sets up motors
void setup_motors() {
  // Attach each Servo object to its corresponding pin
  for(int i = 0; i < sizeof(MOTOR_PINS) / sizeof(MOTOR_PINS[0]); i++) {
    MOTOR_OBJECTS[i].attach(MOTOR_PINS[i]);
  }
}

// Takes a motor index and a speed from -1.0 to 1.0 and runs the corresponding motor at that speed
void set_motor(int motor, float speed) {
  // Decrement the motor index so that "motor 1" maps to MOTOR_PINS[0]
  motor--;
  // Ignore if the specified motor is out-of-bounds
  if(motor < 0 || motor >= sizeof(MOTOR_PINS) / sizeof(MOTOR_PINS[0])) {
    return;
  }
  // Set the motor
  float output = 1500.0f + 500.0f * speed;
  MOTOR_OBJECTS[motor].writeMicroseconds(output);
}

void setup() {
  Usb.Init();
  setup_motors();
  /* START YOUR CODE HERE */
  /* END YOUR CODE HERE */
}

void loop() {
  Usb.Task();
  /* START YOUR CODE HERE */

  // Set motor 1 to value of the left-stick Y axis
  set_motor(1, get_left_stick_y());

  // Set motor 2 to value of the right-stick Y axis
  set_motor(2, get_right_stick_y());
  
  /* END YOUR CODE HERE */
}
