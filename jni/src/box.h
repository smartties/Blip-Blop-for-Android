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

        bool was_inside = isinside;
        isinside = false;
        isinside_w = false;

        bool owned = false;

        for(i = 0; i < MAX_FINGERS; i++)
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
                // TOUCH_UP: a tap that went down and up within one frame.
                // Only a fresh finger counts; one that slid here from
                // elsewhere and lifted is not a press of this box.
                if( (fin[i].state == TOUCH_PRESSING || (fin[i].state == TOUCH_UP && fin[i].fresh)) && collide(fin[i].x, fin[i].y) )
                {
                    isinside = true;
                    fx = (float)(fin[i].x-x)/w;
                    fy = (float)(fin[i].y-y)/h;

                    state = fin[i].state;
                    fin[i].ptr = this;
                }
            }

            if(fin[i].ptr != NULL && (fin[i].ptr == this || compare_ptr(fin[i].ptr)))
            owned = true;
        }

        // Held, but no finger belongs to this box any more: its finger was
        // lifted and reused for a new press within one frame (see
        // Touch_manager::set), so the release was never seen here. Like a
        // normal release, it only counts as a tap if the finger was inside.
        if(!owned && (state == TOUCH_DOWN || state == TOUCH_PRESSING))
        state = was_inside ? TOUCH_UP : TOUCH_NOTHING;

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
    bool contains(string name, float x, float y);

    private:
    vector<Box*> tab;
};

extern Box_manager box_manager;

#endif // BOX_H_INCLUDED
