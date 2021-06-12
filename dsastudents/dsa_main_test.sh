clear
echo "###################################################################################"
echo "##############        Testing DSA-Framework for C++ (DSACPP)        ###############"
echo "##############             (unittest for C++: doctest)              ###############"
echo "###################################################################################"

echo "[1] removing previous output ..."
rm -f ./dsacpp/dsa_main_test

echo "[2] building DSACPP, please wait ..."
g++ ./dsacpp/dsa_main_test.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -I ./doctest -o dsa_main_test

echo "###################################################################################"
echo "[3] running the test ..."
echo "\n"
./dsa_main_test
echo "\n"