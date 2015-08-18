## Websocket Server for ESP2866

This library implements a Websocket server running on an ESP2866 Board e.g NodeMCU. It's based on the [proposed standard][1] published December 2011 which is supported in the current versions (June 2012) of Firefox, Chrome, and Safari 6.0 beta (not older Safari, unfortunately) and thus is quite usable.

The implementation in this library has (still) some restrictions:

* The server **only** handles TXT frames.
* The server **only** handles **single byte** chars.
* The server **only** accepts **final** frames with maximum payload length of 64 bytes. No fragmented data, in other words.
* For now, the server silently ignores all frames except TXT and CLOSE.
* The amount of simultaneous connections may be limited by RAM or hardware.
* There's no keep-alive logic implemented.

_Required headers (example):_

	GET /whatever HTTP/1.1
	Host: server.example.com
	Upgrade: websocket
	Connection: Upgrade
	Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
	Sec-WebSocket-Version: 13

The server checks that all of these headers are present, but only cares that the version is 13.

_Response example:_

	HTTP/1.1 101 Switching Protocols
	Upgrade: websocket
	Connection: Upgrade
	Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=

The last line is the Base64 encoded SHA-1 hash of the key with a concatenated GUID, as specified by the standard.

**Daniel O'Neill:** ***Compared to the original, this library consumes significantly less RAM and provides additional functionality.***

### Requirements

* Arduino IDE 1.6.5 or greater
* esp2866 for Arduino IDE 1.6.5-947-g39819f0 or later
* An ESP2866 Board e.g NodeMCU 0.9 or 1.0
* A Websocket client that conforms to version 13 of the protocol

### Getting started

Install the library to "libraries" folder in your Arduino sketchbook folder. For example, on a mac that's `~/Documents/Arduino/libraries`.

Try the supplied echo example together with the the [web based test client][2] to ensure that things work.

Start playing with your own code and enjoy!

### Feedback

I'm a pretty lousy programmer, at least when it comes to Arduino, and it's been 15 years since I last touched C++, so do file issues for every opportunity for improvement.

Oh by the way, quoting myself:

> Don't forget to place a big ***fat*** disclaimer in the README. There is most certainly bugs in the code and I may well have misunderstood some things in the specification which I have only skimmed through and not slept with. So _please_ do not use this code in appliancies where living things could get hurt, like space shuttles, dog tread mills and Large Hadron Colliders.


[1]: http://datatracker.ietf.org/doc/rfc6455/?include_text=1 "Protol version implemented here"
[2]: http://www.websocket.org/echo.html "Echo Test client"
