
#include<pni/utils/Types.hpp>
#include<pni/utils/Exceptions.hpp>

#include<pni/nx/NX.hpp>

using namespace pni::utils;

/*! \brief field creator class-template

This template generats classes whose instance are responsible for creating
NXField instances. The instance is of type FieldT. 
*/
template<typename FieldT> class FieldCreator{
    private:
        String __n;      //!< name of the field
        Shape __s;       //!< shape of the field
        Shape __cs;      //!< chunk shape of the field
        object __filter; //!< name of the filter to use
    public:
        //---------------------------------------------------------------------
        /*! \brief constructor
       
        The standard constructor for this class.
        \param n name of the field
        \param s shape of the field
        \param cs chunk shape
        \param filter filter object to use for compression
        */
        FieldCreator(const String &n,const Shape &s,const Shape &cs,const object
                &filter):
            __n(n),__s(s),__cs(cs),__filter(filter){}
       
        //---------------------------------------------------------------------
        /*! \brief create field object

        This template emthod finally creates the field object. The datatype to 
        use is determined by the template parameter T. OType is the type of the
        parent object of the field.
        \throws NXFieldError in case of field related problems
        \throws NXFilterError in case of filter related errors
        \param o parent below which the field should be created
        \return instance of a NXField class
        */
        template<typename T,typename OType> 
            FieldT create(const OType &o) const;

        //---------------------------------------------------------------------
        /*! \brief create field using a type string

        This is the method usually used by a client of this class to create an
        instance of an NXField object. The datatype is determined by a string.
        \throws TypeError if the datatype given by the user could no be handled
        \throws NXFieldError if field creation fails
        \throws NXFilterError if the filter object is invalid
        \param o parent object 
        \param type_str string representing the data-type to use
        */
        template<typename OType> 
            FieldT create(const OType &o,const String &type_str) const;
};

//-----------------------------------------------------------------------------
template<typename FieldT>
template<typename T,typename OType> 
    FieldT FieldCreator<FieldT>::create(const OType &o) const
{
    extract<NXDeflateFilter> deflate_obj(__filter);
    if(deflate_obj.check()){
        NXDeflateFilter deflate = deflate_obj();
        if(__cs.rank()==0)
            return FieldT(o.template create_field<T>(__n,__s,deflate));
        else
            return FieldT(o.template create_field<T>(__n,__s,__cs,deflate));
    }else if(__filter.is_none()){
        return FieldT(o.template create_field<T>(__n,__s,__cs));
    }else{
        //raise an exception here
        pni::nx::NXFilterError error;
        error.issuer("template<typename FieldT> template<typename T,"
                "typename OType> FieldT FieldCreator<FieldT>::create(const "
                "OType &o) const");
        error.description("Invalid filter object!");
        throw(error);
    }
}

//------------------------------------------------------------------------------
template<typename FieldT> 
template<typename OType> FieldT 
FieldCreator<FieldT>::create(const OType &o,const String &type_code) const
{
    if(type_code == "uint8") return this->create<UInt8>(o);
    if(type_code == "int8")  return this->create<Int8>(o);
    if(type_code == "uint16") return this->create<UInt16>(o);
    if(type_code == "int16")  return this->create<Int16>(o);
    if(type_code == "uint32") return this->create<UInt32>(o);
    if(type_code == "int32")  return this->create<Int32>(o);
    if(type_code == "uint64") return this->create<UInt64>(o);
    if(type_code == "int64")  return this->create<Int64>(o);

    if(type_code == "float32") return this->create<Float32>(o);
    if(type_code == "float64") return this->create<Float64>(o);
    if(type_code == "float128") return this->create<Float128>(o);
    
    if(type_code == "complex64") return this->create<Complex32>(o);
    if(type_code == "complex128") return this->create<Complex64>(o);
    if(type_code == "complex256") return this->create<Complex128>(o);

    if(type_code == "string") return this->create<String>(o);

    //raise an exception here
    TypeError error;
    error.issuer("template<typename FieldT> template<typename OType> FieldT "
                 "FieldCreator<FieldT>::create(const OType &o,const String &"
                 "type_code) const");
    error.description("Cannot create field with type-code ("+type_code+")!");
    throw(error);
}
