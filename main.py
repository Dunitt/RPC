
from ClientStub import ClientStub

client=  ClientStub("localhost", 8888)

def main():


	print("testSUM: ", client.sum(1.3, 3.2, True))



if __name__ == "__main__":
	main()