
# -*- coding: utf-8 -*-

import sys
import json
import cmath
import requests

class ClientStub():

	def __init__(self, url, port= 12345):

		self.id= 0
		self.url= url
		self.port= port
		self.error= False
		self.batch= False
		self.req= {}
		self.res= {}
		#self.resbt= json.loads('[]')
		#print(self.res)
		#self.req= json.loads('{"jsonrpc": "2.0"}')
		#print(self.req)

	def createBatch(self):
		self.batch= True
		self.req= []

	def endBatch(self):
		#send(self.req)
		self.batch= False
		self.req.clear()

	def getBatch(self):
		pass


	def send(self, reqt):

		print("*************************************************************************")
		print ("ENVIADO: %s" % json.dumps(reqt, sort_keys=True))
		#print("http://" + self.url + ":" + str(self.port))


		if "id" not in reqt:
			notification= True
		else:
			notification= False


		try:
			r= requests.post("http://" + self.url + ":" + str(self.port), json=reqt)
		except:
			raise ConnectionError
			#return
			#print("ConnectionError")
			#self.error= True
			return
			

		#r= requests.post("http://example.com", json=self.req)

		print("RECIBIDO: %s" % r.text)


		if r.status_code != requests.codes.OK:
			raise ConnectionError
			#self.error= True
			#print("CODE: %d" % r.status_code)
		#else:
			#self.error= False

		if notification:
			return

		try:
			self.res= json.loads(r.text)
			#print(self.res)
		except:
			raise NameError("Parse error")
			#print("PARSE ERROR: {}".format(sys.exc_info()[0]))
			#self.error= True
			return

		if "result" not in self.res:
			#self.error= True

			print("ENCONTRO ERROR")
			if self.res["code"]["error"] == -32000:
				raise ZeroDivisionError

			elif self.res["code"]["error"] == -32001:
				raise ValueError

			elif self.res["code"]["error"] == -32600:
				raise NameError("Invalid Request")

			elif self.res["code"]["error"] == -32601:
				raise NameError("Method not found")

			elif self.res["code"]["error"] == -32602:
				raise NameError("Invalid params")

			elif self.res["code"]["error"] == -32002:
				#print("Unexpected error:", sys.exc_info()[0])
				raise NameError("Unexpected error")
				#print(self.res["error"]["code"])
				
				#QUIZÁS:
				#else: 
				#	NameError("Invalid response")

		print("LLEGO")
		
		#print(r.text)
		#print(r.status_code)
		#print(self.error)

	def isError(self):
		return self.error


	def sum(self, a, b, notification= False):

		tmpReq= {}
		if not notification:
			tmpReq["id"]= self.id
			self.id+= 1

		tmpReq["method"]= "sum"
		tmpReq["jsonrpc"]= "2.0"
		tmpReq["params"]= {'a': a, 'b': b}

		if self.batch:
			self.req.append(tmpReq)
			return
		else:
			self.send(tmpReq)

		if notification:
			return

		return self.res["result"]
		'''
		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")'''
'''
	def subtract(self, a, b, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["method"]= "subtract"
		self.req["params"]= {'a': a, 'b': b}

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def multiply(self, a, b, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "multiply"
		self.req["params"]= {'a': a, 'b': b}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def division(self, a, b, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "division"
		self.req["params"]= {'a': a, 'b': b}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def pow(self, a, b, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "pow"
		self.req["params"]= {'a': a, 'b': b}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def sqrt(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "sqrt"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def cos(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1
			
		self.req["id"]= self.id
		self.req["method"]= "cos"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def sin(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "sin"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def tan(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "tan"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def atan2(self, a, b, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "atan2"
		self.req["params"]= {'a': a, 'b': b}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def acos(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "acos"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def asin(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "asin"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def atan(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "atan"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def cosh(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "cosh"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def sinh(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "sinh"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def tanh(self, a, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "tanh"
		self.req["params"]= {'a': a}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return self.res["result"]
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def ccos(self, cplx, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "ccos"
		self.req["params"]= {'a': cplx.real, 'b': cplx.imag}
		#self.id+= 1

		self.send()

		if notification:
			return
		#print(self.res["result"])
		
		if not self.isError():
			return complex(self.res["result"][0], self.res["result"][1])
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def csin(self, cplx, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "csin"
		self.req["params"]= {'a': cplx.real, 'b': cplx.imag}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return complex(self.res["result"][0], self.res["result"][1])
		else:
			print("ERROR: RESULTADO INVÁLIDO")

	def ctan(self, cplx, notification= False):

		if not notification:
			self.req["id"]= self.id
			self.id+= 1

		self.req["id"]= self.id
		self.req["method"]= "ctan"
		self.req["params"]= {'a': cplx.real, 'b': cplx.imag}
		#self.id+= 1

		self.send()

		if notification:
			return

		if not self.isError():
			return complex(self.res["result"][0], self.res["result"][1])
		else:
			print("ERROR: RESULTADO INVÁLIDO")

'''
