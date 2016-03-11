//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of python-pnicore.
//
// python-pnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// python-pnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with python-pnicore.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Aug 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/python.hpp>
#include <boost/python/docstring_options.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath.hpp>
#include "../errors.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using namespace boost::python;

class nxpath_iterator
{
    public:
        typedef nxpath::const_iterator iterator_type;
    private:
        iterator_type _begin;
        iterator_type _end;
    public:
        nxpath_iterator():
            _begin(),
            _end()
        {}

        nxpath_iterator(const iterator_type &b,
                        const iterator_type &e):
            _begin(b),
            _end(e)
        {}

        void increment()
        {
            _begin++;
        }

        object __iter__() const
        {
            return object(nxpath_iterator(_begin,_end));
        }

        object next() 
        {
            if(_begin==_end)
            {
                throw(nxpath_iterator_stop());
                return object();
            }
            
            auto o = *_begin;
            increment();
            return object(o);
        }
};

nxpath_iterator get_iterator(const nxpath &p)
{
    return nxpath_iterator(p.begin(),p.end());
}

static const char *nxpath_attribute_doc = 
"Property setting and getting an attribute name\n"
"\n"
"This read/write property allows to set the attribute section of a NeXus"
" path.\n"
"\n"
".. code-block:: python\n"
"\n"
"    path = make_path(\"/:NXentry/:NXinstrument/NXdetector/data\")\n"
"    print(path)\n"
"    #output /:NXentry/:NXinstrument/NXdetector/data\n"
"    path.attribute = \"units\"\n"
"    print(path)\n"
"    #output /:NXentry/:NXinstrument/:NXdetector/data@units\n";

static const char *nxpath_front_doc = 
"Property returning the first element in the path\n"
"\n"
".. code-block:: python\n"
"\n"
"    p = make_path(\"/:NXentry/:NXinstrument/:NXdetector/data\")\n"
"    print(p.front)\n"
"    #output {'name':'/','base_class':'NXroot'}\n";

static const char *nxpath_back_doc = 
"Property returning the last element in the path\n"
"\n"
".. code-block:: python\n"
"\n"
"    p = make_path(\"/:NXentry/:NXinstrument/:NXdetector/data\")\n"
"    print(p.back)\n"
"    #output {'name':'data','base_class':''}\n";

static const char *nxpath_size_doc = 
"Property returning the size of the path\n"
"\n"
"The size of a path is the number of elements in the object section. "
"In other words the number of elements without the optional filename "
"and attribute.\n";


static const char* make_path_doc = 
"Create a path object from a string\n"
"\n"
"Create a new path object from its string representation.\n"
"\n"
":param str path_str: string representation of the path\n"
":return: new path object\n"
":rtype: instance of :py:class:`nxpath`\n";

static const char *nxpath_filename_doc = 
"Property to set and get the filename section of the path\n"
"\n"
"This read/write property can be used to set the filename section of a NeXus"
" path.\n"
"\n"
".. code-block:: python\n"
"\n"
"    p =  make_path(\"/:NXentry/:NXinstrument/:NXdetector/data\")\n"
"    print(p)\n"
"    #output /:NXentry/:NXinstrument/:NXdetector/data\n"
"    p.filename = \"test.nxs\"\n"
"    print(p)\n"
"    #output test.nxs://:NXentry/:NXinstrument/:NXdetector/data\n";


static const char *is_root_element_doc = 
"Checks if an element is the root element \n"
"\n"
"Returns true if the element passed as the argument is the root element of \n"
"the NeXus tree. This is the case if the element dictionary has a key \n"
"*name* of with value '/' and a key *base_class* with value 'NXroot'.\n"
"\n"
":param dict path_element: the element dictionary\n"
":return: true if the element describes the root element\n"
":rtype: bool\n";

static const char *has_name_doc = 
"True if the element has a name \n"
"\n"
"Returns true if the element dictionary passed has a non-empty *name* key.\n"
"\n"
":param dict path_element: the path element to check\n"
":return: true if the *name* key has a non-empty string value\n"
":rtype: bool\n";

static const char *has_class_doc = 
"True if the element has a non-empty class\n"
"\n"
"Returns true if the element dictionary passed has a non-emtpy *base_class*\n"
" key.\n"
"\n"
":param dict path_element: the path element to check\n"
":return: true if the *base_class* key has a non-empty string value\n"
":rtype: bool\n";

static const char *is_empty_doc = 
"True if the path is empty\n"
"\n"
"An instance of :py:class:`nxpath` is considered empty if \n"
"* it has no file-section\n"
"* no attribute section\n"
"* and no object section\n"
"\n"
"If all this conditions are holding this function will return true.\n"
"\n"
":param nxpath path: the path to check\n"
":return: true if the path is empty, false otherwise\n"
":rtype: bool\n";

static const char *is_absolute_doc  = 
"Returns true if the path is absolute\n"
"\n"
"If the first element in the object section is the root element the path is \n"
"is considered to be absolute. \n"
"\n"
":param nxpath path: path to check for absolutness\n"
":return: true if the path is absolut, false otherwise\n"
":rtype: bool\n";


void wrap_nxpath()
{
    docstring_options doc_options(true,true);
    //------------------iterator wrapper--------------------------------------
    class_<nxpath_iterator>("nxpath_iterator")
        .def("increment",&nxpath_iterator::increment)
        .def("__iter__",&nxpath_iterator::__iter__)
#if PY_MAJOR_VERSION >= 3
        .def("__next__",&nxpath_iterator::next);
#else
        .def("next",&nxpath_iterator::next);
#endif

    //-------------------nxpath wrapper---------------------------------------
    void (nxpath::*set_filename)(const string &) = &nxpath::filename;
    string (nxpath::*get_filename)()const = &nxpath::filename;
    void (nxpath::*set_attribute)(const string &) = &nxpath::attribute;
    string (nxpath::*get_attribute)() const = &nxpath::attribute;
    class_<nxpath>("nxpath")
        .add_property("front",&nxpath::front,nxpath_front_doc)
        .add_property("back",&nxpath::back,nxpath_back_doc)
        .add_property("size",&nxpath::size,nxpath_size_doc)
        .add_property("filename",get_filename,set_filename,nxpath_filename_doc)
        .add_property("attribute",get_attribute,set_attribute,nxpath_attribute_doc)
        .def("_push_back",&nxpath::push_back)
        .def("_push_front",&nxpath::push_front)
        .def("_pop_back",&nxpath::pop_back)
        .def("_pop_front",&nxpath::pop_front)
        .def("__str__",&nxpath::to_string)
        .def("__len__",&nxpath::size)
        .def("__iter__",&get_iterator);


    def("make_path",nxpath::from_string,make_path_doc,args("path_str"));

    bool (*nxpath_match_str_str)(const string &,const string &) = &match;
    bool (*nxpath_match_path_path)(const nxpath &,const nxpath &) = &match;
    def("match",nxpath_match_str_str);
    def("match",nxpath_match_path_path);
    def("join",&join);

    def("is_root_element",&is_root_element,is_root_element_doc,args("path_element"));
    def("is_absolute",&is_absolute,is_absolute_doc,args("path"));
    def("is_empty",&is_empty,is_empty_doc,args("path"));
    def("has_name",&has_name,has_name_doc,args("path_element"));
    def("has_class",&has_class,has_class_doc,args("path_element"));

    nxpath (*nxpath_make_relative_str_str)(const string &,const string &) = 
        &make_relative;
    def("make_relative_",nxpath_make_relative_str_str);
}

