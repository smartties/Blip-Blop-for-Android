#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "input.h"
#include <vector>

using namespace std;

class Box
{
    public :
    Box()
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
        fx = 0;
        fy = 0;
        layer = 0;
        isinside = false;
        isinside_w = false;
        state = TOUCH_NOTHING;
    }

    bool collide(float tx, float ty)
    {
       return (x < tx && x+w > tx && y < ty && y+h > ty);
    }

    void link_to(Box *bbb)
    {
        linked_box.push_back(bbb);
    }
    bool compare_ptr(void *ptr)
    {
        int i;

        for(i = 0; i < linked_box.size(); i++)
        {
            if(linked_box[i] == ptr)
            return true;
        }

        return false;
    }
    void manage(Finger *fin)
    {
        int i;

        if(state == TOUCH_UP)
        state = TOUCH_NOTHING;
        if(state == TOUCH_PRESSING)
        state = TOUCH_DOWN;

        isinside = false;
        isinside_w = false;

        for(i = 0; i < 2; i++)
        {
            if(collide(fin[i].x, fin[i].y))
            isinside_w = true;

            if(fin[i].ptr == this || compare_ptr(fin[i].ptr) )
            {
                if(collide(fin[i].x, fin[i].y))
                {
                    isinside = true;
                    fx = (float)(fin[i].x-x)/w;
                    fy = (float)(fin[i].y-y)/h;
                }

                if( (fin[i].state == TOUCH_NOTHING || fin[i].state == TOUCH_UP) && (state == TOUCH_DOWN || state == TOUCH_PRESSING) )
                {
                    if(collide(fin[i].x, fin[i].y))
                    state = TOUCH_UP;
                    else
                    state = TOUCH_NOTHING;
                }
            }
            if(fin[i].ptr == NULL)
            {
                if( (fin[i].state == TOUCH_PRESSING || fin[i].state == TOUCH_UP) && collide(fin[i].x, fin[i].y) )
                {
                    isinside = true;
                    fx = (float)(fin[i].x-x)/w;
                    fy = (float)(fin[i].y-y)/h;

                    state = fin[i].state;
                    fin[i].ptr = this;
                }
            }
        }

    }

    bool isinside_w;
    float x;
    float y;
    float w;
    float h;
    float fx;
    float fy;
    int layer;
    int state;
    bool isinside;
    string name;
    vector<Box*> linked_box;
};

class Box_manager
{
    public:
    void add(float x1, float y1, float x2, float y2, string name, int layer);
    void manage(int layer);
    int get_state(string name);
    bool isinside(string name);
    bool isinside_w(string name);
    bool get_xy(string name, float &x, float &y);

    private:
    vector<Box*> tab;
};

extern Box_manager box_manager;

#endif // BOX_H_INCLUDED
