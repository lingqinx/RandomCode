from __future__ import division
import numpy

def integral(a,b,n):
	try:
		delta=float((b-a)/n)
	except ZeroDivisionError:
		delta=0
	x = numpy.arange(a,b,delta)
	f = numpy.sin(x)/x
	return f.sum()*delta
#print integral(1,4,300)
from __future__ import division
import numpy

def derivative(a,b,n):
	x = a+ (b-a)*numpy.random.rand(n)	
	x = numpy.sort(x)
	f = numpy.sin(x)/x
	#print f[1:],f[:-1]
	dy = (f[1:]-f[:-1])/(x[1:]-x[:-1])
	return dy
#print derivative(1,4,30)

class Node(object):
	def __init__(self, kappa):
		string = kappa
		kappa = parenthesis_replace(string)
		#length=end=0
		#for k in range(len(string)):
			#while string[k]=="$":
				#length+=1
		if self.has_per(kappa)==True and len(kappa)>1:	
			self.data="("
			self.left=Node(string[1:-1])
		
		i = -1
		if kappa.rfind("+") != -1:
			i = kappa.rfind("+")
		elif kappa.rfind("-") != -1:
			i = kappa.rfind("-")
		elif kappa.rfind("*") != -1:
			i = kappa.rfind("*")
		elif kappa.rfind("/") != -1:
			i = kappa.rfind("/")
		
		
		if i != -1 and self.has_per(kappa)==False:
			self.data = string[i]
			print string,kappa
			self.left = Node(string[:i])
			self.right = Node(string[i + 1:])

		elif self.has_per(kappa)==False:
			self.data = float(kappa)
			self.left = None
			self.right = None
	def has_per(self,kappa):
		flag=True
		for x in kappa:
			if x!="$":
				flag=False
		return flag

	def calculate(self):
		print self.data
		if self.data == "+":
			print self.data
			return self.left.calculate() + self.right.calculate()
		elif self.data == "-":
			return self.left.calculate() - self.right.calculate()
		elif self.data == "*":
			return self.left.calculate() * self.right.calculate()
		elif self.data == "/":
			return self.left.calculate() / self.right.calculate()
		elif self.data == "(":
			return self.left.calculate()
		else:
			return self.data

def parenthesis_replace(kappa):
	s = ""
	level = 0
	for c in kappa:
		if c == "(":
			level += 1
		if level > 0:
			s += "$"
		else:
			s += c
		if c == ")":
			level -= 1
	return s
    
node = Node("1*(2*(3+4))+1") 
#print parenthesis_replace("(1+2)*(3+4)+1")

print node.calculate()