while (1) {
	int sensor = getdigsensor(@@PORT@@);
	if (sensor @@SIGN@@ @@DISTANCE@@) break;
}
