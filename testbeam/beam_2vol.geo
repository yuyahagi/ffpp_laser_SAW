// Gmsh geometry for a 3D beam with two volumes

a = 5;
L1 = 20;	// Height of the 1st block in the substrate
L2 = 20;	// Height of the 2nd block in the substrate
lc = 1;

// ------------------------------------------------------------------------
// Points
// ------------------------------------------------------------------------
// Elliptic cylinder
Point(1) = {0, 0, 0, lc};
Point(2) = {0, a, 0, lc};
Point(3) = {0, a, a, lc};
Point(4) = {0, 0, a, lc};
Point(5) = {L1, 0, 0, lc};
Point(6) = {L1, a, 0, lc};
Point(7) = {L1, a, a, lc};
Point(8) = {L1, 0, a, lc};
Point(9)  = {L1+L2, 0, 0, lc};
Point(10) = {L1+L2, a, 0, lc};
Point(11) = {L1+L2, a, a, lc};
Point(12) = {L1+L2, 0, a, lc};

// ------------------------------------------------------------------------
// Lines
// ------------------------------------------------------------------------
Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};
Line(5) = {5, 6};
Line(6) = {6, 7};
Line(7) = {7, 8};
Line(8) = {8, 5};
Line(9)  = {9, 10};
Line(10) = {10, 11};
Line(11) = {11, 12};
Line(12) = {12, 9};

Line(13) = {1, 5};
Line(14) = {2, 6};
Line(15) = {3, 7};
Line(16) = {4, 8};
Line(17) = {5, 9};
Line(18) = {6, 10};
Line(19) = {7, 11};
Line(20) = {8, 12};

// ------------------------------------------------------------------------
// Surfaces
// ------------------------------------------------------------------------
Line Loop(1) = {1, 2, 3, 4};
Line Loop(2) = {5, 6, 7, 8};
Line Loop(3) = {9, 10, 11, 12};

Line Loop(4) = {1, 14, -5, -13};
Line Loop(5) = {2, 15, -6, -14};
Line Loop(6) = {3, 16, -7, -15};
Line Loop(7) = {4, 13, -8, -16};

Line Loop(8)  = {5, 18, -9, -17};
Line Loop(9)  = {6, 19, -10, -18};
Line Loop(10) = {7, 20, -11, -19};
Line Loop(11) = {8, 17, -12, -20};

Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Plane Surface(6) = {6};
Plane Surface(7) = {7};
Plane Surface(8) = {8};
Plane Surface(9) = {9};
Plane Surface(10) = {10};
Plane Surface(11) = {11};

// ------------------------------------------------------------------------
// Volumes
// ------------------------------------------------------------------------
Surface Loop(1) = {1, 4, 5, 6, 7, 2};
Surface Loop(2) = {2, 8, 9, 10, 11, 3};
Volume(1) = {1};
Volume(2) = {2};

// ------------------------------------------------------------------------
// Physical groups
// ------------------------------------------------------------------------
Physical Surface(1) = {1};
Physical Surface(2) = {2};
Physical Surface(3) = {3};
Physical Surface(4) = {4};
Physical Surface(5) = {5};
Physical Surface(6) = {6};
Physical Surface(7) = {7};
Physical Surface(8) = {8};
Physical Surface(9) = {9};
Physical Surface(10) = {10};
Physical Surface(11) = {11};

Physical Volume(1) = {1};
Physical Volume(2) = {2};
