

from enum import Enum

class OrderedEnum(Enum):
	def __ge__(self, other):
		if self.__class__ is other.__class__:
	 		return self.value >= other.value
		return NotImplemented
	def __gt__(self, other):
		if self.__class__ is other.__class__:
			return self.value > other.value
		return NotImplemented
	def __le__(self, other):
		if self.__class__ is other.__class__:
			return self.value <= other.value
		return NotImplemented
	def __lt__(self, other):
		if self.__class__ is other.__class__:
			return self.value < other.value
		return NotImplemented

class Status(OrderedEnum):
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
