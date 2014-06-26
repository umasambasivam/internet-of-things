## Wiring up an ultrasonic sensor

Add this to the top of your Arduino sketch.

```c
const int trigPin = 2;
const int echoPin = 4;
```

Add this **to your setup function**.
```c
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
```

Add these utility functions to your sketch, preferably at the bottom.

```c
long getDistance() {
  long duration, d1, d2, d3;

  // get 3 readings, use middle one to avoid noise.
  d1 = timePulse(); 
  d2 = timePulse(); 
  d3 = timePulse(); 
  
  // Find the median of d1, d2 and d3.
  if (d1 <= d2 && d2 <= d3) {
    duration = d2;
  } else if (d1 <= d3 && d3 <= d2) {
    duration = d3;
  } else if (d2 <= d3 && d3 <= d1) {
    duration = d3;
  } else if (d2 <= d1 && d1 <= d3) {
    duration = d1;
  } else if (d3 <= d2 && d2 <= d1) {
    duration = d2;
  } else if (d3 <= d1 && d1 <= d2) {
    duration = d1;
  }
  
  // convert the time into a distance
  return microsecondsToCentimeters(duration);
}

long timePulse() {
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(80);  // was 10
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}
  
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
```

To measure distance, use the `getDistance()` function.
```c
long d = getDistance();
if (d < 30) {
  	// do whatever you want to do if the distance is small
}
```

