#!/usr/bin/env python 

import sys
import numpy

sys.path.append("lib/python")

import pni.nx.h5 as nx


f = nx.create_file("test2.h5",True,0)

field = f.create_field("data","uint16")
print field.shape
field.write(17)
print field.read()
field = f.create_field("data2","float32",[10,2])
field.attr("unit","string").value = "m/s"
field.attr("temperature","float32").value = 12.3

field = f.create_field("data3","complex128",[10,3],[10,1])
a = numpy.zeros(field.shape,dtype=field.type_id)
a[...] = 1.421e-1+34.2334j
field.write(a)
print "read from ellipsis"
print field[0,...]
print field[...,1]
print field[...]
print field[1:5,:]
print field[:,0]
print field[0,1]
print field.read()

print "try write selections"
field = f.create_field("data4","float32",[4,5])
a = numpy.zeros(field.shape,dtype=field.type_id)
field.write(a)
print field[...]
field[1,1] = 2
print field[...]
print field[100]

field2 = f.open("data2")
field2.attr("description","string").value = "a stupid data field"


f.close();
