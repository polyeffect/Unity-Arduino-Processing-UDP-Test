import hypermedia.net.*;

UDP udp;  // define the UDP object

Boolean isChange = false;

void setup() {
  size(200, 200);
  noStroke();
  
  udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000
  udp.log( true );         // <-- printout the connection activity
  udp.listen( true );           // and wait for incoming message
}

void draw()
{
  background(0);
  
  if (isChange) fill(180, 255, 255);
  else fill(255, 165, 209);
  rect(0,0, 200, 200);
}

void keyPressed() {
  String ip       = "192.168.0.116"; // the remote IP address
  int port        = 8888;        // the destination port

  udp.send("Hello World", ip, port );   // the message to send
}

//void receive( byte[] data ) {          // <-- default handler
void receive( byte[] data, String ip, int port ) {   // <-- extended handler
  
  data = subset(data, 0, data.length-2);
  String message = new String( data );
  
  println( "receive: \""+message+"\" from "+ip+" on port "+port );
  
  isChange = !isChange;
  //udpSend();
}

void udpSend() {
  String ip       = "192.168.0.116"; // the remote IP address
  int port        = 8888;        // the destination port

  udp.send("Hello World", ip, port );
}
