##load objects from the pninx python C++ module

from ._nx import nxpath
from ._nx import make_path
from ._nx import match as _match
from ._nx import is_root_element
from ._nx import is_absolute
from ._nx import is_empty
from ._nx import has_name
from ._nx import has_class
from ._nx import join
from ._nx import make_relative_

#=============================================================================
def get_name_and_base_class(*args):
    
    if len(args) == 1:
        (name,base_class) = args[0].split(":")
    else:
        name = args[0]
        base_class = args[1]

    return (name,base_class)

#=============================================================================
def get_name_and_base_class_from_args(*args,**kwargs):

    if len(args)==1 and not len(kwargs):
        if args[0][0] == ':':
            return ("",args[0][1:])
        elif args[0].find(':') < 0:
            return (args[0],"")
        else:
            return(args[0].split(":"))
    elif len(args) == 2 and not len(kwargs):
        return (args[0],args[1])
    elif not len(args) and len(kwargs) == 2:
        if "name" in kwargs.keys() and "base_class" in kwargs.keys():
            return (kwargs["name"],kwargs["base_class"])
        else:
            raise KeyError("Wrong keyword arguments: must be 'name' and 'base_class'!")
    else:
        raise SyntaxError("Wrong number of positional or keyword arguments!")


#=============================================================================
def _nxpath_push_back(self,*args,**kwargs):
    """Append element to the end of the object section
   
    This method takes either two positional arguments

    .. code-block:: python
        
        path.push_back("entry","NXentry")

    Where the first one is the *name* and the optional second argument 
    the *base class* of the path element. 

    Alternatively there are two keyword arguments 

    .. code-block:: python

        path.push_back(name="entry",base_class="NXentry")

    which would have the same effect. Finally one can also use a single string 
    to describe a new element

    .. code-block:: python

        path.push_back("entry:NXentry")
        path.push_back(":NXinstrument")

    It must be noted that only a single element can be appended with 
    :py:meth:`push_back`.
    """

    (name,base_class) = get_name_and_base_class_from_args(*args,**kwargs)
    self._push_back({"name":name,"base_class":base_class})

#=============================================================================
def _nxpath_push_front(self,*args,**kwargs):
    """Prepends an element to a path

    This method works like :py:meth:`push_back` but prepends an element 
    in front of the first one. The arguments work the same as for 
    :py:meth:`push_back`.

    """

    (name,base_class) = get_name_and_base_class_from_args(*args,**kwargs)

    self._push_front({"name":name,"base_class":base_class})

#=============================================================================
def _nxpath_pop_front(self):
    """Remove first element from the object section of the path
    
    """
    if not len(self):
        raise IndexError("Object section of path is empty!")

    self._pop_front()

#=============================================================================
def _nxpath_pop_back(self):
    """Remove last element from the object section
    
    """
    if not len(self): 
        raise IndexError("Object section of path is empty!")

    self._pop_back()

#=============================================================================
def _nxpath_add__(self,arg):

    if isinstance(arg,nxpath):
        return join(self,arg)
    elif isinstance(arg,str):
        return join(self,make_path(arg))
    else:
        raise TypeError("Argument must be a string or an nxpath!")

#=============================================================================
def _nxpath_radd__(self,arg):

    if isinstance(arg,nxpath):
        return join(self,arg)
    elif isinstance(arg,str):
        return join(make_path(arg),self)
    else:
        raise TypeError("Argument must be a string or an nxpath!")

nxpath.push_back = _nxpath_push_back
nxpath.push_front = _nxpath_push_front
nxpath.pop_front = _nxpath_pop_front
nxpath.pop_back  = _nxpath_pop_back
nxpath.__add__ = _nxpath_add__
nxpath.__iadd__ = _nxpath_add__
nxpath.__radd__ = _nxpath_radd__

def make_relative(parent,old):
    """Create a relative path

    Makes the path old a relative path to parent. For this function to succeed
    both paths must satisfy two conditions

    * old must be longer than parent
    * both must be absolut paths
    
    If any of these conditions is not satisfied a :py:class:`ValueError`
    exception will be thrown.

    .. code-block:: python

        parent = "/:NXentry/:NXinstrument"
        old    = "/:NXentry/:NXinstrument/:NXdetector/data"

        rel_path = make_relative(parent,old)
        print(rel_path)
        #output: :NXdetector/data

    :param str parent: the new root path 
    :param str old:  the original path which should be made relative to old
    :return: path refering to the same object as old but relative to parent
    :rtype: str
    :raises ValueError: old and parent do not satifisy the above conditions
    """

    return make_relative_(parent,old).__str__()

def match(a,b):
    """
    compute a path match
    """
    
    if(isinstance(a,str)):
        a = make_path(a)
        
    if(isinstance(b,str)):
        b = make_path(b)
        
    return _match(a,b)
