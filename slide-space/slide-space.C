#include "Greenhouse.h"


/* (c)  oblong industries */


#include "Greenhouse.h"

/**
 
  Sliiiiiides... Iiiiiinn... Spaaaaaaaaace...
 
 **/




class Slide  :  public Thing
{ public:
  
  Str src;
  bool is_vid;
  Image *img;
  Video *vid;

  Slide (const Str src_path, Vect offset, float wid)  :  Thing ()
    { src = src_path;
      Str srcCheck = src.Slice (-3);
      if (srcCheck == "png" )
        { img = new Image (src);
          img -> SetWidthUniformly (wid * .9);
          AppendKid (img);
          is_vid = false;
        } else if (srcCheck == "mp4" ){
          vid = new Video (src);
          vid -> SetWidthUniformly (wid * .9);
          vid -> EnableLooping ();
          vid -> SetCornerRadius (0);
          AppendKid (vid);
          //vid -> Play ();
          is_vid = true;
        }
      IncTranslation (offset);
    }

  void slide_on ()
    { if (is_vid) vid -> Play (); }
  
  void slide_off ()
    { if (is_vid) vid -> Stop (); }

};


class Mover  :  public Thing
{ public:
  
  float width;
  
  Vect over;
  Vect up;
  Vect norm;
  Vect start;
  float wid, hei;
  
  Trove <Vect> slide_vects;
  Trove <Str> slide_names;

  int active_slide = 0;
  Vect active_vect;
  
  Mover ()  :  Thing ()
  { width = 8.0;
    
    // store feld dimenions and orientation
    SpaceFeld *f = Feld ();
    over = f -> Over ();
    up = f -> Up ();
    norm = f -> Norm ();
    wid = f -> Width ();
    hei = f -> Height ();
    
    SlapOnFeld();
    
    for (int i = 0  ;  i < 8  ;  ++i)
      { slide_vects.Append (Vect (0.0, 0.0, -i * 1000.0));
        //slide_vects.Append (Vect (cos ( 2 * PI * i / 7 + PI / 2) * 1000, 0.0, sin ( 2 * PI * i / 7 + PI / 2) * 2000));
      }
    
    slide_names.Append ("slides/oblong.001.png");
    slide_names.Append ("slides/oblong.002.png");
    slide_names.Append ("slides/oblong.003.png");
    slide_names.Append ("slides/oblong.004.png");
    slide_names.Append ("slides/oblong.005.png");
    slide_names.Append ("slides/oblong.006.png");
    slide_names.Append ("slides/oblong.007.png");
    slide_names.Append ("slides/move-scale.mp4");
    
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");
    slide_names.Append ("slides/move-scale.mp4");


    
    slide_vects.Append (Vect (400.0, 400.0, 0));
    slide_vects.Append (Vect (400.0, 0.0, -1000));
    slide_vects.Append (Vect (400.0, -400.0, 0));
    slide_vects.Append (Vect (-400.0, 400.0, 1000));
    slide_vects.Append (Vect (-400.0, 0, -1000));
    slide_vects.Append (Vect (-400.0, -400.0, 0));
    slide_vects.Append (Vect (0, 400.0, 1000));
    slide_vects.Append (Vect (0, -400.0, 0));
    
    start = Translation ();
  }
  
  void Travail ()
  {
  }
  
  void NextSlide ()
  { Slide *s  = NthKid <Slide> ( active_slide );
    s -> slide_off ();
    //
    active_slide++;
    if (active_slide >= slide_names.Count ()) active_slide = 0;
    TranslationAnimateQuadratic (0.5);
    Vect move = slide_vects[active_slide];
    move.Scale (Vect (-1, -1, -1));
    SetTranslation(start + move);
    //
    s = NthKid <Slide> ( active_slide );
    s -> slide_on ();
  }
  
  void PrevSlide ()
  { Slide *s  = NthKid <Slide> ( active_slide );
    s -> slide_off ();
    //
    active_slide--;
    if (active_slide < 0) active_slide = slide_names.Count () - 1;
    TranslationAnimateQuadratic (0.5);
    Vect move = slide_vects[active_slide];
    move.Scale (Vect (-1, -1, -1));
    SetTranslation(start + move);
    //
    s = NthKid <Slide> ( active_slide );
    s -> slide_on ();
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
  
  Vect MapToFeld (Vect v)
  { return Vect (v . ProjectOnto (over) + v . ProjectOnto (up) + v . ProjectOnto (norm)); }
  
};




void Setup ()
{ Mover *m = new Mover ();
  
  for (int i = 0  ;  i < m -> slide_names.Count()  ;  ++i)
    { Slide *s = new Slide (m -> slide_names[i], m -> slide_vects[i], m -> wid);
      m -> AppendKid (s);
    }
  m -> NthKid <Slide> (0) -> slide_on ();
  
  // color the background
  SetFeldsColor (Color (.2706, .2706, .3098));
  
  
}