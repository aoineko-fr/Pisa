:: Path
set Tools=..\..\tools
set MSXtk=%Tools%\MSXtk\bin
set Dest=.\content

if not exist %Dest% md %Dest%

%MSXtk%\MSXimg.exe datasrc/graph_tileset.png -copy datasrc/gk.txt -out %Dest%\tileset.h -pos 0 128 -size 256 32 -name g_DataTilset -trans 0xFF00FF -bpc 4 -pal custom --pal24
%MSXtk%\MSXimg.exe datasrc/graph_bg.png -copy datasrc/gk.txt -out %Dest%\bg.bin -pos 0 0 -size 256 212 -name g_DataBG -bpc 4 -pal custom --pal24
%MSXtk%\MSXimg.exe datasrc/graph_sprite.png -copy datasrc/gk.txt -out %Dest%\sprite.h -pos 0 0 -size 256 32 -name g_DataSprite -trans 0xFF00FF -bpc 4 -pal custom --pal24
