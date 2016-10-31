#!/usr/bin/python
# -*- coding:utf-8 -*-

#	1.首先思路为获取所有股票代码
#	2.获取每只代表对应的所有信息
#	3.



import json
import tushare as ts
from pandas import Series,DataFrame
import pandas as pd

debug=1

#定义保存文件的路径
stock_item_path="/Users/lishuaizhe/Documents/knowledge/stock_name.json"

#DataFrame转换为字典型
def df_to_dic( code, stockData_df ):
	data_dic={}
	for i, data in enumerate(stockData_df.values):
		data_dic[i]={'code':code, 'p_change':data[6]}
	return data_dic

#定义函数获取信息
def getNetData():
	print "... to get server data ..."
	# 行业分类
	stockData_df=ts.get_industry_classified()
	# 概念分类
	# df=ts.get_concept_classified()
	#上证50成份股
	# stockData_df=ts.get_sz50s()
	#保存股票基础信息到文件
	# df.to_json(stock_item_path,orient='records')
	stock={}
	for i, data in enumerate(stockData_df.values):
		stock[i]={}
		print ">>>>> ", data[0], "   ", data[1], "   ", data[2]
		stock[i]['code'], stock[i]["name"]=data[0], data[1]
	return stock
	
#获取每条股票最近两天的数据
def getTheStockData( code_or_stock ):
	code=0
	if not isinstance(code_or_stock, basestring):
		code=code_or_stock['code']
	df=ts.get_hist_data(code, start='2016-01-21',end='2016-04-07',ktype='D')
	tmpdata = df_to_dic( code, df )
	tmpdata['up'], tmpdata['up_count'], tmpdata['down'], tmpdata['down_count'] = getUpAndDown(tmpdata)
	return tmpdata

#解析json获取头为0/6的股票信息
def getStock_A():
	for json_stock_item_data in stockData:
		if json_stock_item_data["code"][0] == '0' or json_stock_item_data["code"][0] == '6':
			print json_stock_item_data["name"], json_stock_item_data["code"]


#根据每条信息取出up/down
def getUpAndDown( stockData ):
	up_data=0
	down_data=0
	up_count=0
	down_count=0
	for k, v in stockData.items():
		if float(v['p_change']) > 0:
			up_data=up_data+v['p_change']
			up_count=up_count+1
		else:
			down_data=down_data+v['p_change']
			down_count=down_count+1
	return up_data, up_count, down_data, down_count



def foreach_dic( data_dic ):
	for (k, v) in data_dic.items():
		print k, str(v)
	
# def getRS( up, up_count, down, down_count ):
	# up_ratio = up/up_count
	# down_ratio = down/down_count
	# return up_ratio/abs(down_ratio)

def getRS( stockdata ):
	print ">>>> the stockdata is: ", stockdata
	up=stockdata['up']
	up_count=stockdata['up_count']
	down=stockdata['down']
	down_count=stockdata['down_count']
	print ">>> up: ", up, "  up_count: ", up_count, "  down: ", down, "  down_count: ", down_count
	if up_count ==0 and down_count == 0:
		return 0
	up_ratio = up/up_count
	down_ratio = down/down_count
	return up_ratio/abs(down_ratio)

def getRSI( stockdata ):
	rs=getRS(stockdata)
	stockdata['rsi']=100-100/(1+rs)
	print ">>>> rsi:", stockdata['rsi']
	return stockdata

def sortByRsi( lis ):
	return sorted(lis.iteritems(), key=lambda asd:asd[1]['rsi'])
	# list.sort(lambda x,y:cmp(x['rsi'],y['rsi']))

if debug==1:
	#从服务器上获取数据  -> 字典型
	stockData_dic = getNetData()
	for k,v in stockData_dic.items():
		print "getting ...", k, "  code: ", stockData_dic[k]['code'], "  name: ", stockData_dic[k]['name']
		stockData_dic[k]=getTheStockData(stockData_dic[k])
		stockData_dic[k]=getRSI(stockData_dic[k])
	sortStock = sortByRsi(stockData_dic)
	print "\n\n\n>>>>>>>>>>>>>分割线>>>>>>>>>>>>\n\n\n"
	print "type sortStock: ", type(sortStock)
	print "type stockData_dic: ", type(stockData_dic)
	for k, v in sortStock:
		print "code: ", v[0]['code'], " rsi: ", v['rsi']
elif debug==2:
	stockdata = getTheStockData('600988')
	stockdata = getRSI(stockdata)
	for (k, v) in stockdata.items():
		print "k: ", k, ">>>",str(v)
elif debug==3:
	getNetData()


# _list={}
# for index in range(0, 10):
# 	_list[index]={}
# 	_list[index]['name']="xx"+str(index)
# 	_list[index]['rsi']=index
# _listx=sorted(_list.iteritems(), key=lambda asd:asd[1]['rsi'])
# print _listx
# print "type _list", type(_list)
# print "type _listx", type(_listx)



# dic={ 'a':3, 'b':2, 'c':1 }
# dic={}
# for x in xrange(1,3):
# 	dic[x]={}
# 	dic[x]['name']="name"+str(x)
# 	dic[x]['index']=3-x
# dicex=sorted(dic.iteritems(), key=lambda asd:asd[1]['index'], reverse=True)
# print dicex

# # sorted(_list, cmp=lambda x, y:cmp(x['rsi'], y['rsi']))
# for (k, v ) in _list.items():
# 	print str(v)


# dic={}
# dic['a']=3
# dic['b']=2
# dic['c']=1
# dic=sorted(dic.iteritems(), key=lambda asd:asd[0], reverse=False)
# print dic


#	RSI曲线计算
#	N日RS=[A/(A+B)]x100%
#	A--N日内收盘涨幅之和
#	B--N日内收盘跌幅之和(取正值)
#	N日RSI= 100 - 100/(1+RS)



#遍历当前表
# foreach_dic( stockData_dic )


# foreach(data)
# getStock_A()

#Series
# s = Series([1,2,3,'abc'],index=['a','b','c','d'])
# print s.index

#DataFrame
# data = {'state':['Ohino','Ohino','Ohino','Nevada','Nevada'],
#         'year':[2000,2001,2002,2001,2002],
#         'pop':[1.5,1.7,3.6,2.4,2.9]}
# df=DataFrame(data)
# for i, row in enumerate(df.values):
# 	data = df.index[i]
# 	a, b, c = row
# 	print a








