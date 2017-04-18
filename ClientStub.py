
import json
import requests
from BatchStage import BatchStage

class ClientStub():

	def __init__(self, url, port= 12345):

		self.id= 0
		self.url= url
		self.port= port
		self.error= False
		self.batch= BatchStage.INACTIVE
		self.req= None
		self.res= None
		#self.resbt= json.loads('[]')
		#print(self.res)
		#self.req= json.loads('{"jsonrpc": "2.0"}')
		#print(self.req)

	def isReady(self):
		pass

	def beginBatch(self):
		self.batch= BatchStage.ACTIVE
		self.req= []

	def endBatch(self):
		
		if self.batch != BatchStage.ACTIVE:
			return

		self.batch= BatchStage.READY
		data= json.dumps(self.req)
		print("ENVIADO: ", data)
		self.send(data)
		self.batch= BatchStage.RECEIVED


	def getBatch(self, idx):

		if self.batch != BatchStage.RECEIVED:
			raise NameError("There are not batch")

		
		if idx > len(self.res) - 1:
			raise NameError("Index out of range")

		outJson= self.res[idx]
		if "result" in outJson:
			return outJson["result"]

		else:
			if outJson["error"]["code"] == -32000:
				raise NameError("Division by zero")

			elif outJson["error"]["code"] == -32001:
				raise NameError("Domain error")

			elif outJson["error"]["code"] == -32002:
				raise NameError("Range error")

			elif outJson["error"]["code"] == -32003:
				raise NameError("Underflow error")

			elif outJson["error"]["code"] == -32004:
				raise NameError("Overflow error")

			elif outJson["error"]["code"] == -32000:
				raise NameError("Division by zero")

			elif outJson["error"]["code"] == -32600:
					raise NameError("Invalid Request")

			elif outJson["error"]["code"] == -32601:
				raise NameError("Method not found")

			elif outJson["error"]["code"] == -32602:
				raise NameError("Invalid params")

			elif outJson["error"]["code"] == -32002:
				raise NameError("Unexpected error")
			else:
				raise NameError("Invalid response")


	def send(self, data):
		
		#if self.isReady():
		#	return True

		try:
			r= requests.post("http://" + self.url + ":" + str(self.port), json=json.loads(data))
		except:
			raise ConnectionError
			#return
			#print("ConnectionError")
			#self.error= True
			return

		print("RECIBIDO: %s" % r.text)


		if r.status_code != requests.codes.OK:
			raise ConnectionError
			return True

		try:
			self.res= json.loads(r.text)
		except:
			raise NameError("Parse error")
			#print("PARSE ERROR: {}".format(sys.exc_info()[0]))
			#self.error= True
			print("SE EJECUTA")
			return True

		if self.batch == BatchStage.READY:
			self.batch= BatchStage.RECEIVED
			return False

		if "result" in self.res:
			return False
		else:
			raise NameError("Invalid response")
			return True
	
		
	def sum(self, a, b, notification= False):
		
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "sum"
		outJson["params"]= {"a": a, "b": b}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]

	

	def subtract(self, a, b, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "subtract"
		outJson["params"]= {"a": a, "b": b}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]

	

	def multiply(self, a, b, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "multiply"
		outJson["params"]= {"a": a, "b": b}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]

	

	def division(self, a, b, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "division"
		outJson["params"]= {"a": a, "b": b}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]

	

	def pow(self, a, b, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "pow"
		outJson["params"]= {"a": a, "b": b}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def sqrt(self, a, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "sqrt"
		outJson["params"]= {"a": a}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	
	def cos(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "cos"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def sin(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "sin"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def tan(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "tan"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def atan2(self, beta, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "atan2"
		outJson["params"]= {"a": alpha, "b": beta}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def acos(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "acos"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def asin(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "asin"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def atan(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "atan"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def cosh(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "cosh"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def sinh(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "sinh"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]


	def tanh(self, alpha, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "tanh"
		outJson["params"]= {"a": alpha}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return self.res["result"]



	def ccos(self, cplx, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "ccos"
		outJson["params"]= {"a": cplx.real, "b": cplx.imag}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return complex(self.res["result"][0], self.res["result"][1])


	def csin(self, cplx, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "csin"
		outJson["params"]= {"a": cplx.real, "b": cplx.imag}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return complex(self.res["result"][0], self.res["result"][1])


	def ctan(self, cplx, notification= False):
		if self.batch == BatchStage.RECEIVED:
			self.batch= BatchStage.INACTIVE

		outJson= {}
		outJson["jsonrpc"]= "2.0"
		outJson["method"]= "ctan"
		outJson["params"]= {"a": cplx.real, "b": cplx.imag}
		if not notification:
			outJson["id"]= self.id
			self.id+= 1

		data= json.dumps(outJson)

		if self.batch == BatchStage.ACTIVE:
			self.req.append(outJson)
			return 0
		#print("PRUEBA")

		print("ENVIADO: ", data)
		self.error= self.send(data)
		if not self.error:
			return complex(self.res["result"][0], self.res["result"][1])

