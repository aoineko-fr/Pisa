// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄      
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
//  Program template
//─────────────────────────────────────────────────────────────────────────────

// Segment	Bank	Content
// 	0		 1		 Program (higher 16K part)
// 	1		 2		 Tileset image
// 	2		 0		 Program (lower 16K part)
// 	3		 2		 BG image (lower part)
// 	4		 2		 BG image (higher part)
// 	5		 2		 --not used yet--)

//=============================================================================
// INCLUDES
//=============================================================================
#include "msxgl.h"
#include "v9990.h"
#include "game_pawn.h"

//=============================================================================
// DEFINES
//=============================================================================

// Library's logo
#define MSX_GL "\x01\x02\x03\x04\x05\x06"

#define FORCE		24
#define GRAVITY		1

// External data
extern const unsigned char g_DataTilset[4196];
extern const unsigned char g_DataTilset_palette[];
extern const unsigned char g_DataBG_palette[];
extern const char g_Font_MGL_Sample6[];
extern const unsigned char g_DataSprite[4196];
extern const unsigned char g_DataSprite_palette[];

// Function prototype
void InitializePalette();

//=============================================================================
// READ-ONLY DATA
//=============================================================================

// Animation characters
const u8 g_ChrAnim[] = { '-', '/', '|', '\\' };

#define OOO 20
// Sample level tiles map
const u8 g_TileMap[32 * 27] =
{
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,  10,  11,  12,  13, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 106, 107, 108, 109, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,  10,  11,  12,  13, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 106, 107, 108, 109, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO,  10,  11,  12,  13, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, 106, 107, 108, 109, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	  10,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  11,  12,  13,
	  42,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  45,
	  74,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  75,  76,  77,
};


// Pawn sprite layers
const Game_Sprite g_SpriteLayers[] =
{//   X  Y  Pattern  Color  Option
	{ 0, 0, 0,       2,     0 }, // Black sprite...
};

// Idle animation frames
const Game_Frame g_FramesIdleR[] =
{ //  Pattern Frames Function
	{ 0, 1, NULL },
};

// Idle animation frames
const Game_Frame g_FramesIdleL[] =
{ //  Pattern Frames Function
	{ 15, 1, NULL },
};

// Move animation frames
const Game_Frame g_FramesMoveR[] =
{
	{ 2,	4,	NULL },
	{ 3,	4,	NULL },
	{ 4,	4,	NULL },
	{ 5,	4,	NULL },
	{ 6,	4,	NULL },
	{ 7,	4,	NULL },
};

// Move animation frames
const Game_Frame g_FramesMoveL[] =
{
	{ 13,	4,	NULL },
	{ 12,	4,	NULL },
	{ 11,	4,	NULL },
	{ 10,	4,	NULL },
	{ 9,	4,	NULL },
	{ 8,	4,	NULL },
};

// Actions id
enum ANIM_ACTION_ID
{
	ACTION_IDLE_R = 0,
	ACTION_IDLE_L,
	ACTION_MOVE_R,
	ACTION_MOVE_L,
	ACTION_MAX,
};

// List of all player actions
const Game_Action g_AnimActions[ACTION_MAX] =
{ //  Frames        Number                  Loop? Interrupt?
	{ g_FramesIdleR, numberof(g_FramesIdleR), TRUE, TRUE },
	{ g_FramesIdleL, numberof(g_FramesIdleL), TRUE, TRUE },
	{ g_FramesMoveR, numberof(g_FramesMoveR), TRUE, TRUE },
	{ g_FramesMoveL, numberof(g_FramesMoveL), TRUE, TRUE },
};

//=============================================================================
// VARIABLES
//=============================================================================

Game_Pawn g_PlayerPawn;				// Player's pawn data structure
// struct V9_Sprite g_PlayerSprite;

u16 g_FrameCounter;

bool g_VSynch = FALSE;

bool g_bTurnRight = TRUE;			// Is player looking forward right direction?
bool g_bMoving = FALSE;				// Is player moving?
bool g_bInAir = FALSE;				// Is player jumping?
i8   g_VelocityY = 0;				// Current player velocity
i8   g_DX = 0;						// Current X movement
i8   g_DY = 0;						// Current Y movement

u8   g_PrevRow8 = 0xFF;				// Previous keyboard 8th row value

//=============================================================================
// FUNCTONS
//=============================================================================

//-----------------------------------------------------------------------------
// V9990 V-blank interrupt
void V9_InterruptVBlank()
{
	g_VSynch = TRUE;
}

//-----------------------------------------------------------------------------
// V9990 H-blank interrupt
void V9_InterruptHBlank()
{}

//-----------------------------------------------------------------------------
// V9990 Command end interrupt
void V9_InterruptCommand()
{}

