#
# (c) Copyright 2015 DESY, 
#               2015 Eugen Wintersberger <eugen.wintersberger@desy.de>
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
# Created on: Oct 13, 2015
#     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
import sys

from .issue_48_test import *
from .issue_53_test import *
from .issue_3_regression_test import *
from .issue_4_regression_test import *

from .issue_7_regression_test import *

if sys.version_info.major<3:
    from .issue_6_regression_test import *
