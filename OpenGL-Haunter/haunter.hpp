#ifndef RC_HAUNTER_HPP
#define RC_HAUNTER_HPP
#include "main.hpp"

namespace haunter{

class ForceField
{
        public:
        void draw();
};

class GrassField
{
        public:
        void draw();
};

class Moon
{
        public:
        void draw();
};

class HaunterFace
{
    public:
        void drawLeftEyes();
		void drawRightEyes();
		void drawFace();
		void drawMouth();

};

class Haunter_Hand
{
    public:
        void draw();
};

class HauntedHouse
{
public :
    ForceField field;
    GrassField rumput;
    HaunterFace haunterFace;
    Haunter_Hand haunterHand;
    Moon moon;

public:
    void draw(){
        field.draw();
        rumput.draw();
        moon.draw();
        haunterFace.drawLeftEyes();
		haunterFace.drawRightEyes();
        haunterFace.drawFace();
        haunterFace.drawMouth();
        haunterHand.draw();
    }

};

};

#endif
