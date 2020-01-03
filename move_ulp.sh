#! /bin/bash

g++ -std=c++11 -o create_ulp create_ulp.cpp
./create_ulp
mv create_polygon.ulp ~/Documents/EAGLE/ulps/
