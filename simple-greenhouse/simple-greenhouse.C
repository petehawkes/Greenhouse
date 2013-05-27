/* (c)  oblong industries */


#include "Greenhouse.h"

/**
 When using new resource files please be sure to do the following in order to
 ensure that your application can find those resources:
 
 - Place all resource files in:
 
 /opt/oblong/greenhouse/share
 
 - OR if you'd like to keep your resource files separated from the installed
 resources:
 
 Create a folder for your personal resource files and add the following
 line to your ~/.bash_profile (Mac) or ~/.bashrc (Linux) file:
 
 export OB_SHARE_PATH=[/path/to/new/share]:$OB_SHARE_PATH
 **/

class Rect : public Thing
{
public:
    Rect () : Thing () {}
    void DrawSelf ()
    {
        DrawQuad(Vect (), 50 * Over (), 50 * Up ());
    }
};

class GrabbableImage : public Image
{
public:
    GrabbableImage () : Image ()
    {}
    
    //    void PointingHarden (PointingEvent *e)
    //    { if (IsHeedless())  // if no one else owns me
    //        Heed (e);
    //    }
    
    void PointingInsideHarden (PointingEvent *e)
    { //if (IsHeedless())  // if no one else owns me
        Heed (e);
    }
    
    void PointingMove (PointingEvent *e)
    {
        if (IsHeeding(e)) {
            IncTranslation( IntersectionDiff(e, Feld () -> Loc ()));
        }
    }
    
    void PointingSoften (PointingEvent *e)
    {  StopHeeding(e);  }
    
    /* start kinect stuff */
    
    
    
    void FistMove (PointingEvent *e)
    {
        if (IsHeedless ())
            Heed (e);
        
        if (IsHeeding (e)) {
            IncTranslation( FistMotion (e, Feld () -> Loc ()));
        }
    }
    
    void FistVanish (PointingEvent *e)
    { StopHeeding(); }
    
};




void Setup ()
{ /// Start Hacking!
    
    /* standard image
     Image *img = new Image();
     img -> SetAdjColor(Color(0.4));
     img -> SlapOnFeld();
     */
    
    GrabbableImage *img1 = new GrabbableImage();
    img1 -> SetAdjColor(Color(0.4));
    img1 -> SlapOnFeld();
    
    GrabbableImage *img2 = new GrabbableImage();
    img2 -> SetAdjColor(Color(0.8));
    img2 -> SetScale(0.5f);
    img2 -> SlapOnFeld();
    
    /*
     Rect *rect = new Rect ();
     rect -> SetAdjColor(Color(0.0, 0.0, 1.0));
     rect -> SlapOnFeld();
     */
    
}
