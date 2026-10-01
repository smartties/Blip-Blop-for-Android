#!/usr/bin/env python3
"""Generates the on-screen touch controls (assets/ui/*.png) used on phones.

The 2014 port loaded these from data/*.png but never shipped them. Sizes and
anchor points match Game::drawTools() / the touch boxes in game.cpp (the game
draws in 640x480). Requires Pillow: python3 -m pip install Pillow
"""
import math
import os
from PIL import Image, ImageDraw

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "assets", "ui")
SS = 4  # supersampling for smooth edges


def canvas(w, h):
    return Image.new("RGBA", (w * SS, h * SS), (0, 0, 0, 0))


def save(img, name):
    w, h = img.size
    img.resize((w // SS, h // SS), Image.LANCZOS).save(os.path.join(OUT, name), optimize=True)


def disc(d, cx, cy, r, fill, outline, width):
    d.ellipse([(cx - r) * SS, (cy - r) * SS, (cx + r) * SS, (cy + r) * SS],
              fill=fill, outline=outline, width=width * SS)


def poly(d, pts, fill):
    d.polygon([(x * SS, y * SS) for x, y in pts], fill=fill)


def button(name, w, h, symbol, pressed):
    img = canvas(w, h)
    d = ImageDraw.Draw(img)
    cx, cy, r = w / 2, h / 2, min(w, h) / 2 - 2
    fill = (255, 255, 255, 150) if pressed else (0, 0, 0, 110)
    ink = (40, 40, 40, 255) if pressed else (255, 255, 255, 220)
    disc(d, cx, cy, r, fill, (255, 255, 255, 200), 2)
    symbol(d, cx, cy, r * 0.55, ink)
    save(img, name)


def sym_fire(d, cx, cy, s, ink):
    # crosshair
    disc(d, cx, cy, s * 0.75, None, ink, 3)
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        d.line([((cx + dx * s * 0.35) * SS, (cy + dy * s * 0.35) * SS),
                ((cx + dx * s * 1.1) * SS, (cy + dy * s * 1.1) * SS)], fill=ink, width=3 * SS)
    disc(d, cx, cy, s * 0.15, ink, None, 0)


def sym_jump(d, cx, cy, s, ink):
    # up arrow
    poly(d, [(cx, cy - s), (cx + s * 0.9, cy), (cx + s * 0.35, cy), (cx + s * 0.35, cy + s),
             (cx - s * 0.35, cy + s), (cx - s * 0.35, cy), (cx - s * 0.9, cy)], ink)


def sym_bomb(d, cx, cy, s, ink):
    # star burst (cow bomb)
    pts = []
    for i in range(16):
        a = math.pi * 2 * i / 16 - math.pi / 2
        rr = s * (1.05 if i % 2 == 0 else 0.5)
        pts.append((cx + math.cos(a) * rr, cy + math.sin(a) * rr))
    poly(d, pts, ink)


def main():
    os.makedirs(OUT, exist_ok=True)

    for pressed in (False, True):
        sfx = "_p" if pressed else ""
        button("shoot%s.png" % sfx, 60, 64, sym_fire, pressed)
        button("jump%s.png" % sfx, 62, 64, sym_jump, pressed)
        button("ulti%s.png" % sfx, 58, 64, sym_bomb, pressed)

    # pause (drawn at 595,5)
    img = canvas(40, 40)
    d = ImageDraw.Draw(img)
    disc(d, 20, 20, 18, (0, 0, 0, 110), (255, 255, 255, 200), 2)
    for x in (14, 23):
        d.rectangle([x * SS, 11 * SS, (x + 4) * SS, 29 * SS], fill=(255, 255, 255, 230))
    save(img, "pause.png")

    # virtual stick base: drawn at (pad_x - 85, pad_y - 100), so centred on (85, 100)
    img = canvas(170, 200)
    d = ImageDraw.Draw(img)
    disc(d, 85, 100, 82, (0, 0, 0, 70), (255, 255, 255, 170), 3)
    for a in range(4):
        ang = math.pi / 2 * a
        cx, cy = 85 + math.cos(ang) * 64, 100 - math.sin(ang) * 64
        s = 10
        tip = (cx + math.cos(ang) * s, cy - math.sin(ang) * s)
        l = (cx + math.cos(ang + 2.3) * s, cy - math.sin(ang + 2.3) * s)
        r = (cx + math.cos(ang - 2.3) * s, cy - math.sin(ang - 2.3) * s)
        poly(d, [tip, l, r], (255, 255, 255, 170))
    save(img, "pad.png")

    # stick knob: drawn at (x - 30, y - 35), so centred on (30, 35)
    img = canvas(60, 70)
    d = ImageDraw.Draw(img)
    disc(d, 30, 35, 27, (255, 255, 255, 140), (255, 255, 255, 230), 2)
    save(img, "stick.png")


if __name__ == "__main__":
    main()
