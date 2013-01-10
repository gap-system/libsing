gap> #
gap> # A collection of tests that use to produce errors crashes
gap> #
gap> s := SI_ring(0,["a","b","c"]);
<singular ring>
gap> m := SI_matrix(4,3,s,"1,0,4,2,0,5,0,0,0,3,0,6");
<singular object:
1,0,4,
2,0,5,
0,0,0,
3,0,6 >
gap> SI_syz(m);
<singular object:
0,
1,
0 >
gap> r := SI_ring(3,["a","b"]);
<singular ring>
gap> x := SI_poly(r,SI_bigint(2));
<singular poly:-1>