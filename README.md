RGBStripBluetoothController

This is an ongoing project.

The controller uses hex input (00 -> FF) through serial to create objects with those inputs as arguments. The base style class holds all needed functions, which means any subclasses can have their own drawing method, whilst only needing to call the base-classes draw funtion.

Due to memory limits, I will have to find ways to optimise. First one is instead of passing hex, convert the number into a character first. That way all we need to do read one character as a integer to get the value, rather than reading two and converting it to an integer.
Another optimisation would be to use the built-in EEPROM to store the styles that loop. Right now I delete the current object before even reading the serial, due to the serial reading taking up SRAM (where the style object is stored) which quickly fills it up.
One more optimisation could be within the objects themselves i.e. only use esssential variables.
