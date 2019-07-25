sudo apt-get install bison
sudo apt-get install swig
cd sphinxbase-5prealpha
./autogen.sh
.configure
make
sudo make install
export LD_LIBRARY_PATH=/usr/local/lib
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
cd ../pocketsphinx-5prealpha
./autogen.sh
.configure
make
sudo make install
