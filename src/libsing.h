#ifndef LIBSING_H
#define LIBSING_H

#if 1
// HACK: Workaround #1 for version of GAP before 2011-11-16:
// ensure USE_GMP is defined
#define USE_GMP 1
#endif

#include <src/compiled.h>

//////////////////////////////////////////////////////////////////////////////
/**
@file libsing.h
This C header file file contains all of declarations for C++ functions that 
are to be called from C, or vice-versa.
**/
//////////////////////////////////////////////////////////////////////////////

extern Obj SingularTypes;    /* A kernel copy of a plain list of types */
extern Obj SingularRings;    /* A kernel copy of a plain list of rings */
extern Obj SingularElCounts; /* A kernel copy of a plain list of ref counts */
extern Obj SingularErrors;   /* A kernel copy of a string */
extern Obj SingularProxiesType;   /* A kernel copy of the type of proxy els */

//////////////// Layout of the T_SINGULAR objects /////////////////////
// 3 words: 
// First is the GAP type as a small integer pointing into a plain list
// Second is a pointer to a C++ singular object
// The third is an index into the list of all singular rings and the
// corresponding reference counting list.

inline UInt TYPE_SINGOBJ( Obj obj ) { return (UInt) ADDR_OBJ(obj)[0]; }
inline void SET_TYPE_SINGOBJ( Obj obj, UInt val )
{ ADDR_OBJ(obj)[0] = (Obj) val; }
inline void *CXX_SINGOBJ( Obj obj ) { return (void *) ADDR_OBJ(obj)[1]; }
inline void SET_CXX_SINGOBJ( Obj obj, void *val )
{ ADDR_OBJ(obj)[1] = (Obj) val; }
inline UInt RING_SINGOBJ( Obj obj ) { return (UInt) ADDR_OBJ(obj)[2]; }
inline void SET_RING_SINGOBJ( Obj obj, UInt val )
{ ADDR_OBJ(obj)[2] = (Obj) val; }

inline void INC_REFCOUNT( UInt ring )
{
    Int count = INT_INTOBJ(ELM_PLIST(SingularElCounts,ring));
    count++;
    SET_ELM_PLIST(SingularElCounts,ring,INTOBJ_INT(count));
}

inline void DEC_REFCOUNT( UInt ring )
{
    Int count = INT_INTOBJ(ELM_PLIST(SingularElCounts,ring));
    count--;
    SET_ELM_PLIST(SingularElCounts,ring,INTOBJ_INT(count));
}

static inline Obj NEW_SINGOBJ(UInt type, void *cxx)
{
    Obj tmp = NewBag(T_SINGULAR, 2*sizeof(Obj));
    SET_TYPE_SINGOBJ(tmp,type);
    SET_CXX_SINGOBJ(tmp,cxx);
    return tmp;
}

static inline Obj NEW_SINGOBJ_RING(UInt type, void *cxx, UInt ring)
{
    Obj tmp = NewBag(T_SINGULAR, 3*sizeof(Obj));
    SET_TYPE_SINGOBJ(tmp,type);
    SET_CXX_SINGOBJ(tmp,cxx);
    SET_RING_SINGOBJ(tmp,ring);
    INC_REFCOUNT(ring);
    return tmp;
}

static inline Obj NEW_SINGOBJ_RING_PROXY(UInt type, void *cxx, UInt ring, Obj ind)
{
    Obj tmp = NewBag(T_SINGULAR, 4*sizeof(Obj));
    SET_TYPE_SINGOBJ(tmp,type);
    SET_CXX_SINGOBJ(tmp,cxx);
    SET_RING_SINGOBJ(tmp,ring);
    INC_REFCOUNT(ring);
    return tmp;
}
#define SINGTYPE_BIGINT         1
#define SINGTYPE_DEF            2 
#define SINGTYPE_IDEAL          3 
#define SINGTYPE_INT            4 
#define SINGTYPE_INTMAT         5 
#define SINGTYPE_INTVEC         6 
#define SINGTYPE_LINK           7 
#define SINGTYPE_LIST           8 
#define SINGTYPE_MAP            9 
#define SINGTYPE_MATRIX        10 
#define SINGTYPE_MODULE        11 
#define SINGTYPE_NUMBER        12 
#define SINGTYPE_PACKAGE       13 
#define SINGTYPE_POLY          14 
#define SINGTYPE_PROC          15 
#define SINGTYPE_QRING         16 
#define SINGTYPE_RESOLUTION    17 
#define SINGTYPE_RING          18 
#define SINGTYPE_STRING        19 
#define SINGTYPE_VECTOR        20 
#define SINGTYPE_USERDEF       21 
#define SINGTYPE_PYOBJECT      22 

#define SINGTYPE_LASTNUMBER    22

/* If you change these numbers, then also adjust the table TypeTable
 * in cxxfuncs.cc! */

#if 0
proxies fuer:
  ideal   ->  poly
  list    ->  ?
  matrix  ->  poly
  module  ->  vector
  qring   ->  ideal
#endif

inline int ISSINGOBJ(int typ, Obj obj)
{
    return TNUM_OBJ(obj) == T_SINGULAR && TYPE_SINGOBJ(obj) == typ;
}


//////////////// C++ functions to be called from C ////////////////////


void SingularObjMarkFunc(Bag o);
void SingularFreeFunc(Obj o);
Obj TypeSingularObj(Obj o);
Obj FuncSingularRingWithoutOrdering(Obj self, Obj charact, Obj names);
Obj FuncIndeterminatesOfSingularRing(Obj self, Obj r);
Obj FuncSI_MONOMIAL(Obj self, Obj rr, Obj coeff, Obj exps);
Obj FuncSI_STRING_POLY(Obj self, Obj po);
Obj FuncSI_COPY_POLY(Obj self, Obj po);
Obj FuncSI_ADD_POLYS(Obj self, Obj a, Obj b);
Obj FuncSI_NEG_POLY(Obj self, Obj a);
Obj FuncSI_MULT_POLYS(Obj self, Obj a, Obj b);
Obj FuncSI_MULT_POLY_NUMBER(Obj self, Obj a, Obj b);
Obj FuncSI_INIT_INTERPRETER(Obj self, Obj path);
Obj FuncSI_EVALUATE(Obj self, Obj st);
Obj FuncValueOfSingularVar(Obj self, Obj name);
Obj FuncLastSingularOutput(Obj self);
Obj FuncSI_bigint(Obj self, Obj nr);
Obj FuncSI_Intbigint(Obj self, Obj b);
Obj FuncSI_intvec(Obj self, Obj l);
Obj FuncSI_Plistintvec(Obj self, Obj iv);
Obj FuncSI_intmat(Obj self, Obj m);
Obj FuncSI_Matintmat(Obj self, Obj im);
Obj FuncSI_ideal(Obj self, Obj l);


//////////////// C functions to be called from C++ ////////////////////

void PrintGAPError(const char* message);

#endif //#define LIBSING_H

