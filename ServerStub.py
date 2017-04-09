
# -*- coding: utf-8 -*-

import sys
import json
import Dispatcher
from inspect import signature
from flask import Flask, request, jsonify

app = Flask(__name__)

with open("./MethodSettings.json") as file:
	methods= json.load(file)

with open("./Errors.json") as file:
	errors= json.load(file)

def validate(inJson):

		if inJson is None:
			return 0

		if not isinstance(inJson, dict):
			return -1

		if ("jsonrpc" not in inJson) or ("method" not in inJson):
			return -1

		if (not isinstance(inJson["jsonrpc"], str)) or (isinstance(inJson["jsonrpc"], str) and inJson["jsonrpc"] != "2.0"):
			return -1

		if not isinstance(inJson["method"], str):
			return -1

		mt= inJson["method"].lower()
		if mt.startswith("rpc."):
			return -2

		if ("params" in inJson) and (not (isinstance(inJson["params"], list) or isinstance(inJson["params"], dict))):
			return -1

		e, p= False, False
		for mt in methods:

			if mt["method"] == inJson["method"]:

				e= True
				if ("list" not in mt) and ("params" not in inJson):
					p= True
					break

				elif ("list" in mt) and ("params" in inJson) and (isinstance(inJson["params"], list)) and (len(mt["list"]) == len(inJson["params"])):

					pl= True
					for pm, pmList in zip(inJson["params"], mt["list"]):

						if pmList == "int" and not isinstance(pm, int):
							pl= False
							break

						if pmList == "double" and not isinstance(pm, float):
							pl= False
							break

					p= pl
					if pl:
						break

				elif ("names" in mt) and ("params" in inJson) and (isinstance(inJson["params"], dict)) and (len(mt["names"]) == len(inJson["params"])):
									
					pl= True	#ES POSIBLE QUITAR "pmKey".
					for (pmKey, pmValue), (pmNamesKey, pmNamesValue) in zip(inJson["params"].items(), mt["names"].items()):
						
						if pmNamesKey not in inJson["params"]:
							pl= False
							break

						if pmNamesValue == "int" and not isinstance(pmValue, int):
							pl= False
							break

						if pmNamesValue == "double" and not isinstance(pmValue, float):
							pl= False
							break
						
					p= pl
					if pl:
						break

		if not e:
			return -2

		if not p:
			return -3

		if "id" not in inJson:
			return 1
		elif not isinstance(inJson["id"], str) and not isinstance(inJson["id"], (int, float)) and isinstance(inJson["id"], None):
			return -1

		return 2


def dispatch(inJson):

	mt= inJson["method"]
	sig= signature(Dispatcher.funcdict[mt])
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

	try:
		result= Dispatcher.funcdict[mt](pm)

	except ZeroDivisionError:
		outJson["error"]= errors[5]["error"]
		return outJson

	except ValueError:
		outJson["error"]= errors[6]["error"]
		return outJson

	except:
		outJson["error"]= errors[7]["error"]
		return outJson

	if isinstance(result, complex):
		outJson["result"]= [result.real, result.imag]
	else:
		outJson["result"]= result

	return outJson




@app.route('/', methods = ["POST"])
def index():

	inJson= request.get_json(force= True, silent= True)
	print("*****************************************************************************************************")
	print("RECIBIDO: %s" % request.data.decode("utf-8 -*-"))

	if isinstance(inJson, list):

		if not inJson:
			print("ENVIADO: %s" % (json.dumps(errors[1], sort_keys=True)))
			return json.dumps(errors[1])

		arrayJson= []
		for itJson in inJson:

			t= validate(itJson)

			if t <= 0:
				outJson= errors[abs(t)]
				if (t != 0)  and ("id" in inJson):
					outJson["id"]= inJson["id"]

			else:
				outJson= dispatch(itJson)

			if t != 1:
				arrayJson.append(outJson)

		if arrayJson:
			print("ENVIADO: %s" % (json.dumps(arrayJson, sort_keys=True)))
			return json.dumps(arrayJson)
		else:
			print("ENVIADO: %s" % (json.dumps(arrayJson, sort_keys=True)))
			return ("", 204)


	else:
		#DECLARAR outJson AQUÍ
		t= validate(inJson)

		if t <= 0:

			outJson= errors[abs(t)]
			if (t != 0)  and ("id" in inJson):
				outJson["id"]= inJson["id"]

		else:
			outJson= dispatch(inJson)
	
		if t == 1:
			print("ENVIADO: %s" % "")
			return ("", 204)
		else: #SE PUEDE ELIMINAR EL ELSE
			print("ENVIADO: %s" % (json.dumps(outJson, sort_keys=True)))
			return json.dumps(outJson)

	print("ENVIADO: %s" % (json.dumps(errors[4], sort_keys=True)))
	return dumps(errors[4]) #ESCRIBIR json.dumps(errors[4])


if __name__ == '__main__':
    app.run(debug= True, port= 8888)