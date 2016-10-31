#!/usr/bin/python
# _*_ coding:utf-8 _*_
# 1.关于import 和 from ... import的区别
# 	import 为包含大的库 使用的时候需要 命名空间+函数名  类似于std::string
# 	from ... import 包含指定的内容  使用的时候不需要包含命名空间 
# 	
# 	
# 	
 

# python 面向对象
class Base(object):
	"""docstring for Base"""
	def __init__(self, arg):
		super(Base, self).__init__()
		self._name=arg["name"]

	def showName(self):
		print "name: ", self._name

	def showClassName(self):
		print "this is base"

class Sub(Base):
	"""docstring for Sub"""
	def __init__(self, arg):
		super(Sub, self).__init__(arg)
		self._age = arg["age"]

	def showAge(self):
		print "age: ", self._age

	def showClassName(self):
		print "this is Sub"

arg={}
arg["name"]="lishuaizhe"
arg["age"]=27
sub = Sub(arg)
sub.showAge()
sub.showName()
super(Sub, sub).showClassName()  #调用父类的方法
if isinstance(sub, Base):
	print "this is Base"
if isinstance(sub, Sub):
	print "this is Sub"
else:
	print "this is none"


print dir(sub)
print sub.__doc__
		
		