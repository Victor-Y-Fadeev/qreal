while (1) {
	int sensor = getansensor(@@PORT@@);
	if (sensor @@SIGN@@ @@DISTANCE@@) break;
}
