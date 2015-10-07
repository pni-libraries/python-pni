import unittest
import numpy
import os

import pni.io.nx.h5 as nx
from pni.io.nx.h5 import nxfield
from pni.io.nx.h5 import deflate_filter
from pni.io.nx.h5 import create_file
from pni.io.nx.h5 import open_file

#implementing test fixture
class creation_test_uint8(unittest.TestCase):
    """
    This test creates a single file as the only artifact. The result for 
    every individual test is written to the same file. This makes 
    investigation in case of errors easier.

    We will test all the inquery properties directly in the creation test. 
    This makes somehow sense and we can spare a single test suite
    """
    _typecode="uint8"
    file_path = os.path.split(__file__)[0]
    file_name = "creation_test_{tc}.nxs".format(tc=_typecode)
    full_path = os.path.join(file_path,file_name)

    @classmethod
    def setUpClass(self):
        """
        Setup the file where all the tests are performed. 
        """
        self.gf = create_file(self.full_path,overwrite=True)
        self.gf.close()

    
    def setUp(self):
        self.gf = open_file(self.full_path,readonly=False)
        self.root = self.gf.root()

    def tearDown(self):
        self.root.close()
        self.gf.close()


    def test_scalar_creation(self):
        f = self.root.create_field("scalar",self._typecode)
        self.assertTrue(f.is_valid)
        self.assertEqual(f.dtype,self._typecode)
        self.assertEqual(f.shape,(1,))
        self.assertEqual(f.size,1)
        self.assertEqual(f.filename,self.full_path)
        self.assertEqual(f.parent.name,"/")
        self.assertEqual(f.path,"/scalar")
        self.assertEqual(f.name,"scalar")

    def test_multidim_creation_without_chunk(self):
        f = self.root.create_field("multidim_without_chunk",
                                   self._typecode,
                                   shape=(0,1024,1024))
        self.assertTrue(f.is_valid)
        self.assertEqual(f.dtype,self._typecode)
        self.assertEqual(f.shape,(0,1024,1024))
        self.assertEqual(f.size,0)
        self.assertEqual(f.filename,self.full_path)
        self.assertEqual(f.parent.name,"/")
        self.assertEqual(f.path,"/multidim_without_chunk")
        self.assertEqual(f.name,"multidim_without_chunk")


    def test_multidim_creation_with_chunk(self):
        f = self.root.create_field("multidim_with_chunk",
                                   self._typecode,
                                   shape=(1,1024,1024),
                                   chunk=[1,1024,1024])
        self.assertTrue(f.is_valid)
        self.assertEqual(f.dtype,self._typecode)
        self.assertEqual(f.shape,(1,1024,1024))
        self.assertEqual(f.size,1024**2)
        self.assertEqual(f.filename,self.full_path)
        self.assertEqual(f.parent.name,"/")
        self.assertEqual(f.path,"/multidim_with_chunk")
        self.assertEqual(f.name,"multidim_with_chunk")

    def test_multidim_creation_without_chunk_and_filter(self):
        comp = deflate_filter()
        comp.rate = 2
        f = self.root.create_field("multidim_without_chunk_with_filter",
                                   self._typecode,
                                   shape=(0,1024,1024),
                                   filter=comp)
        self.assertTrue(f.is_valid)
        self.assertEqual(f.dtype,self._typecode)
        self.assertEqual(f.shape,(0,1024,1024))
        self.assertEqual(f.size, 0)
        self.assertEqual(f.filename,self.full_path)
        self.assertEqual(f.parent.name,"/")
        self.assertEqual(f.path,"/multidim_without_chunk_with_filter")
        self.assertEqual(f.name,"multidim_without_chunk_with_filter")


    def test_multdim_creation_with_chunk_and_filter(self):
        comp = deflate_filter()
        comp.rate = 2
        f = self.root.create_field("multidim_with_chunk_with_filter",
                                   self._typecode,
                                   shape=(0,1024,1024),
                                   chunk=[1,1024,1024],
                                   filter=comp)
        self.assertTrue(f.is_valid)
        self.assertEqual(f.dtype,self._typecode)
        self.assertEqual(f.shape,(0,1024,1024))
        self.assertEqual(f.size,0)
        self.assertEqual(f.filename,self.full_path)
        self.assertEqual(f.parent.name,"/")
        self.assertEqual(f.path,"/multidim_with_chunk_with_filter")
        self.assertEqual(f.name,"multidim_with_chunk_with_filter")


class creation_test_uint16(creation_test_uint8):
    _typecode = "uint16"

class creation_test_uint32(creation_test_uint8):
    _typecode = "uint32"

class creation_test_uint64(creation_test_uint8):
    _typecode = "uint64"

class creation_test_int8(creation_test_uint8):
    _typecode = "int8"

class creation_test_int16(creation_test_uint8):
    _typecode = "int16"

class creation_test_int32(creation_test_uint8):
    _typecode = "int32"

class creation_test_int64(creation_test_uint8):
    _typecode = "int64"

class creation_test_float32(creation_test_uint8):
    _typecode = "float32"

class creation_test_float64(creation_test_uint8):
    _typecode = "float64"

class creation_test_float128(creation_test_uint8):
    _typecode = "float128"

class creation_test_complex32(creation_test_uint8):
    _typecode = "complex32"

class creation_test_complex64(creation_test_uint8):
    _typecode = "complex64"

class creation_test_complex128(creation_test_uint8):
    _typecode = "complex128"

class creation_test_bool(creation_test_uint8):
    _typecode = "bool"

class creation_test_string(creation_test_uint8):
    _typecode = "string"