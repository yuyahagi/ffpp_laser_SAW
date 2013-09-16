// Gmsh project created on Wed Aug  7 12:26:40 2013

h = 30;	// Height of the elliptic cylinder
a = 37.5;
b = 75;
p = 212.13;	// period
lc1 = 10;
lc2 = 100;
L1 = 2000;	// Height of the 1st block in the substrate
L2 = 10000;	// Height of the 2nd block in the substrate

// ------------------------------------------------------------------------
// Points
// ------------------------------------------------------------------------
// Elliptic cylinder
Point(1) = {0, 0, 0, lc1};
Point(2) = {a, 0, 0, lc1};
Point(3) = {0, b, 0, lc1};
Point(4) = {-a, 0, 0, lc1};
Point(5) = {0, -b, 0, lc1};
Point(6) = {0, 0, h, lc1};
Point(7) = {a, 0, h, lc1};
Point(8) = {0, b, h, lc1};
Point(9) = {-a, 0, h, lc1};
Point(10) = {0, -b, h, lc1};

// Substrate top
Point(11) = {p/2, p/2, 0, lc1};
Point(12) = {-p/2, p/2, 0, lc1};
Point(13) = {-p/2, -p/2, 0, lc1};
Point(14) = {p/2, -p/2, 0, lc1};

// Substrate middle
Point(15) = {p/2, p/2, -L1, lc2};
Point(16) = {-p/2, p/2, -L1, lc2};
Point(17) = {-p/2, -p/2, -L1, lc2};
Point(18) = {p/2, -p/2, -L1, lc2};

// Substrate bottom
Point(19) = {p/2, p/2, -L1-L2, lc2};
Point(20) = {-p/2, p/2, -L1-L2, lc2};
Point(21) = {-p/2, -p/2, -L1-L2, lc2};
Point(22) = {p/2, -p/2, -L1-L2, lc2};

// ------------------------------------------------------------------------
// Lines
// ------------------------------------------------------------------------
// Elliptic cylinder
Ellipse(1) = {2, 1, 2, 3};
Ellipse(2) = {3, 1, 4, 4};
Ellipse(3) = {4, 1, 4, 5};
Ellipse(4) = {5, 1, 2, 2};
Ellipse(5) = {7, 6, 7, 8};
Ellipse(6) = {8, 6, 9, 9};
Ellipse(7) = {9, 6, 9, 10};
Ellipse(8) = {10, 6, 7, 7};
Line(9) = {2, 7};
Line(10) = {3, 8};
Line(11) = {4, 9};
Line(12) = {5, 10};

// Substrate top
Line(13) = {11, 12};
Line(14) = {12, 13};
Line(15) = {13, 14};
Line(16) = {14, 11};

// Substrate middle
Line(17) = {15, 16};
Line(18) = {16, 17};
Line(19) = {17, 18};
Line(20) = {18, 15};

// Substrate bottom
Line(21) = {19, 20};
Line(22) = {20, 21};
Line(23) = {21, 22};
Line(24) = {22, 19};

// Substrate vertical lines (top-middle)
Line(25) = {11, 15};
Line(26) = {12, 16};
Line(27) = {13, 17};
Line(28) = {14, 18};

// Substrate vertical lines (middle-bottom)
Line(29) = {15, 19};
Line(30) = {16, 20};
Line(31) = {17, 21};
Line(32) = {18, 22};

// ------------------------------------------------------------------------
// Surfaces
// ------------------------------------------------------------------------
Line Loop(33) = {5, 6, 7, 8};
Plane Surface(34) = {33};	// Elliptic cylinder top
Line Loop(35) = {1, 2, 3, 4};
Plane Surface(36) = {35};	// Elliptic cylinder bottom
Line Loop(37) = {9, 5, -10, -1};
Ruled Surface(38) = {37};	// Elliptic cylinder sides
Line Loop(39) = {10, 6, -11, -2};
Ruled Surface(40) = {39};
Line Loop(41) = {11, 7, -12, -3};
Ruled Surface(42) = {41};
Line Loop(43) = {12, 8, -9, -4};
Ruled Surface(44) = {43};

Line Loop(45) = {13, 14, 15, 16};
Plane Surface(46) = {35, 45};	// Substrate top (with a hole)
Line Loop(47) = {17, 18, 19, 20};
Plane Surface(48) = {47};	// Substrate middle layer
Line Loop(49) = {21, 22, 23, 24};
Plane Surface(50) = {49};	// Substrate bottom
Line Loop(51) = {13, 26, -17, -25};
Plane Surface(52) = {51};	// Substrate back (top-middle)
Line Loop(53) = {14, 27, -18, -26};
Plane Surface(54) = {53};	// Substrate left (top-middle)
Line Loop(55) = {15, 28, -19, -27};
Plane Surface(56) = {55};	// Substrate front (top-middle)
Line Loop(57) = {16, 25, -20, -28};
Plane Surface(58) = {57};	// Substrate right (top-middle)

Line Loop(59) = {17, 30, -21, -29};
Plane Surface(60) = {59};	// Substrate back (middle-bottom)
Line Loop(61) = {18, 31, -22, -30};
Plane Surface(62) = {61};	// Substrate left (middle-bottom)
Line Loop(63) = {19, 32, -23, -31};
Plane Surface(64) = {63};	// Substrate front (middle-bottom)
Line Loop(65) = {20, 29, -24, -32};
Plane Surface(66) = {65};	// Substrate right (middle-bottom)

// Force mesh of the substrate sides to match the opposite side
Periodic Surface(56) {-15, 27, 19, -28} = (52) {13, 26, -17, -25};
Periodic Surface(58) {-16, 28, 20, -25} = (54) {14, 27, -18, -26};
Periodic Surface(64) {-19, 31, 23, -32} = (60) {17, 30, -21, -29};
Periodic Surface(66) {-20, 32, 24, -29} = (62) {18, 31, -22, -30};

// ------------------------------------------------------------------------
// Volumes
// ------------------------------------------------------------------------
Surface Loop(67) = {40, 38, 44, 42, 34, 36};
Volume(68) = {67};	// Elliptic cylinder
Surface Loop(69) = {46, 58, 52, 54, 56, 36, 62, 64, 66, 60, 50};
Volume(70) = {69};	// Substrate (top-middle-bottom)

// ------------------------------------------------------------------------
// Physical groups
// ------------------------------------------------------------------------
Physical Surface(1) = {34};	// Elliptical cylinder top
Physical Surface(2) = {36};	// Elliptical cylinder bottom
Physical Surface(3) = {44, 38, 40, 42};	// Elliptical cylinder side
Physical Surface(4) = {46};	// Substrate top
Physical Surface(5) = {50};	// Substrate bottom
Physical Surface(6) = {52};	// Substrate back
Physical Surface(7) = {54};	// Substrate left
Physical Surface(8) = {56};	// Substrate front
Physical Surface(9) = {58};	// Substrate right

// Surfaces bottom half
Physical Surface(10) = {60};	// Substrate back
Physical Surface(11) = {62};	// Substrate left
Physical Surface(12) = {64};	// Substrate front
Physical Surface(13) = {66};	// Substrate right

// Volumes
Physical Volume(21) = {68};	// Elliptical cylinder
Physical Volume(22) = {70};	// Substrate
