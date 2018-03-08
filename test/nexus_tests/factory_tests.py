#
# (c) Copyright 2018 DESY 
#
# This file is part of python-pni.
#
# python-pni is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# python-pni is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with python-pni.  If not, see <http://www.gnu.org/licenses/>.
# ===========================================================================
#
# Created on: Feb 19, 2018
#     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
from __future__ import print_function
import unittest
import os
from pni.io import h5cpp
from pni.io.h5cpp.file import AccessFlags
from pni.io import nexus

module_path = os.path.dirname(os.path.abspath(__file__))

class BaseFactoryTest(unittest.TestCase):
    
    filename = os.path.join(module_path,"BaseFactoryTest.nxs")
    
    def setUp(self):
        
        self.file = nexus.create_file(self.filename,AccessFlags.TRUNCATE)
        self.root = self.file.root()
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
        self.root.close()
        self.file.close()
        
    def test_create_entry(self):
        
        entry = nexus.BaseClassFactory.create(parent=self.root,
                                              path=h5cpp.Path("scan_1"),
                                              base_class="NXentry")
        self.assertEqual(entry.type,h5cpp.node.Type.GROUP)
        self.assertTrue(entry.attributes.exists("NX_class"))
        self.assertEqual(entry.attributes["NX_class"].read(),"NXentry")
        
class FieldFactoryTest(unittest.TestCase):
    
    filename = os.path.join(module_path,"FieldFactoryTest.nxs")
    
    def setUp(self):
        
        self.file = nexus.create_file(self.filename,AccessFlags.TRUNCATE)
        self.root = self.file.root()
        
    def tearDown(self):
        
        self.root.close()
        self.file.close()
        
    def test_simple_scalar_field(self):
        
        field = nexus.FieldFactory.create(parent=self.root,
                                          path=h5cpp.Path("temperature"),
                                          type=h5cpp.datatype.kFloat32,
                                          space=h5cpp.dataspace.Scalar())
        
        self.assertEqual(field.dataspace.type,h5cpp.dataspace.Type.SCALAR)
        self.assertEqual(field.link.path.name,"temperature")
        self.assertEqual(field.datatype,h5cpp.datatype.kFloat32)
    
    def test_chunked_field(self):
        
        space = h5cpp.dataspace.Simple((0,1024),(h5cpp.dataspace.UNLIMITED,1024))
        field = nexus.FieldFactory.create_chunked(parent=self.root,
                                                  path=h5cpp.Path("mca"),
                                                  type=h5cpp.datatype.kUInt32,
                                                  space=space,
                                                  chunk=(1,1024))
        
        self.assertEqual(field.creation_list.layout,h5cpp.property.DatasetLayout.CHUNKED)
        
        