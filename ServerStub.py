
# -*- coding: utf-8 -*-

import sys
import json
import Settings
from Status import Status
from Processor import Processor
from flask import Flask, request, jsonify

app = Flask(__name__)


@app.route('/', methods = ["POST"])
def index():

	request.get_json(force= True, silent= True)
	print("*****************************************************************************************************")
	print("RECIBIDO: %s" % request.data.decode("utf-8 -*-"))

	data= request.data.decode("utf-8 -*-")

	processor= Processor(data)
	processor.Process()
	data= processor.getResponse()

	print("ENVIADO: %s" % data)

	return data


if __name__ == '__main__':
	Settings.init()
	app.run(debug= True, port= 8888)