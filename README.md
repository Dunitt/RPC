# RPC

## Para compilar la biblioteca libmicrohttpd:
```
./configure --prefix=<path>/RPC/libmicrohttpd --with-libcurl=<path>/RPC/curl
make
make install
```

## Para compilar el servidor en C++11:
```
export LD_LIBRARY_PATH=./libmicrohttpd/lib/
g++ -std=c++11 -o ServerStub.out ServerStub.cpp -I./libmicrohttpd/include/ -L./libmicrohttpd/lib/ -lmicrohttpd
```

## Para compilar el cliente en C++11:
```
export LD_LIBRARY_PATH=./curl/lib/
g++ -std=c++11 -o main.out main.cpp -I./curl/include/ -L./curl/lib/ -lcurl
```

## Para compilar el servidor en Python 3:

### Se requiere instalar:
1. Requests
2. Flask

## Para compilar el cliente en Python 3:

Sin requerimientos extras.

