#!/usr/bin/python
# _*_ coding:utf-8 _*_

import collections

# dic = {}
# dic["name"] = "xx"
# dic["age"] = 10

# if isinstance(dic, collections.Iterable):
# 	print "this is Iterable"
# else:
# 	print "this is not Iterable"

#遍历key
# for k in dic:
# 	print ">>> k: ", k

#获取键值对
# for k, v in dic.items():
# 	print ">>k: ", k, " ... v: ", v

# for k, v in enumerate(dic):
# 	print ">>>k : ", k , "  v: ", v

# 遍历值
# for k in dic.itervalues():
# 	print "k: ", k
# 	

# L = [ x*x for x in range(10) if x%2 != 0 ]
# for k in L:
# 	print ">>> k: ", k

# g = ( x*x for x in range(10) )
# for k in g: 
# 	print "g: k: ", k

# def char_change(c):
# 	return c.lower()

# l=['adam', 'LISA', 'barT']
# newl = map(char_change, l)
# print newl


# def is_odd(n):
# 	return n%2==0

# l=filter(is_odd, [x for x in range(100)])
# print l


# def fib():
#     a,b= 0,1
#     while 1:
#         yield b 			b=1  1  2  3
#         i = b 				i=1  1  2  3
#         b = a + b 			b=1  2  3  5
#         a = i 				a=1  1  2  
# def gnext(x = 0,y = 1):  	x = 3, y = 10
#     g = fib()
#     max = y + 1				max = 11
#     n = 1
#     l = []
#     while n <= max:
#         l.append(g.next())	1 
#         n = n + 1
#     print l[x:y]


# gnext(3, 10)



# from collections import namedtuple

# websites = [
#     ('Sohu', 'http://www.google.com/', u'张朝阳'),
#     ('Sina', 'http://www.sina.com.cn/', u'王志东'),
#     ('163', 'http://www.163.com/', u'丁磊')
# ]
# Website = namedtuple('Website', ['name', 'url', 'founder'])
# for website in websites:
#     website = Website._make(website)
#     print website.founder


# class Employee:
# 	empCount=0
# 	def __init__(self, name, salary):
# 		self.name=name
# 		self.salary=salary
# 		Employee.empCount += 1

# 	def displayCount(self):
# 		print "Total Employee %d" % Employee.empCount

# 	def displayEmployee(self):
# 		print "Name: ", self.name, ", Salary: ", self.salary

# emp1 = Employee("Zara", 2000)
# emp2 = Employee("Zara1", 3000)

# emp1.displayEmployee()

# print "empCount: %d" % Employee.empCount
# emp1.age=10
# print "age: %d" % emp1.age

# print ">>>>>>>>>>>>>"
# emp2.displayEmployee()
# emp2.displayCount()


# class Student(object):
# 	"""docstring for ClassName"""
# 	def __init__(self, arg):
# 		print ">>> init Student"
# 		self.name = arg["name"]
# 		self.age = arg["age"]

# 	def showName(self):
# 		print "this student name: ", self.name

# 	def showClassName(self):
# 		print ">>> this is Student"

# class Petrel(Student):
# 	"""docstring for Petrel"""
# 	def __init__(self, arg):
# 		super(Petrel, self).__init__(arg)
# 		print ">>> init Petrel"
# 		self.__sex=arg["sex"]

# 	def showInfo(self):
# 		print ">>> name: ", self.name, ">>> age: ", self.age, ">>> sex: ", self.__sex

# 	def showClassName(self):
# 		print ">>> this is Petrel"


# dic={}
# dic["name"]="小李子"
# dic["age"]="28"
# dic["sex"]='M'
# stud = Petrel(dic)
# stud.showName()	
# super(Petrel,stud).showClassName()	#调用基类的方法
# 



# class Student(object):
# 	__slots__ = ("name", "age", "_score", "_sex")

# 	@property
# 	def score(self):
# 	    return self._score

# 	@score.setter
# 	def score(self, value):
# 		if value >0 and value < 100:
# 			self._score = value
# 		else:
# 			raise ValueError("max");

# 	@property
# 	def sex(self):
# 	    return self._sex
	
# 	@sex.setter
# 	def sex(self, value):
# 		self._sex = value

# 	def __init__(self):
# 		super(Student, self).__init__()

# s = Student()
# s.sex=12
# print s.sex
# 
# 
# 

# path="/Users/lishuaizhe/Documents/knowledge/shellTest.sh"

# print os.path.split(path)
# print os.path.join(path, 'haha')


# from multiprocessing import Process
# import os

# def run_proc(name):
# 	print "Run child process %s (%s)" % (name, os.getpid())

# if __name__=="__main__":
# 	print "Parent process %s." % os.getpid()
# 	p = Process(target=run_proc, args=('test',))
# 	print "Process will start"
# 	p.start()
# 	p.join()
# 	print "Process end"





# from multiprocessing import Pool
# import os, time, random

# def long_time_task(name):
# 	print 'Run task %s(%s)...' % (name, os.getpid())
# 	start = time.time()
# 	time.sleep(random.random()*3)
# 	end=time.time()
# 	print "Task %s runs %0.2f seconds." % (name, end-start)


# if __name__ == "__main__":
# 	print "Parent process %s." % os.getpid()
# 	p=Pool()
# 	for i in range(5):
# 		p.apply_async(long_time_task, args(i,))
# 	print "Wait for ..."
# 	p.close()
# 	p.join()
# 	print "All DDone"
# 	


from collections import namedtuple

Point = namedtuple("Point", ['x', 'y', 'z'])
p = Point(2, 3, 4)
print p.x, p.y, p.z




sum = 0
for x in range(100):
	sum = sum + x
print "sum is %d" % sum






















		

