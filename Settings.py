
import json

def init():

	global Methods
	global Errors

	with open("./MethodSettings.json") as file:
		Methods= json.load(file)

	with open("./Errors.json") as file:
		Errors= json.load(file)
