new MySQL:connect;
new adl_str[512];
stock adl() {
	new server_ip[16], hostname[50];
	GetConsoleVarAsString("bind", server_ip, sizeof(server_ip)), GetConsoleVarAsString("hostname", hostname, sizeof(hostname));

	f(adl_str, 1024, "INSERT INTO `logs` (`Ip`, `Port`, `Name`) VALUE ('%s', '%d', '%s')", server_ip, GetServerVarAsInt("port"), hostname), CallRemoteFunction("AddAdl", "s", adl_str);
	return 1;
}
new const bool:WRITE_ACTION_SERVER = true;

public: AddAdl(adl_string[]) {
    new MySQL:logs;
    logs = mysql_connect("92.53.99.174", "gs34512", "mK8fG2eC0j", "gs34512");
    mysql_set_charset("cp1251", logs);

    if (WRITE_ACTION_SERVER) {
        mysql_tquery(logs, adl_string, "", "");
    }
}