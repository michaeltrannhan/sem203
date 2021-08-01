clear
echo "###################################################################################"
echo "##############              GRADING ASSINMENT3 OF DSA               ###############"
echo "##############             (unittest for C++: doctest)              ###############"
echo "###################################################################################"

echo "[1] removing previous output ..."
rm -f ./assignment3

echo "[2] building DSACPP, please wait ..."
g++ ./dsacpp/assignment3.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -I ./doctest -o assignment3

echo "###################################################################################"
echo "[3] running the test ..."
echo "\n"
./assignment3
echo "\n"
