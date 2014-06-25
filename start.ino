#include <SPI.h>
#include <Ethernet.h>

// Your Arduino Ethernet's MAC address.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Your Arduino Ethernet's IP address (192.168.1.177). This is the URL that you type into the browser URL bar.
IPAddress ip(192,168,1,177);
// Tell your Ethernet server to listen on port 80 (the standard port for HTTP requests)
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  // Wait until serial is loaded.
  while (!Serial) { }
   
  // start the Ethernet connection and the server.
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  // If there is an incoming client
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    
    // While the client is connected and waiting for data
    while (client.connected()) {
      // Check for HTTP timeout
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          
          // The standard HTTP response header for a successful request.
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
	        client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          
          // ************************************************
          // ************************************************
          // BELOW IS WHERE YOU PRINT OUT YOUR HTML PAGE. ***
          // ************************************************
          // ************************************************
          client.println("<html>");
            client.println("<head>");
              client.println("<title>Arduino Ethernet</title>");
            client.println("</head>");
            
            client.println("<body>");
            
            client.println("</body>");
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
