#include "msxgl.h"
#include "v9990.h"

// Fonts data
#include "font/font_mgl_sample6.h"

// Tileset data
#include "content/tileset.h"

// Background data
#include "content/bg.h"

// Sprite data
#include "content/sprite.h"

//-----------------------------------------------------------------------------
// Initialize V9990 palette
void InitializePalette()
{
	V9_SetPalette(0 + 1, 15, g_DataTilset_palette);
	V9_SetPalette(16 + 1, 15, g_DataBG_palette);
	V9_SetPalette(32 + 1, 15, g_DataSprite_palette);
}
