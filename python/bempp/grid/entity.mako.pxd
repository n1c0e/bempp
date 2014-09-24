<%
codims = [('0','codim_zero'),('1','codim_one'),('2','codim_two')]
%>
from bempp.utils cimport unique_ptr
from bempp.grid.geometry cimport Geometry, c_Geometry
from bempp.grid.codim_template cimport codim_zero,codim_one,codim_two


cdef extern from "bempp/grid/entity.hpp" namespace "Bempp":
    cdef cppclass c_Entity "Bempp::Entity"[codim]:
        size_t level() const
        const c_Geometry& geometry() const

% for (codim,codim_template) in codims:

cdef class Entity${codim}:
   cdef const c_Entity[${codim_template}] * impl_
   cpdef size_t level(self)
   cpdef Geometry _geometry(self)

% endfor
