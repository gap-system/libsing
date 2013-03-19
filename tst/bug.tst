gap> #
gap> # A collection of tests that use to produce errors crashes
gap> #
gap> s := SI_ring(0,["a","b","c"]);
<singular ring>
gap> m := SI_matrix(s,4,3,"1,0,4,2,0,5,0,0,0,3,0,6");
<singular matrix (mutable):
1,0,4,
2,0,5,
0,0,0,
3,0,6 >
gap> SI_syz(m);
<singular module (mutable):
0,
1,
0 >
gap> r := SI_ring(3,["a","b"]);
<singular ring>
gap> x := SI_poly(r,SI_bigint(2));
<singular poly (mutable):-1>
gap> 
gap> #
gap> # The following used to segfault, due to bugs in SingObj::cleanup
gap> #
gap> SI_\+(3^60, []);
Error, Argument to Singular call is no valid Singular object
gap> 
gap> #
gap> # Former segfault due to insufficient arg checking
gap> #
gap> R := SI_ring( 0, [ "x" ] );
<singular ring>
gap> M := SI_matrix( R, 2, 2, "0" );
<singular matrix (mutable):
0,0,
0,0 >
gap> f := function( M ) SI_\[(M,1,1,SI_poly(R,"1")); end;;
gap> f(M);
Error, incorrect number of arguments
gap> 
gap> r := SI_ring(0,["x","y","z"],[["lp",3]]);
<singular ring>
gap> SI_ringlist(r);
<singular list (mutable):
[1]:
   0
[2]:
   [1]:
      x
   [2]:
      y
   [3]:
      z
[3]:
   [1]:
      [1]:
         lp
      [2]:
         1,1,1
   [2]:
      [1]:
         c
      [2]:
         0
[4]:
   _[1]=0>
