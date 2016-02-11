#include "Button.h"
#include "global_main.h"
#include "global_graphic.h"

Button::Button(string _text, void(*_fn)(), Area _area, Color _color)
    : text(_text), color(_color), fn(_fn), area(_area), cs(_area, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK)
{
    //
}

Button::Button(string _text, void(*_fn)(), Color _color)
    : text(_text), color(_color), fn(_fn), cs(Area(), ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK)
{
    //
}

void Button::update()
{
    cs.update(area);
    if (cs.click()) fn();
}

void Button::draw()
{
    Color c = color;
    if (cs.getInvaded()) c += 75;
    else if (cs.getIsPressed()) c -= 75;

    float gradient_diff = 11.0/7.0;
    drawGradient(area, c + Color(static_cast<float>(c.getR())/(gradient_diff), static_cast<float>(c.getG())/(gradient_diff), static_cast<float>(c.getB())/(gradient_diff)),
                       c - Color(static_cast<float>(c.getR())/(gradient_diff), static_cast<float>(c.getG())/(gradient_diff), static_cast<float>(c.getB())/(gradient_diff)));

    al_draw_text(font(area.h()/3), [](bool b)->Color{return b ? Color::white() : Color::black();}(color.ifDark()),
                 area.cx(), area.cy() - area.h()/6, ALLEGRO_ALIGN_CENTER, text.c_str());
}

void Button::reInit(const Area& other)
{
    area.reInit(other);
    cs.update(area);
}

void Button::reInit(Area::Style s, float a1, float a2, float a3, float a4) throw(Error)
{
    area.reInit(s, a1, a2, a3, a4);
    cs.update(area);
}
