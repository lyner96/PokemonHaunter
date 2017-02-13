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
            void drawMouth(GLenum draw_mode = GL_FILL, GLint ures = 100, GLint vres = 100);
    };

    class Haunter_Hand
    {
        public:
            void draw();
            Haunter_Hand();
            ~Haunter_Hand();

        private:
            //Setup Quadric Object
            GLUquadricObj *pObj;
    };

    class bezierSurface
    {
        public:
            bezierSurface() { }
            ~bezierSurface() { }
            void setup(const GLfloat* controlPoints, GLint uOrder, GLint vOrder, const bool autonormal = false);
            void drawControlPoints();
            void init(int num);

        private:
            GLint uorder, vorder;
            const GLfloat* controlpoints;
    };

    class HauntedHouse
    {
        public :
            ForceField field;
            GrassField rumput;
            HaunterFace hfo;
            Haunter_Hand haunterHand;
            Moon moon;
            bezierSurface bso;

            void draw()
            {
                field.draw();
                rumput.draw();
                moon.draw();
                hfo.drawLeftEyes();
                hfo.drawRightEyes();
                hfo.drawFace();
                haunterHand.draw();

                for (int i = 0; i < 10; i++)
                {
                    bso.init(i + 1);
                }
            }
    };
};
#endif
