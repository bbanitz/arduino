#include <Arduino.h>
#include <Stream.h>

class ESP8266_bb
{
public :
	ESP8266_bb();
	String readData(int *connectionId);
	void begin(Stream *serial,Stream *serialDebug);
	String sendData(String command, const int timeout, boolean debug);
	void sendClient(int connectionId, String message);
	void sendDebug(String message);
	void closeClient(int id);
private:
	Stream *serial;                                            
	Stream *serialDebug;

};   