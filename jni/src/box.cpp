#include "box.h"

Box_manager box_manager;

void Box_manager::add(float x1, float y1, float x2, float y2, string name, int layer)
{
    Box *box = new Box;

    box->x = x1;
    box->y = y1;
    box->w = x2-x1;
    box->h = y2-y1;
    box->layer = layer;
    box->name = name;

    tab.push_back(box);
}

void Box_manager::manage(int layer)
{
    int i,j;

    for(i = 0; i < tab.size(); i++)
    if(tab[i]->layer == layer)
    tab[i]->manage(&in.finger[0]);

    /*for(i = 0; i < tab.size(); i++)
    LOGI("state %d", tab[i]->state);

    LOGI(" ");*/
}

int  Box_manager::get_state(string name)
{


    int i;

    for(i = 0; i < tab.size(); i++)
    {
        if(name == tab[i]->name)
        return tab[i]->state;
    }

    return TOUCH_NOTHING;
}

bool Box_manager::isinside(string name)
{
    int i;

    for(i = 0; i < tab.size(); i++)
    {
        if(name == tab[i]->name)
        return tab[i]->isinside;
    }
    return false;
}

bool Box_manager::isinside_w(string name)
{
    int i;

    for(i = 0; i < tab.size(); i++)
    {
        if(name == tab[i]->name)
        return tab[i]->isinside_w;
    }
    return false;
}

bool Box_manager::get_xy(string name, float &x, float &y)
{
    int i;

    for(i = 0; i < tab.size(); i++)
    {
        if(name == tab[i]->name)
        {
            x = tab[i]->fx;
            y = tab[i]->fy;
            return true;
        }
    }
    return false;
}
