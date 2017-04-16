
# -*- coding: utf-8 -*-

import sys
import json
from Processor import Processor
from flask import Flask, request, jsonify

app = Flask(__name__)


@app.route('/', methods = ["POST"])
def index():
	pass


if __name__ == '__main__':
    app.run(debug= True, port= 8888)