#!/usr/bin/python
# -*- coding:utf-8 -*-

import json
import tushare as ts
from pandas import Series,DataFrame
import pandas as pd

debug=2

#定义保存文件的路径
stock_item_path="/Users/lishuaizhe/Documents/knowledge/stock_name.json"

#DataFrame转换为字典型
def df_to_dic( stockData_df ):
	data_dic={}
	for i, data in enumerate(stockData_df.values):
		code, name = data
		data_dic[i]={'code':code, 'name':name}
	return data_dic

#定义函数获取信息
def getNetData():
	# 行业分类
	# df=ts.get_industry_classified()
	# 概念分类
	# df=ts.get_concept_classified()
	#上证50成份股
	stockData_df=ts.get_sz50s()
	#保存股票基础信息到文件
	# df.to_json(stock_item_path,orient='records')
	return df_to_dic(stockData_df)
	


#获取每条股票最近两天的数据
def getTheStockData( code ):
	print "code: ", code
	df=ts.get_hist_data(code, start='2016-3-28',end='2016-3-30')
	print df
	return df_to_dic( df )

#解析json获取头为0/6的股票信息
def getStock_A():
	for json_stock_item_data in stockData:
		if json_stock_item_data["code"][0] == '0' or json_stock_item_data["code"][0] == '6':
			print json_stock_item_data["name"], json_stock_item_data["code"]


#根据每条信息取出up/down
def getUpAndDown( stockData ):
	up_data=0
	down_data=0
	for k, v in stockData.items():
		if float(v['p_change']) > 0:
			up_data=up_data+v['p_change']
		else:
			down_data=down_data+v['p_change']
	return up_data, down_data



def foreach_dic( data_dic ):
	for (k, v) in data_dic.items():
		print k, str(v)

		
if debug==1:
	#从服务器上获取数据  -> 字典型
	stockData_dic = getNetData()
	all_stock_data={}
	for k,v in stockData_dic.items():
		print "getting ...", k
		all_stock_data[k]={}
		all_stock_data[k]['code']=v['code']
		all_stock_data[k]['name']=v['name']
		all_stock_data[k]['data']=getTheStockData(all_stock_data[k]['code'])
		up_data, down_data = getUpAndDown(all_stock_data[k]['data'])
		print up_data, down_data
		print all_stock_data[k]['data']
else:
	getTheStockData('600848')


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








