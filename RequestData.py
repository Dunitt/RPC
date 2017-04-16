
import json
from Status import Status



class RequestData():
	def __init__(self):
		self.id= None
		self.nparams= 0
		self.params= []
		self.result= None
		self.status= None	
		self.method= ""
		self.notification= False
