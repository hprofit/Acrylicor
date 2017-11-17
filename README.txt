Full feature list can be found in Acrylicor_Feature_List.xlsx

The game engine itself can be utilized via the AcrylicorAPI. 
A system to add extensions to the engine is in the works.


Testing the Math Libraries:
acrylicor {testFlags}

testFlags : 
	-a: Run all tests
	-v: Run all Vector related tests
		-v2: Run all Vector2D tests
		-v3: Run all Vector3D tests
	-m: Run all Matrix related tests
		-m2: Run all Matrix2x2 tests
		-m3: Run all Matrix3x3 tests
	-s: Run all Static Collision tests