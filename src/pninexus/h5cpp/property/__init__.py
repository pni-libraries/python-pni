#
# import enumerations
#

from pninexus.h5cpp._property import DatasetFillValueStatus
from pninexus.h5cpp._property import DatasetFillTime
from pninexus.h5cpp._property import DatasetAllocTime
from pninexus.h5cpp._property import DatasetLayout
from pninexus.h5cpp._property import LibVersion
from pninexus.h5cpp._property import CopyFlag

def CopyFlag_or(self,b):
    if isinstance(b,(CopyFlag,CopyFlags)):
        return CopyFlags(self) | b
    else:
        raise TypeError("RHS of | operator must be a CopyFlag instance!")
    
CopyFlag.__or__ = CopyFlag_or

#
# import utility classes
#
from pninexus.h5cpp._property import CopyFlags
from pninexus.h5cpp._property import ChunkCacheParameters
from pninexus.h5cpp._property import CreationOrder

#
# import propety list classes
#
from pninexus.h5cpp._property import List
from pninexus.h5cpp._property import DatasetTransferList
from pninexus.h5cpp._property import FileAccessList
from pninexus.h5cpp._property import FileCreationList
from pninexus.h5cpp._property import FileMountList
from pninexus.h5cpp._property import LinkAccessList
from pninexus.h5cpp._property import ObjectCopyList
from pninexus.h5cpp._property import ObjectCreationList
from pninexus.h5cpp._property import StringCreationList
from pninexus.h5cpp._property import DatasetAccessList
from pninexus.h5cpp._property import DatatypeAccessList
from pninexus.h5cpp._property import GroupAccessList
from pninexus.h5cpp._property import DatasetCreationList
from pninexus.h5cpp._property import GroupCreationList
from pninexus.h5cpp._property import TypeCreationList
from pninexus.h5cpp._property import AttributeCreationList
from pninexus.h5cpp._property import LinkCreationList