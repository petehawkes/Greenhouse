#include "Greenhouse.h"

void Setup ()
{ // create the image from file
    Image *b = new Image ("images/page1.png");
    // place the image centered on the feld (i.e. window)
    b -> SlapOnFeld ();
    
    // set the color of the border
    b -> SetBorderColor (Color (1, 0, 0));
    // set the width of the border (in millimeters)
    b -> SetBorderWidth (5.0);
    // remove the border color
    b -> NoBorderColor ();
    
    // set backing color to black
    b -> SetBackingColor (Color (0.49, 0.59, 0.49, 1.0));
    // remove the backing color
    b -> NoBackingColor ();
    
    // set the radius of the image corners
    b -> SetBorderColor (Color (0.79, 0.79, 0.89, 1.0));
    b -> SetCornerRadius (0.5 * b -> Width());
    
    float64 aspect = b -> Aspect ();
    INFORM ("aspect = " + FLOAT (aspect));
    
    // set the size in terms of millimeters
    b -> SetSize (100); //size in mm
    // set the size relative to the feld
    b -> SetSize (0.25 * Diag (Feld ()));
    
    // set the width/height relative to itself
    b -> SetWidth ( 2 * b -> Width () );
    b -> SetHeight ( 3 * b -> Height () );
    
    // set the width/height, retaining aspect ratio
    b -> SetWidthUniformly ( 150.0 );
    b -> SetHeightUniformly ( 75.0 );
    
    // load a new image from file
    b -> SetImage ("images/page3.png");
    
    // get the image data and make a new image with it
    ImageData *i = b -> Data ();
    Image *c = new Image ();
    c -> SetImage (i);
    c -> SlapOnFeld ();
    c -> IncTranslation (0.25 * Feld () -> Width () * Feld () -> Over () +
                         0.25 * Feld () -> Height () * Feld () -> Up ());
}