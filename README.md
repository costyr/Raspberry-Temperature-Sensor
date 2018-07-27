# Raspberry-Temperature-Sensor
Monitors the temperature in multiple rooms and sends the data to a server using Socket.IO protocol

## Prerequisites

- Clang 6
- Boost 1.67

### Install Clang on Raspberry PI

```
cd ~
wget http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-armv7a-linux-gnueabihf.tar.xz
```
Extract Clang archive and move clang folder to /usr/local

```
tar -xf clang+llvm-6.0.0-armv7a-linux-gnueabihf.tar.xz
rm clang+llvm-6.0.0-armv7a-linux-gnueabihf.tar.xz
mv clang+llvm-6.0.0-armv7a-linux-gnueabihf clang_6.0.0
sudo mv clang_6.0.0 /usr/local
```
Add clang compiler to PATH

```
echo 'export PATH=/usr/local/clang_6.0.0/bin:$PATH' >> .bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/clang_6.0.0/lib:$LD_LIBRARY_PATH' >> .bashrc
```

### Install Boost on Raspeberry PI

```
cd ~
wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
```

Extract archive and move to /usr/local

```
tar -xvzf boost_1_67_0.tar.gz
rm boost_1_67_0.tar.gz
sudo mv boost_1_67_0 /usr/local
```

Build the necessary subset only

```
cd /usr/local/boost_1_67_0
./bootstrap.sh
bjam install --prefix="<your boost install folder>" --with-system --with-date_time --with-random link=static runtime-link=shared threading=multi
```

## Build project

```
make
```
