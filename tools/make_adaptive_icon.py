#!/usr/bin/env python3
"""Builds the adaptive launcher icon (Android 8+) from the original 2014 icon.

The artwork inside the old square frame becomes the full-bleed background
layer (108dp), so launchers can mask it to a circle / squircle.
Requires Pillow: python3 -m pip install Pillow
"""
import os
from PIL import Image

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
SRC = os.path.join(ROOT, "res", "drawable-xxhdpi", "ic_launcher.png")
SIZES = {"mdpi": 108, "hdpi": 162, "xhdpi": 216, "xxhdpi": 324, "xxxhdpi": 432}

src = Image.open(SRC).convert("RGBA")
w, h = src.size
m = int(w * 0.09)                      # drop the grey frame and rounded corners
art = src.crop((m, m, w - m, h - m))
bg = Image.new("RGBA", art.size, (34, 34, 34, 255))
art = Image.alpha_composite(bg, art)

for dpi, px in SIZES.items():
    out = os.path.join(ROOT, "res", "drawable-" + dpi)
    os.makedirs(out, exist_ok=True)
    art.resize((px, px), Image.LANCZOS).convert("RGB").save(
        os.path.join(out, "ic_launcher_background.png"), optimize=True)
