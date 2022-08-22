cd build
export CPUPROFILER=game.prof
echo Starting game with profiler...
./game
pprof --gif game game.prof > game.gif 
pprof --callgrind game game.prof > game.callgrind   
cd ..
bash analyze.sh
