# JumpGame

This is probably not useful for anyone else, but I made an Arduino based jumping game.   Mostly just for myself at this point.

If anyone wants to build something like this, here's the parts I used:

Floor pressure pad/switch: http://www.trossenrobotics.com/store/p/3508-Switch-Floor-Mat-14-Inches-x-30-Inches.aspx

This is jus an on/off switch, I used an old telephone cable to connect it to the digital read pins.  It didn't register my 80 lb daughter, so I had to duct tape some stiff wires underneath it to make it press down.  I also stuck a yoga mat underneath it and a doormat on top to keep it from getting worn out.

(I think I got 2) Adafruit NeoPixel Digital RGB LED Strip - Black 30 LED - BLACK https://www.adafruit.com/product/1460
Counter: https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack

I used this to make a counter: https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack  I tried making a counter for another project using a cheaper product and ended up with a rats nest of wires and writing custom code to display numbers.  This is vastly easier.  You can just say matrix.println(1234) and it shows 1234.

I used an Arduino Diecimila (really old; it was lying around).  Probably any modern one that looks like that would work.

I used some kids wading pool I think we got at Home Depot and ziptied the NeoPixels in.

![Jump Rope Image](https://github.com/lhenkel/JumpGame/blob/master/JumpRoper.jpg)
