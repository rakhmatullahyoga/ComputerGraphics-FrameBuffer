#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main(){
        // variables for handling framebuffer
        FrameBuffer frame;
        DrawingObject draw;
        RGBcolor WHITE; WHITE.setRGB(255, 255, 255);
        RGBcolor BLACK; BLACK.setRGB(0, 0, 0);
        RGBcolor RED; RED.setRGB(255, 0, 0);
        RGBcolor GREEN; GREEN.setRGB(0, 255, 0);
        RGBcolor BLUE; BLUE.setRGB(0, 0, 255);

        //variables for handling mouse driver
        FILE *fmouse;
        char b[3];
        fmouse = fopen("/dev/input/mice","r");

        // variable pointer data
        int xd=0,yd=0; //x/y movement delta
        int xo=0,yo=0; //x/y overflow (out of range -255 to +255)
        int lb=0,mb=0,rb=0,hs=0,vs=0; //left/middle/right mousebutton

        // variables for cache pointer data a moment before
        int xd0=0,yd0=0;
        int xo0=0,yo0=0;
        int lb0=0,mb0=0,rb0=0,hs0=0,vs0=0; 

        //variables for handle pointer
        int resX = 1366, resY = 768; // monitor resolution
        int x=resX/2, y=resY/2; // center of monitor resolution
        int margin = 10; // margin of bound
        Point ref1, ref2;
        Point pointer(x, y);

        // loop variable
        int run=0; 

        printf("Initialization finish\n");
        

        while(!run){
                //read from mouse driver
                fread(b,sizeof(char),3,fmouse);
                lb=(b[0]&1)>0;  //left button
                rb=(b[0]&2)>0;  //right button
                mb=(b[0]&4)>0;  //middle button
                hs=(b[0]&16)>0; //horizonal slide
                vs=(b[0]&32)>0; //vertical slide
                xo=(b[0]&64)>0; //???
                yo=(b[0]&128)>0;//???
                xd=b[1];        //delta x from a moment before
                yd=b[2];        //delya y from a moment before

                x += xd; 
                //if pointer.x out of bound
                if(x>resX-margin) x = resX-margin;
                if(x<margin) x = margin;
                
                y -= yd;
                //if pointer.y out of bound
                if(y>resY-margin) y = resY-margin;
                if(y<margin) y = margin;
                
                system("clear");

                //DEBUG
                printf("hs=%d,vs=%d,lb=%d rb=%d mb=%d xo=%d yo=%d xd=%d yd=%d\n",hs,vs,lb,rb,mb,xo,yo,xd,yd);
                printf("%d %d\n", x, y);

                pointer = Point(x, y);
                RGBcolor color = WHITE;
                if(lb==1) color = RED;
                if(rb==1) color = GREEN;
                //if(mb==1) run = 1;
                draw.plotCircle(pointer, 3, color, frame);
                color.setRGB(255, 255, 255);

                if((lb0==0) && (lb==1))
                {
                        ref1 = pointer;
                }
                else if((lb0==1) && (lb==1))
                {
                        ref2 = pointer;
                        Point top_left = Point(min(ref1.GetAbsis(), ref2.GetAbsis()), 
                                                min(ref1.GetOrdinat(), ref2.GetOrdinat()));
                        int height = abs(ref1.GetOrdinat() - ref2.GetOrdinat());
                        int width = abs(ref1.GetAbsis() - ref2.GetAbsis());
                        draw.drawRectangle(top_left, height, width, WHITE, frame);
                }

                hs0=hs; vs0=vs; lb0=lb; rb0=rb; mb0 = mb; xo0=xo; yo0=yo; xd0=xd; yd0=yd;
        }
        fclose(fmouse);
	
	return 0;
}
