
import math
import cmath
from ClientStub import ClientStub

client=  ClientStub("localhost", 8888)

def main():

	for i in range(10000):
		client.beginBatch()
		print("testSUM: ", client.sum(1.3, 3.2))
		print(client.subtract(1, 3), 1 - 3)
		print(client.subtract(1.1, 3.3), 1.1 - 3.3)
		print(client.multiply(1, 3), 1 * 3)
		print(client.multiply(1.1, 3.3), 1.1 * 3.3)
		client.endBatch()

		print(client.getBatch(0))
		print(client.getBatch(1))
		print(client.getBatch(2))
		print(client.getBatch(3))
		print(client.getBatch(4))
		print(client.division(1, 3), 1 // 3)
	#print(client.getBatch(5))
	#print(client.getBatch(100))


	for i in range(10000):
		#print(client.division(1, 0))
		#print(client.sqrt(3.7), math.sqrt(3.7))
		print(client.division(1.1, 3.3), 1.1 / 3.3)
		print(client.pow(3.6, 2.1), math.pow(3.6, 2.1))
		print(client.sqrt(3.7), math.sqrt(3.7))
		print(client.cos(3.7), math.cos(3.7))
		print(client.sin(3.7), math.sin(3.7))
		print(client.tan(3.7), math.tan(3.7))
		print(client.atan2(3.7, 4.5), math.atan2(3.7, 4.5))
		print(client.acos(0.7), math.acos(0.7))
		print(client.asin(0.7), math.asin(0.7))
		print(client.atan(0.7), math.atan(0.7))
		print(client.cosh(3.7), math.cosh(3.7))
		print(client.sinh(3.7), math.sinh(3.7))
		print(client.tanh(3.7), math.tanh(3.7))
		print(client.ccos(complex(3.7, 1.0)), cmath.cos(complex(3.7, 1.0)))
		print(client.csin(complex(3.7, 1.0)), cmath.sin(complex(3.7, 1.0)))
		print(client.ctan(complex(3.7, 1.0)), cmath.tan(complex(3.7, 1.0)))
		

if __name__ == "__main__":
	main()