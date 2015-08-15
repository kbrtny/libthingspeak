# ThingSpeak C library (libthingspeak)

Library forked from gabrield and added functionality to add more then one value (field1, field2, filed3 for example) 
with one call to thinkspeak.com. It can be extended to all  8 fields that are accepted by thingspeak.com

As a reference note, channels on thingspeak can only be updated once every 15 seconds, so it is most efficient to combine field updates into one channel update.

## Beta Release Notes

  The goals of the design had been focused on supporting *unix* platforms
  and providing simple wrapper methods that will enable users to implement
  a very functional ThingSpeak agent application on an platform that supports BSD sockets.

  This library is still in early development stage, then do not expect too much from it,
  but it's being improved as  far as my needs go - and maybe yours (just let me know 
  or send a pull request :D ).

## Get started

Run this from the shell:

      git clone  https://github.com/bcatalin/libthingspeak
      cd libthingspeak
      make all
      sudo make install

## Contributing

  I use GitHub fork/pull-request model and encourage users to contribute
  changes back. The general guideline is to submit no more then one feature
  in a single pull-request and each individual commit should contain only
  related changes.
