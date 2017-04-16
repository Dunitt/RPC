
from enum import Enum

class Status(Enum):
	REQUEST_OK = -1
	#NOTIFICATION_OK= -1
	PARSE_ERROR = 0
	INVALID_REQUEST = 1
	METHOD_NOT_FOUND = 2
	INVALID_PARAMS = 3
	INTERNAL_ERROR = 4
	DIVISION_BY_ZERO = 5
	DOMAIN_ERROR = 6
	RANGE_ERROR = 7
	UNDERFLOW_ERROR = 8
	OVERFLOW_ERROR = 9
	UNEXPECTED_ERROR = 10