public: VKResponse(index, response_code, data[], playerid)
{
	if !(response_code == 200) *then
		data[0] = EOS;
		
	switch DialogListID[index] do
	{
		case 1:
			return PlayerDialogVK(index);
	}
	switch GetPlayerDialogID(index) do
	{
		case 2,7782:
			return SPDF(index, 7782, DIALOG_STYLE_INPUT, "{BFBBBA}{FFFFFF}����������� | {ae433d}���������", "\n{ffffff}����� ������ ��������� ��� �� ��������\n%s {ffffff}��������� {ae443d}���{ffffff},\n������� ���������� ������ � ������ ����.\n\n{ae443d}����� �������� ���� � ����� � �������,\n����������� ���������� ������: ALT + TAB!\n\n", !"�", !"�", data);
		
		case 7778:
		{
			if GetString(data, "-1") *then
				return SCM(index, 0x4c75a3FF, !"���������:{FFFFFF} ���������� ���� ������������ ��������� ���������� ������ ��������� �� ��������: {ae433d}SAMP: Arizona Role Play"),
						PlayerDialogVK(index, 1);
			
			return SPDF(index, 7779, DIALOG_STYLE_INPUT, "{FFFFFF}���� ���� | {ae433d}���������", "\n{ffffff}����� ������ ��������� ��� �� ��������\n%s ��������� {ae443d}���{ffffff},\n������� ���������� ������ � ������ ����.\n\n{ae443d}����� �������� ���� � ����� � �������,\n����������� ���������� ������: ALT + TAB!\n\n", !"�", !"�", data);
		}
		case 7779:
		{
			sscanf(data, "s[64]d", mysql_string, PI[index][pVkontakte]);
			DeletePVar(index, "Stranicia"), DeletePVar(index, "CodeVK");
			
			for new i; i < strlen(mysql_string); i++ do
			{
				if mysql_string[i] == '|' *then { mysql_string[i] = ' '; break; }
			}
			
			UpdatePlayerDataInt(index, "Vkontakte", PI[index][pVkontakte]);
					
			f(global_str, 600, "\n{FFFFFF}����������:\n- �������: {4c75a3}%s\n{FFFFFF}- �������������: {4c75a3}%d\n\n{FFFFFF}�� {aeFF3d}������� {ffffff}��������� ������� ������� � �������� {4c75a3}���������{ffffff}.\n������ ��� ����������� � {ae443d}IP-������ {ffffff}��������� �� ����,\n� �������� ��� ���������� ��������� {ae443d}�������� {ffffff}����\n��� ����� ��������� {ae443d}��� ��� ������������� �����{ffffff}!\n\n", mysql_string, PI[index][pVkontakte]);
				
			return SPD(index, 0, DIALOG_STYLE_MSGBOX, !"{FFFFFF}�������� | {ae433d}���������", global_str, !"x", !"");
		}
		case 7780:
			return SPDF(index, 7781, DIALOG_STYLE_INPUT, !"{FFFFFF}������� | {ae433d}���������", "\n{ffffff}����� ������ ��������� ��� �� ��������\n%s {ffffff}��������� {ae443d}���{ffffff},\n������� ���������� ������ � ������ ����.\n\n{ae443d}����� �������� ���� � ����� � �������,\n����������� ���������� ������: ALT + TAB!\n\n", !"�", !"�", data);

		case 7781:
		{
			SPDF(index, 0, DIALOG_STYLE_MSGBOX, !"{FFFFFF}������� | {ae433d}���������", "\n{FFFFFF}����������:\n- �������: {4c75a3}%s\n{FFFFFF}- �������������: {4c75a3}%d\n\n{FFFFFF}�� {aeFF3d}������� {ffffff}�������� ������� ������� �� �������� {4c75a3}���������{ffffff}.\n\n��������� ���������� ��� ������ {ae433d}����������:\n{ae433d}- {ffffff}����������� ������������� �����������\n\n", !"x", !"", data, PI[index][pVkontakte]);
			UpdatePlayerDataInt(index, "Vkontakte", PI[index][pVkontakte] = 0);
			DeletePVar(index, "CodeVK"); 
			return false;
		}
		case 7723:
		{
			if GetString(data, "-1") *then {
				
				SCM(index, 0x4c75a3FF, !"[restorevk]:{FFFFFF} ������ �������� �� ��������� � ������� ��������");
				return PlayerDialogVK(index, 4);
			}
			return SPDF(index, 7724, DIALOG_STYLE_INPUT, "{BFBBBA}{FFFFFF}�������������� | {ae433d}���������", "\n{ffffff}����� ������ ��������� ��� �� ��������\n%s ��������� {ae443d}���{ffffff},\n������� ���������� ������ � ������ ����.\n\n{ae443d}����� �������� ���� � ����� � �������,\n����������� ���������� ������: ALT + TAB!\n\n", !"�", !"�", data);
		}
		case 3002:
			return SPDF(index, 7777, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}���������� | {ae433d}���������", "{FFFFFF}��������\t{FFFFFF}��������\n{2787F5}1. {FFFFFF}�������:\t%s\n{2787F5}2. {FFFFFF}�������� �������\n{2787F5}3. {FFFFFF}�������� IP\t{9ACD32}��������{FFFFFF}", !"�", !"�", data);
		
	}
	return false;
}

