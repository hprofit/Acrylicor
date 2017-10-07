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