//-----------------------------------------------------------------------------
// Initialize V9990
void InitializeV9990()
{
	// Initialize screen mode
	V9_SetScreenMode(V9_MODE_P1);
	V9_SetInterrupt(V9_INT_VBLANK);
	V9_SetBackgroundColor(1);
	V9_SetSpriteEnable(TRUE);
	V9_SetDisplayEnable(TRUE);
	V9_SelectPaletteP1(0, 1);

	// Sprite attribute table
	struct V9_Sprite attr;
	for(u16 i = 0; i < 125; ++i)
	{
		attr.D = 1;
		V9_SetSpriteP1(i, &attr);
	}

	//.........................................................................
	// SEGMENT 1 DATA

	SET_BANK_SEGMENT(2, 1); // Bank 2 = Segment 1
	InitializePalette();
	V9_FillVRAM(V9_P1_PGT_A, 0x00, 128*212); // Clean layer A pattern
	V9_WriteVRAM(V9_P1_PGT_A, g_DataTilset, sizeof(g_DataTilset));

	V9_FillVRAM(V9_P1_PGT_B, 0x00, 128*212); // Clean layer A pattern

	// Sprite pattern generator table
	V9_SetSpritePatternAddr(V9_P1_SGT_08000);
	V9_WriteVRAM(0x08000, g_DataSprite, sizeof(g_DataSprite));

	//.........................................................................
	// SEGMENT 3 DATA

	SET_BANK_SEGMENT(2, 3); // Bank 2 = Segment 3
	V9_WriteVRAM(V9_P1_PGT_B, (const u8*)0x8000, 16 * 1024); // Copy 16 K

	//.........................................................................
	// SEGMENT 4 DATA

	SET_BANK_SEGMENT(2, 4); // Bank 2 = Segment 4
	V9_WriteVRAM(V9_P1_PGT_B + 16 * 1024, (const u8*)0x8000, 128 * 212 - 16 * 1024); // Copy the remaining

	for (u16 i = 0; i < 32 * 27; i++)
	{
		u8 x = i % 32;
		u8 y = i / 32;

		V9_Poke16(V9_CellAddrP1A(x, y), g_TileMap[i]);
		V9_Poke16(V9_CellAddrP1B(x, y), i);
		V9_Poke16(V9_CellAddrP1B(x + 32, y), i);
	}
}

//-----------------------------------------------------------------------------
// 
void WaitV9990Synch()
{
	while(!g_VSynch) {}

	g_VSynch = FALSE;
	g_FrameCounter++;
}

const u8 g_MoveAnimationR[] = { 2, 3, 4, 5, 6, 7, };


//-----------------------------------------------------------------------------
// Physics callback
void PhysicsEvent(u8 event, u8 tile)
{
	tile;
	switch(event)
	{
	case PAWN_PHYSICS_BORDER_DOWN:
	case PAWN_PHYSICS_BORDER_RIGHT:
		break;
	
	case PAWN_PHYSICS_COL_DOWN: // Handle downward collisions 
		g_bInAir = FALSE;
		break;
	
	case PAWN_PHYSICS_COL_UP: // Handle upward collisions
		g_VelocityY = 0;
		break;
	
	case PAWN_PHYSICS_FALL: // Handle falling
		if(!g_bInAir)
		{
			g_bInAir = TRUE;
			g_VelocityY = 0;
		}
		break;
	};
}

//-----------------------------------------------------------------------------
// Collision callback
bool PhysicsCollision(u8 tile)
{
	return (tile != OOO);
}

//-----------------------------------------------------------------------------
// 
void UpdateV9990()
{
	WaitV9990Synch();

	// Update movement
	g_DX = 0;
	g_DY = 0;
	u8 row8 = Keyboard_Read(8);
	if(IS_KEY_PRESSED(row8, KEY_RIGHT))
	{
		g_DX++;
		g_bMoving = TRUE;
		g_bTurnRight = TRUE;
	}
	else if(IS_KEY_PRESSED(row8, KEY_LEFT))
	{
		g_DX--;
		g_bMoving = TRUE;
		g_bTurnRight = FALSE;
	}
	else
		g_bMoving = FALSE;
	
	if(g_bInAir)
	{
		g_DY -= g_VelocityY / 4;
		
		g_VelocityY -= GRAVITY;
		if(g_VelocityY < -FORCE)
			g_VelocityY = -FORCE;

	}
	else if(IS_KEY_PRESSED(row8, KEY_SPACE) || IS_KEY_PRESSED(row8, KEY_UP))
	{
		g_bInAir = TRUE;
		g_VelocityY = FORCE;
	}

	g_PrevRow8 = row8;

	u8 action = ACTION_IDLE_R;
	if (g_bMoving)
	{
		if (g_bTurnRight)
			action = ACTION_MOVE_R;
		else
			action = ACTION_MOVE_L;
	}
	else
	{
		if (g_bTurnRight)
			action = ACTION_IDLE_R;
		else
			action = ACTION_IDLE_L;
	}

	GamePawn_SetAction(&g_PlayerPawn, action);
	GamePawn_SetMovement(&g_PlayerPawn, g_DX, g_DY);

	GamePawn_Update(&g_PlayerPawn);
	GamePawn_Draw(&g_PlayerPawn);

	V9_SetScrollingBX(g_FrameCounter);
}

//-----------------------------------------------------------------------------
// Program entry point
void main()
{
	VDP_SetMode(VDP_MODE_SCREEN0);
	VDP_EnableVBlank(FALSE);
	VDP_ClearVRAM();

	SET_BANK_SEGMENT(2, 1); // Bank 2 = Segment 1
	Print_SetTextFont(g_Font_MGL_Sample6, 1);
	Print_SetColor(COLOR_WHITE, COLOR_BLACK);
	Print_SetPosition(0, 0);
	Print_DrawText("PISA Great Game");

	InitializeV9990();

	// Init player pawn
	GamePawn_Initialize(&g_PlayerPawn, g_SpriteLayers, numberof(g_SpriteLayers), 0, g_AnimActions);
	GamePawn_SetTileMap(g_TileMap);
	GamePawn_SetPosition(&g_PlayerPawn, 100, 100);
	GamePawn_InitializePhysics(&g_PlayerPawn, PhysicsEvent, PhysicsCollision, 16, 16);

	u8 count = 0;
	while(!Keyboard_IsKeyPressed(KEY_ESC))
	{
		UpdateV9990();

		Print_SetPosition(39, 0);
		Print_DrawChar(g_ChrAnim[count++ % 4]);
	}

	Bios_Exit(0);
}