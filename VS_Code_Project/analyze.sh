echo Showing profiles...
cd build/prof
feh game.gif --geometry 960x990 &
kcachegrind game.callgrind
firefox flamegraph_out.svg