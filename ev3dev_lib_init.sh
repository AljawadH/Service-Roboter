#!/bin/bash
echo "init lib in ../ev3dev-c";
cd ..;
git clone https://github.com/in4lio/ev3dev-c.git;
cd ev3dev-c;
git submodule update --init --recursive;

#docker betreten und den rest im docker ausfueren

#cd source/ev3;
#make;
#sudo make install;
#make shared;
#sudo make shared-install;
