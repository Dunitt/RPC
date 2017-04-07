# RPC

# Para compilar la biblioteca libmicrohttpd:

./configure --prefix=<path>/RPC/libmicrohttpd --with-libcurl=<path>/RPC/curl


# Para compilar el servidor en c++11:

export LD_LIBRARY_PATH=./libmicrohttpd/lib/

g++ -std=c++11 -o ServerStub ServerStub.cpp -I./libmicrohttpd/include/ -L./libmicrohttpd/lib/ -lmicrohttpd


# Para compilar el cliente en  C++11:

export LD_LIBRARY_PATH=./curl/lib/

g++ -std=c++11 -o main main.cpp -I./curl/include/ -L./curl/lib/ -lcurl

g++ -std=c++11 -o main main.cpp -I./curl/include/ -L./curl/lib/ -lcur


