
# -*- coding: utf-8 -*-

import json
from ServerStub import ServerStub
from flask import Flask, request, jsonify

app = Flask(__name__)
serverStub= ServerStub("./MethodSettings.json")

@app.route('/', methods = ["POST"])
#@app.route('/')
def index():

	r= request.get_json(force= True, silent= True)
	print("RECIBIDO: {}".format(request.data.decode("utf-8 -*-")))
	#print(request.data)

	#print(r)

	if r is None:
		#raise
		#print("ENTRO")
		print('ENVIADO: {"jsonrpc": "2.0", "error": {"code": -32700, "message": "Parse error"}, "id": null}')
		return jsonify({"jsonrpc": "2.0", "error": {"code": -32700, "message": "Parse error"}, "id": None})


	resp= serverStub.dispatch(r)
	print('ENVIADO: ' + json.dumps(resp))
	return jsonify(resp)


	print('ENVIADO: {"jsonrpc": "2.0", "error": {"code": -32603, "message": "Internal error"}, "id": null}')
	return jsonify({"jsonrpc": "2.0", "error": {"code": -32603, "message": "Internal error"}, "id": None})

if __name__ == '__main__':
    app.run(debug= True, port= 8888)