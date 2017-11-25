while (!(getansensor(@@DRIVER@@, @@PORT@@) @@SIGN@@ @@VALUE@@)) {
	t_sleep(10);
}