stock PlayerDialogVK(playerid, list = 0)
{
	switch list do
	{
		case 0:
		{
			if PI[playerid][pVkontakte] *then
				return GetVKName(playerid, 0);
			else 
				SPD(playerid, 7777, DIALOG_STYLE_TABLIST_HEADERS, !"{FFFFFF}���������� | {ae433d}���������", "{FFFFFF}��������\t{FFFFFF}��������\n{2787F5}1. {FFFFFF}�������:\t{ae433d}�� ��������\n{2787F5}2. {FFFFFF}��������� �������\n", !"�", !"�");
		}
		case 1: return SPD(playerid, 7778, DIALOG_STYLE_INPUT, !"{FFFFFF}���������� | {ae433d}���������", "\n{ffffff}������ ��� ��� ����� � ������ {ae433d} IP-������ {ffffff} � ��� ����� ������������� ���, ������� ����� ��������� ��� ����� \n{ae433d}������ ��������{FFFFFF}.\n\n��� ����� ������� � ������ �������� {4c75a3}��������� {ffffff}�� ��� �� ��������� ������ � �������� ��������.\n������������ � ������ ������ �������� {4c75a3}���������{ffffff}. ���������� ������ �������� � ������� ������ ������� - \n�� {ae433d}������� {ffffff}�������� ���� ������� �������!\n\n������� ������������:\n{ae433d}- {ffffff}����������� �����������\n{ae433d}- {ffffff}���������� � ����� ���������\n{ae433d}- {ffffff}���������� � ����������� � ������� ������\n{ae433d}- {ffffff}������� ����������� �������� ��������\n\n��� ��������� ������ ������� �������� ���������� ����:\n{ae433d}1. {ffffff}��������� �� ������ {4c75a3}https://vk.com/sampcarton {ffffff}( {4c75a3}Arizona Carton � ������ �������� ������ SAMP{ffffff} )\n{ae433d}2. {ffffff}��������� ��������� �� ������ ����� ������ {ae433d}\"��������� ���������\"\n{ae433d}3. {ffffff}�������� ������ �� ���� �������� {4c75a3}��������� {ffffff}� ���� ���� � ������� {ae433d}\"�����\"\n\n", !"�", !"�");
		case 2: return SPD(playerid, 7780, DIALOG_STYLE_MSGBOX, !"{FFFFFF}������� | {ae433d}���������", !"{FFFFFF}�� ������������� ������� ����� �������� {4c75a3}���������{FFFFFF}?", !"�", !"�");
		case 3:
		{
			new code = 100000+random(900000);
			SetPVarInt(playerid, "CodeVK", code);
			
			//f(mysql_string, 400, "vk_id=%d&msg=%d&list=3&nickname=%s", PI[playerid][pVkontakte], code, PN(playerid));
			//SendVK(playerid, mysql_string);
		}
		case 4: return SPD(playerid, 7723, DIALOG_STYLE_INPUT, !"{FFFFFF}�������������� | {ae433d}���������", !"{ffffff}������� ������ �� ����������� � �������� �������� {4c75a3}���������", !"�", !"�");
	}
	return false;
}

stock GetVKName(playerid, did = 1)
{	
	//f(mysql_string, 400, "vk_id=%d&list=2", PI[playerid][pVkontakte]);
	//SendVK(playerid, mysql_string);
	return DialogListID[playerid] = did;
}