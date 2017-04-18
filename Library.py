
# -*- coding: utf-8 -*-

import math
import cmath

def sum(arg):
	return arg[0] + arg[1]

def subtract(arg):
	return arg[0] - arg[1]

def multiply(arg):
	return arg[0] * arg[1]

def division(arg):
	if isinstance(arg[0], int) and isinstance(arg[0], int):
		return arg[0] // arg[1]	#Utilizar // para enteros

	elif isinstance(arg[0], float) and isinstance(arg[0], float):
		return arg[0] / arg[1]	#Utilizar // para enteros

def pow(arg):
	return math.pow(arg[0], arg[1]) #Utilizar ** para enteros

def sqrt(arg):
	return math.sqrt(arg[0])

def cos(arg):
	return math.cos(arg[0])

def sin(arg):
	return math.sin(arg[0])

def tan(arg):
	return math.tan(arg[0])

def atan2(arg):
	return math.atan2(arg[0], arg[1])

def acos(arg):
	return math.acos(arg[0])

def asin(arg):
	return math.asin(arg[0])

def atan(arg):
	return math.atan(arg[0])

def cosh(arg):
	return math.cosh(arg[0])

def sinh(arg):
	return math.sinh(arg[0])

def tanh(arg):
	return math.tanh(arg[0])

def ccos(arg):
	return cmath.cos(complex(arg[0], arg[1]))

def csin(arg):
	return cmath.sin(complex(arg[0], arg[1]))

def ctan(arg):
	return cmath.tan(complex(arg[0], arg[1]))

funcdict = {

	"sum": sum,
	"subtract": subtract,
	"multiply": multiply,
	"division": division,
	"pow": pow,
	"sqrt": sqrt,
	"cos": cos,
	"sin": sin,
	"tan": tan,
	"atan2": atan2,
	"acos": acos,
	"asin": asin,
	"atan": atan,
	"cosh": cosh,
	"sinh": sinh,
	"tanh": tanh,
	"ccos": ccos,
	"csin": csin,
	"ctan": ctan

}