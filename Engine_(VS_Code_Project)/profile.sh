cd build
export CPUPROFILE=game.prof
export PATH=/usr/local/src/FlameGraph:$PATH
#export HEAPPROFILE=HEAP_
echo Starting game with profiler...
./game
pprof --gif game game.prof > game.gif
pprof --collapsed ./game game.prof >> flamegraph.collapse
/usr/local/src/FlameGraph/flamegraph.pl flamegraph.collapse > flamegraph_out.svg
pprof --callgrind game game.prof > game.callgrind
cd ..
bash analyze.sh
