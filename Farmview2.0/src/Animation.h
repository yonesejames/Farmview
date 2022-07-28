#ifndef ANIMATION_H
#define ANIMATION_H


struct Animation
/* 
    Animation creates movements using frame and speed as well as starting image 
    for index.
*/
{
    int index;
    int frames;
    int speed;

    // Default constructor:
    Animation(){}

    // Overloaded constructor:
    Animation(int i, int f, int s)
    /* Takes in index, frame, and seconds to show movement */
    {
        index = i;
        frames = f;
        speed = s;
    }
};


#endif

