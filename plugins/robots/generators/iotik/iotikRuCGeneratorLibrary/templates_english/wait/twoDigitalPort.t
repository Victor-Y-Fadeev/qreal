while (!(getdigsensor(@@DRIVER@@, { @@PORT@@, @@PORT_2@@ }) @@SIGN@@ @@VALUE@@)) {
	t_sleep(10);
}
