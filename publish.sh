#!/bin/bash

# Device
rm -rf device/
mkdir -p device/config/chips/
cp -rf ../../../device/config/chips/v851s/ device/config/chips/

# Target
rm -rf openwrt/target/ 
mkdir -p openwrt/target/
cp -rf ../../../openwrt/target/v851s/ openwrt/target/

# package/lizard
rm -rf openwrt/package/lizard/
mkdir openwrt/package/lizard
cp -rf ../../../openwrt/package/lizard/* openwrt/package/lizard/