/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx-python.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the NXFile wrapper template.
 *
 * Created on: Feb 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXFILEWRAPPER_HPP__
#define __NXFILEWRAPPER_HPP__

#include "NXObjectWrapper.hpp"
#include "NXGroupWrapper.hpp"

/*! \brief NXFile wrapper template

This template can be used to create NXFile wrappers.
*/
template<typename FType> class NXFileWrapper:public NXGroupWrapper<FType>
{
    public:
        //==================constructor and destructor=========================
        //! default constructor
        NXFileWrapper():NXGroupWrapper<FType>(){}

        //----------------------------------------------------------------------
        //! copy constructor
        NXFileWrapper(const NXFileWrapper<FType> &o):
            NXGroupWrapper<FType>(o){}

        //----------------------------------------------------------------------
        //! move constructor
        NXFileWrapper(NXFileWrapper<FType> &&f):
            NXGroupWrapper<FType>(std::move(f)){}

        //-----------------------------------------------------------------------
        //! move conversion constructor from wrapped object
        explicit NXFileWrapper(FType &&f):NXGroupWrapper<FType>(std::move(f)){}

        //-----------------------------------------------------------------------
        //! copy conversion constructor from wrapped object
        explicit NXFileWrapper(const FType &f):NXGroupWrapper<FType>(f){}

        //----------------------------------------------------------------------
        //! destructor
        ~NXFileWrapper()
        {
        }

        //=======================assignment operators===========================
        //! move conversion assignment from wrapped object
        NXFileWrapper<FType> &operator=(FType &&f)
        {
            NXGroupWrapper<FType>::operator=(f);
            return *this;
        }

        //-----------------------------------------------------------------------
        //! copy conversion assignment from wrapped object
        NXFileWrapper<FType> &operator=(const FType &f)
        {
            NXGroupWrapper<FType>::operator=(f);
            return *this;
        }

        //------------------------------------------------------------------------
        //! copy assignment
        NXFileWrapper<FType> &operator=(const NXFileWrapper<FType> &f)
        {
            if(this != &f) NXGroupWrapper<FType>::operator=(f);
            return *this;
        }

        //-------------------------------------------------------------------------
        //! move assignment
        NXFileWrapper<FType> &operator=(NXFileWrapper<FType> &&f)
        {
            if(this != &f) NXGroupWrapper<FType>::operator=(std::move(f));
            return *this;
        }
};

//-----------------------------------------------------------------------------
/*! \brief create a file

This template wraps the static create_file method of FType. 
\param n name of the new file
\param ov if true overwrite existing file
\param s split size (feature not implemented yet)
\return new instance of NXFileWrapper
*/
template<typename FType> NXFileWrapper<FType> create_file(const String &n,
        bool ov=true,ssize_t s=0)
{
    NXFileWrapper<FType> file(FType::create_file(n,ov,s));
    return file;
}

//------------------------------------------------------------------------------
/*! \brief open a file

Template wraps the static open_file method of NXFile. 
\param n name of the file
\param ro if true open the file read only
\return new instance of NXFileWrapper
*/
template<typename FType> NXFileWrapper<FType> open_file(const String &n,
        bool ro=false)
{
    return NXFileWrapper<FType>(FType::open_file(n,ro)); 
}

//------------------------------------------------------------------------------
template<typename FType> void wrap_nxfile(const String &class_name)
{
    
    class_<NXFileWrapper<FType>,bases<NXGroupWrapper<FType> > >(class_name.c_str())
        .def(init<>())
        ;

    //need some functions
    def("__create_file",&create_file<FType>);
    def("__open_file",&open_file<FType>);
}

#endif
