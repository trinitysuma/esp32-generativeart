# esp32-generativeart
module 2 of creative embedded systems

This project uses PlatformIO to create a generative message on an ESP32.  Please see the files in this repository.

## Materials
* ESP32
* Battery

## Using custom fonts
To use a custom font, you must use a TrueType to Adafruit GFX converter so the font in the header file can be properly referenced.  This creates a GFXFont type variable that can be referenced with "#define font &variable_name" in the main.cpp file.  TFT_eSPI also has built-in fonts.

## Defining generativity 
In this project, generativity refers to the degree of randomness present in the message.  In my implementation, the direction of the final line of text is randomly selected from up/down/left/right.  These directions are defined in 
```
enum ScrollDir {
    RIGHT_TO_LEFT,
    LEFT_TO_RIGHT,
    TOP_TO_BOTTOM,
    BOTTOM_TO_TOP
};
```

The function ```scrollLinesOnce``` chooses the scroll direction with a random seed defined by ```randomSeed(23)```.

Read more about the piece here: 

