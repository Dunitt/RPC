
import json
import Settings
from Status import Status
from Dispatcher import Dispatcher
from RequestData import RequestData

class Processor():

	def __init__(self, data):
		if (not Settings.Methods) or (not Settings.Errors):
			print("Error iniando.")

		self.inJson= None
		self.outJson= None
		self.isBatch= False
		self.requests= []
		self.response= []
		self.dispatcher= Dispatcher()

		try:
			self.inJson= json.loads(data)
		except:
			#print("PARSE ERROR")
			self.outJson= Processor.getErrors(Status.PARSE_ERROR)
			return

		if not self.inJson:
			#print("VACIO")
			self.outJson= Processor.getErrors(Status.INVALID_REQUEST)
			return

		if isinstance(self.inJson, dict):
			#print("OBJETO")
			self.isBatch= False
			self.requests.append(self.inJson)
			#print(self.requests)

		elif isinstance(self.inJson, list):
			#print("LOTE")
			self.isBatch= True
			self.requests= self.inJson
			#print(self.requests)



		#print(isinstance(self.inJson, dict))
		#print(self.inJson)


	def Process(self):

		for itJson in self.requests:

			out= None
			notification= False
			status= self.validate(json.dumps(itJson))
			#print("Status: ", status)
			# print(Status.RANGE_ERROR < Status.REQUEST_OK)

			if (status != Status.PARSE_ERROR) and (status != Status.INVALID_REQUEST) and ("id" not in itJson):
				notification= True

			if status >= Status.PARSE_ERROR:

				out= Processor.getErrors(status)
				if (status != Status.PARSE_ERROR) and (status != Status.INVALID_REQUEST) and (not notification):
					out["id"]= itJson["id"]

			else:
				out= self.dispatcher.Dispatch(itJson)
				print("OUT: ", out)

			if not notification:
				self.response.append(out)

		if self.isBatch:
			if self.response:
				self.outJson= self.response
			else:
				self.outJson= None

		elif self.response:
			#print("VACIO: ", self.response)
			self.outJson= self.response[0]


	def validate(self, data):
		
		#print("VALIDATE")
		currentJson= json.loads(data)

		#print(currentJson)
		#print(isinstance(currentJson, dict))
		
		if not currentJson:
			#print("VACIO")
			return Status.INVALID_REQUEST

		if not isinstance(currentJson, dict):
			#print("NO OBJETO")
			return Status.INVALID_REQUEST

		if ("jsonrpc" not in currentJson) or ("method" not in currentJson):
		 	return Status.INVALID_REQUEST

		if (not isinstance(currentJson["jsonrpc"], str)) or (isinstance(currentJson["jsonrpc"], str) and currentJson["jsonrpc"] != "2.0"):
		 	return Status.INVALID_REQUEST

		if not isinstance(currentJson["method"], str):
			return Status.INVALID_REQUEST

		mt= currentJson["method"].lower()
		if mt.startswith("rpc."):
		 	return Status.INVALID_REQUEST

		if ("params" in currentJson) and (not (isinstance(currentJson["params"], list) or isinstance(currentJson["params"], dict))):
		 	return Status.INVALID_REQUEST

		e, p= False, False
		for mt in Settings.Methods:

			if mt["method"] == currentJson["method"]:

				e= True
				if ("list" not in mt) and ("params" not in currentJson):
					p= True
					break

				elif ("list" in mt) and ("params" in currentJson) and (isinstance(currentJson["params"], list)) and (len(mt["list"]) == len(currentJson["params"])):

					pl= True
					for pm, pmList in zip(currentJson["params"], mt["list"]):

						if pmList == "int" and not isinstance(pm, int):
							pl= False
							break

						if pmList == "double" and not isinstance(pm, float):
							pl= False
							break

					p= pl
					if pl:
						break

				elif ("names" in mt) and ("params" in currentJson) and (isinstance(currentJson["params"], dict)) and (len(mt["names"]) == len(currentJson["params"])):
									
					pl= True	#ES POSIBLE QUITAR "pmKey".
					for (pmKey, pmValue), (pmNamesKey, pmNamesValue) in zip(currentJson["params"].items(), mt["names"].items()):
						
						if pmNamesKey not in currentJson["params"]:
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
			return Status.METHOD_NOT_FOUND

		if not p:
			return Status.INVALID_PARAMS

		if ("id" in currentJson) and not (isinstance(currentJson["id"], str) or isinstance(currentJson["id"], (int, float)) or isinstance(currentJson["id"], None)):
			return Status.INVALID_REQUEST

		return Status.REQUEST_OK
	
	def getResponse(self):
		if self.outJson is None:
			return ""
		else:
			return json.dumps(self.outJson)

	@staticmethod
	def getErrors(status):
		return Settings.Errors[status.value]

	
