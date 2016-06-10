#!/usr/bin/env sh 

sudo apt-get remove -y cmake # 卸载旧版本的 
sudo add-apt-repository -y ppa:george-edison55/precise-backports 
sudo apt-get update  
sudo apt-get install cmake 
cmake --version
