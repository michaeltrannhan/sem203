clear
echo "###################################################################################"
echo "##############  Simple Examples using DSA-Framework for C++         ###############"
echo "###################################################################################"

echo "[1] removing previous output ..."
rm -f ./examples/bin/*

echo "[2] building examples, please wait ..."
g++ ./examples/src/triangle.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -o ./examples/bin/triangle
g++ ./examples/src/polyline.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -o ./examples/bin/polyline
g++ ./examples/src/pointdemo.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -o ./examples/bin/pointdemo
g++ ./examples/src/intro/lecture1.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -o ./examples/src/intro/lecture1
g++ ./examples/src/intro/pointer.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -o ./examples/src/intro/pointer

echo "###################################################################################"
echo "[3] running examples"

echo "\n"
echo "PointDemo program:"
./examples/bin/pointdemo

echo "\n"
echo "Triangle program:"
./examples/bin/triangle

echo "\n"
echo "Polyline program:"
./examples/bin/polyline