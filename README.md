# RPC

## Para compilar la biblioteca libmicrohttpd:
```
1. ./configure --prefix=<path>/RPC/libmicrohttpd --with-libcurl=<path>/RPC/curl
2. make
3. make install
```

## Para compilar el servidor en C++11:
```
1. export LD_LIBRARY_PATH=./libmicrohttpd/lib/
2. g++ -std=c++11 -o ServerStub.out ServerStub.cpp -I./libmicrohttpd/include/ -L./libmicrohttpd/lib/ -lmicrohttpd
```

## Para compilar el cliente en  C++11:
```
1. export LD_LIBRARY_PATH=./curl/lib/
2. g++ -std=c++11 -o main.out main.cpp -I./curl/include/ -L./curl/lib/ -lcurl
```


