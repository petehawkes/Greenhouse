#include "Greenhouse.h"


/* (c)  oblong industries */


#include "Greenhouse.h"

/**
 
  Sliiiiiides... Iiiiiinn... Spaaaaaaaaace...
 
 **/


Trove <Vect> slide_vects;
Trove <Str> slide_names;

Vect active_vect;




class Slide  :  public Thing
{ public:
  
  Str src_path;

  Slide (const Str &src_path)  :  Thing ()
    {
    
    }


};


class Mover  :  public Sketch
{ public:
  
  float width;
  
  Vect over;
  Vect up;
  Vect norm;
  Vect start;
  float wid, hei;
  
  //int slide_count = 8;
  int active_slide = 0;
  
  Mover ()  :  Sketch ()
  { width = 8.0;
    
    // store feld dimenions and orientation
    SpaceFeld *f = Feld ();
    over = f -> Over ();
    up = f -> Up ();
    norm = f -> Norm ();
    wid = f -> Width ();
    hei = f -> Height ();
    
    SlapOnFeld();
    
    //    // draw
    //    SetStroked (false);
    //    SetFillColor (Color (1, 1, 1));
    //    DrawEllipse (Vect (0, 0, 0), width, width);
    
    start = Translation ();
  }
  
  void Travail ()
  {
  }
  
  void NextSlide ()
  { active_slide++;
    if (active_slide >= slide_names.Count ()) active_slide = 0;
    TranslationAnimateQuadratic (0.5);
    Vect move = slide_vects[active_slide];
    move.Scale (Vect (-1, -1, -1));
    SetTranslation(start + move);
  }
  
  void PrevSlide ()
  { active_slide--;
    if (active_slide < 0) active_slide = slide_names.Count () - 1;
    TranslationAnimateQuadratic (0.5);
    Vect move = slide_vects[active_slide];
    move.Scale (Vect (-1, -1, -1));
    SetTranslation(start + move);
  }
  
  void PointingHarden (PointingEvent *e)
  { //pointer_loc = Intersection (e);
    NextSlide ();
  }
  
  //  Keyboard interactions
  void Blurt (BlurtEvent *e)
  { if (Utters (e, "x"))
    NextSlide ();
  else if (Utters (e, "z"))
    PrevSlide ();
  }
  
  /*
   void FistAppear (PointingEvent *e)
   { // get control of this object if there's no one already controlling it
   if (IsLeftHandish (e))
   NextSlide ();
   else
   PrevSlide ();
   }
   */
  
  
  Vect MapToFeld (Vect v)
  { return Vect (v . ProjectOnto (over) + v . ProjectOnto (up) + v . ProjectOnto (norm)); }
  
  
};




void Setup ()
{ for (int i = 0  ;  i <= 7  ;  ++i)
  { slide_vects.Append (Vect (0.0, 0.0, -i * 1000.0));
    //slide_vects.Append (Vect (cos ( 2 * PI * i / 7 + PI / 2) * 1000, 0.0, sin ( 2 * PI * i / 7 + PI / 2) * 2000));
  }
  
  //Str n = foo.Slice (-3);
  
  //INFORM ("checking:" + n);
  
  
  slide_names.Append ("slides/oblong.001.png");
  slide_names.Append ("slides/oblong.002.png");
  slide_names.Append ("slides/oblong.003.png");
  slide_names.Append ("slides/oblong.004.png");
  slide_names.Append ("slides/oblong.005.png");
  slide_names.Append ("slides/oblong.006.png");
  slide_names.Append ("slides/oblong.007.png");
  slide_names.Append ("images/move-scale.mp4");
  
  slide_names.Append ("slides/oblong.001.png");
  slide_names.Append ("slides/oblong.002.png");
  slide_names.Append ("slides/oblong.003.png");
  slide_names.Append ("slides/oblong.004.png");
  slide_names.Append ("slides/oblong.005.png");
  slide_names.Append ("slides/oblong.006.png");
  slide_names.Append ("slides/oblong.007.png");
  slide_names.Append ("slides/move-scale.mp4");
  
  
  //
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  //  slide_names.Append ("images/move-scale.mp4");
  
  
  slide_vects.Append (Vect (0.0, 0.0, 0));
  slide_vects.Append (Vect (400.0, 0.0, -1000));
  slide_vects.Append (Vect (400.0, -400.0, 0));
  slide_vects.Append (Vect (-400.0, 400.0, 1000));
  slide_vects.Append (Vect (-400.0, 0, -1000));
  slide_vects.Append (Vect (-400.0, -400.0, 0));
  slide_vects.Append (Vect (0, 400.0, 1000));
  slide_vects.Append (Vect (0, -400.0, 0));
  
  Mover *m = new Mover ();
  
  for (int i = 0  ;  i <= slide_names.Count()  ;  ++i)
    { Str str = slide_names[i];
      Str strCheck = str.Slice (-3);
      if (strCheck == "png" )
        { Image *img = new Image (str);
          m -> AppendKid (img);
          img -> IncTranslation (slide_vects[i]);
          img -> SetWidthUniformly (m -> wid * .9);
          //all_slides.Append (img);
        } else if (strCheck == "mp4" ){
          Video *vid = new Video (str);
          m -> AppendKid (vid);
          vid -> IncTranslation (slide_vects[i]);
          vid -> SetWidthUniformly (m -> wid * .9);
          vid -> EnableLooping ();
          vid -> Play ();
          vid -> SetCornerRadius (0);
          //all_slides.Append (vid);
        }
    }
  
  // color the background
  SetFeldsColor (Color (.2706, .2706, .3098));
  // generate a new random seed for unique results each time
  SeedRandomizer ();
  // add the Mover
  
  
  
  
}