#ifndef RC_HAUNTER_HPP
#define RC_HAUNTER_HPP
#include "main.hpp"

namespace haunter{

class ForceField
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
    HaunterFace haunterFace;
    Haunter_Hand haunterHand;

public:
    void draw(){
        field.draw();
        haunterFace.drawLeftEyes();
		haunterFace.drawRightEyes();
        haunterFace.drawFace();
        haunterFace.drawMouth();
        haunterHand.draw();
    }

    void tickTime()
    {

    }

    void init()
    {

    }

};

};

#endif
