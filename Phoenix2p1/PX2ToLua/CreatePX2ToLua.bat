: dir
cd /d E:/Phoenix3d/Phoenix2p1/PX2ToLua/
del "PX2ToLua.cpp"
: tolua
tolua++.exe -n PX2 -o PX2ToLua.cpp PX2ToLua.pkg