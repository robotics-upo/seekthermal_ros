# seekthermal_ros Node
ROS node for Seek thermal imaging devices

## Depedencies

This node has a lot of dependencies and you need to install them manually because of the PPA does not work. You can also run the script `installDependencies.sh` in the scripts folder. 

First install these dependencies from the repositories:

`sudo apt-get install doxygen pkg-config debhelper cmake groff qt4-dev-tools -y`

Download and install [libpng12-0](http://ftp.us.debian.org/debian/pool/main/libp/libpng/libpng12-0_1.2.50-2+deb8u3_amd64.deb).

`sudo dpkg -i libpng12-0_1.2.50-2+deb8u3_amd64.deb`

Then, download, compile and install with cmake ReMake package:

`git clone https://github.com/kralf/remake.git && mkdir -p remake/build && cd remake/build && cmake .. && make && sudo make install`

Then, you compile and install libseekthermal:

`git clone https://github.com/robotics-upo/libseekthermal.git && mkdir -p libseekthermal/build && cd libseekthermal/build && cmake .. && make && sudo make install`

## Known Issues

If you try to launch the included launch and it gives Usb Error: Access denied, maybe you should need to add your user to the dialout group

`sudo adduser <username> dialout`

## Todo

- [x] Improve performance. Sometimes the CPU comsuption is 100%: Finally fixed, there were 2 while loops withouth sleeps....
- [ ] Try to improve framerate. 
- [ ] Make it plug and play: Right know, you have to launch the node with the camera connected, and it crashes if you disconnect it. The best behavior would be to wait until a device is discovered at the startup and if the camera is disconnected, wait again.