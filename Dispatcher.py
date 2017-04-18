
import sys
import json
import Library
from Status import Status
from inspect import signature
from RequestData import RequestData

class Dispatcher():
	def __init__(self):
		pass

	def Dispatch(self, inJson):

		mt= inJson["method"]
		sig= signature(Library.funcdict[mt])
		t= len(sig.parameters)
		pm= [None] #¿QUÉ PASA SI EL MÉTODO NO TIENE PARÁMETROS?


		nid= inJson["id"] if ("id" in inJson) else None
		outJson= {"jsonrpc": "2.0", "id": nid}

		if "params" in inJson:

			pm= [None] * len(inJson["params"]) #QUIZÁS SE PUEDA COLOCAR DESPUÉS DEL "else:"

			if isinstance(inJson["params"], list):
				pm= inJson["params"]

			else:
				for (key, value) in inJson["params"].items():
					if key == "a":
						pm[0]= value

					if key == "b":
						pm[1]= value

		# try:
			result= Library.funcdict[mt](pm)

		# except ZeroDivisionError:
		# 	outJson["error"]= errors[Status.DIVISION_BY_ZERO]["error"]
		# 	return outJson

		# except ValueError:
		# 	outJson["error"]= errors[6]["error"]
		# 	return outJson

		# except:
		# 	outJson["error"]= errors[Status.UNEXPECTED_ERROR]["error"]
		# 	return outJson

		if isinstance(result, complex):
			outJson["result"]= [result.real, result.imag]
		else:
			outJson["result"]= result

		return outJson
