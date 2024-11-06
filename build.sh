echo "Building"
gcc src/Asteroids.c -o build/Asteroids -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g 
