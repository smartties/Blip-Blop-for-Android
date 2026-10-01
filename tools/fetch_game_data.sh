#!/bin/sh
# Copies the original Blip & Blop game data (graphics, levels, sounds, music)
# from the PC release into assets/data/, where the Android build expects it.
# Source: https://github.com/benkaraban/blip-blop (vc-projects/Blip_n_Blop_3/data)
set -e
ROOT=$(cd "$(dirname "$0")/.." && pwd)
DEST="$ROOT/assets/data"
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

git clone --depth 1 --filter=blob:none --sparse https://github.com/benkaraban/blip-blop.git "$TMP/bb"
git -C "$TMP/bb" sparse-checkout set vc-projects/Blip_n_Blop_3/data

mkdir -p "$DEST"
cp -R "$TMP/bb/vc-projects/Blip_n_Blop_3/data/." "$DEST/"
echo "Game data copied to $DEST ($(ls "$DEST" | wc -l | tr -d ' ') files)"
