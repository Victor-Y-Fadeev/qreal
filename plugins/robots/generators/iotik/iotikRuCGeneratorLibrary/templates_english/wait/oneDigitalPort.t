while (!(getdigsensor(@@DRIVER@@, { @@PORT@@ }) @@SIGN@@ @@VALUE@@)) {
	t_sleep(10);
}
