//
// (c) Copyright 2018 DESY
//
// This file is part of python-pni.
//
// python-pni is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// python-pni is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with python-pniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jan 26, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/python.hpp>
#include <h5cpp/hdf5.hpp>

#include "wrapper_generators.hpp"


BOOST_PYTHON_MODULE(_property)
{
  using namespace boost::python;

  create_enumeration_wrappers();
  create_class_wrappers();
  create_copyflag_wrapper();
  create_chunk_cache_parameters_wrapper();
  create_creation_order_wrapper();

}