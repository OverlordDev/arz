
enum p_quest_bonus {
	
	P_QUEST_ID,
	P_QUEST_PROGRESS
};

new const P_QuestBonus[MAX_PLAYERS][p_quest_bonus];

enum bonus_quest_data {
	
	bQuestName[100],
	bQuestStory[500],
	bQuestPayHour,
	bQuestMaxProgress
};


new const QuestBonus[][bonus_quest_data] = {
	
	{"���-�� �������� � ����...", "�� ���� ������� ���������� � ����� ������� �������� ����� ����������� �� ������� ������.\n��������� ���� ��� � �� ������ ������ � ��� ����, ������� �������� ��� ����� � �� �����.\n�� ��� ��� � �� ���� �� ������ � ������ ������, �� ���� ��� ������ ��������� ��.", 25, 2},
	{"�������", "... ������, �� �-���, ������, ������� ��\n�� �����.. ������ �� �����, ����� ������� �����, ���? ��� �� ���� ����..", 50, 3},
	{"� � ���� ���������", "���.... ���������\n� ���� ���� � ����� �������� ��������� �� ����������, ��� ����� ������\n������� ������ �.", 50, 1}
	//{"�������������� ����������", "������������ ����� ��� ��� ����� ���, �������������� ����������.", 50, 3}

};


new const QuestBonusStory[][][] = {

	{"���������� �� ���������� ������� ����� �������� � ��� �� GPS ����� ������� ������� \'�����\'.\n����� ���� ���������� � �����.", "������������ �� ����� � ������ �������� ���������� ����.", ""},
	{"� ������� ������ ��� ������ ��� ��������� ������� ��� ��������� �����,\n�� �� ��� ��� ������... ����� � ����� ��� ��� ���������.", "�� �������� ���� ������� �������� � ������ � ��������� ��� �������� ����� ���������.\n�� ��� ������ ������� ���� ���������, ������� ��� ����.\n��� ������� ���� �������� � �������� ��� �������,\n�������������� ����� ��� ��������� ������� ��� ���� ��������.", "����������� ����� �������� �� �������� ����������� ������ �������.\n��� ����� ����������� ���� ���.\n�� ���� ����� �� ������ ���� ����� �������������������� ��������� ��� ��."},
	{"�������� �� ����� ���������� � ���� �� GPS � ������ ���������.", "", ""}
};

new const QuestQuestions[][][] = {
	
	{"10 * 10", "100"},
	{"90 / 2", "45"},
	{"S = (a + b) * 2\na = 20, b = 5\n���� ����� S?", "50"},
	{"������ �� 144", "12"},
	{"������ ����� ����� ��?", "3"}

};


cmd:arzquest(playerid)
{
	global_str = "{FFFFFF}�������� ������\t{FFFF00}��������\n";

	for new i; i < sizeof (QuestBonus); i++ do {

		strcat(global_str, (str_f("\n%s\t%s", QuestBonus[i][bQuestName], P_QuestBonus[playerid][P_QUEST_ID] > i ? "{73B461}[��������]{FFFFFF}":"{D5736E}[�� ��������]{FFFFFF}")));

	}

	return SPD(playerid, 9924, DIALOG_STYLE_TABLIST_HEADERS, !"�������� ��������� �����", global_str, !"�����", !"������");
}

stock QuestBonus_next(playerid, bool:up_etap = false)
{
	new data = P_QuestBonus[playerid][P_QUEST_PROGRESS], id = P_QuestBonus[playerid][P_QUEST_ID];

	if up_etap == false *then { 

		data ++;

		P_QuestBonus[playerid][P_QUEST_PROGRESS] = data;

		if P_QuestBonus[playerid][P_QUEST_PROGRESS] == QuestBonus[id][bQuestMaxProgress] *then {

			// ������ ������ ���

			P_QuestBonus[playerid][P_QUEST_PROGRESS] = 0;
			P_QuestBonus[playerid][P_QUEST_ID] ++;
			
			PI[playerid][pPlayHour] += QuestBonus[id][bQuestPayHour];

			SPDF(playerid, 0, DIALOG_STYLE_MSGBOX, !"�������������� �� �����", "{FFFFFF}�� ������� ������ ������� � ��������: {D5736E}- {FFFFFF}%d ���(��) � /arz", !"�������", !"", QuestBonus[id][bQuestPayHour]);
		}

		SQL("UPDATE arzquest SET quest_id = %d, quest_progress = %d WHERE player_id = %d LIMIT 1;", P_QuestBonus[playerid][P_QUEST_ID], P_QuestBonus[playerid][P_QUEST_PROGRESS], PI[playerid][pID]);

		if !(P_QuestBonus[playerid][P_QUEST_ID] == id) *then
			return true;
	}

	switch id do 
	{
		case 0: {

			switch data do {

				case 0: {
					
					EnableGPSForPlayer(playerid, -1404.3688,-1925.4354,22.0040);
					SCM(playerid, COLOR_VALIK, !"[����������]{FFFFFF} �������������� ����� �������� � ��� �� ���������.");
				}

				case 1: {

					EnableGPSForPlayer(playerid, -1877.7156,-1897.4963,88.5346);

					_GiveGun(playerid, 43, 10);

				}
			}
			
		}

		case 1: {

			switch data do {
				
				case 0: {

					EnableGPSForPlayer(playerid, 2200.4019,-1532.5143,10.8281);
				}

				case 1: {
					
					EnableGPSForPlayer(playerid, 955.1244,-1874.4138,8.6123);
					SCM(playerid, COLOR_GREY, !"������� ��� ����... ������ �������.");

				}

				case 2: {
					
					EnableGPSForPlayer(playerid, 767.2220,-582.0569,17.3359);
					SCM(playerid, COLOR_VALIK, !"[���������]{FFFFFF} ��� ���������� ������ ��� ����� ������������ ����� �������� ������ ����� \'Don La Gandon\'.");
				}
			}
		}

		case 2: {

			switch data do {
				
				case 0: {

					EnableGPSForPlayer(playerid, -2703.4348,373.1399,4.9689);
				}
			}

		}
	}

	return SCM(playerid, COLOR_OLDRED, !"[����������]{FFFFFF} ���� �� ������ ��� �� ��� ��������� ��� �� ������ => /arzquest");
}


stock QuestBonusData(playerId, data)
{
	if !(P_QuestBonus[playerId][P_QUEST_ID] - data == 0) *then
		return SCM(playerId, COLOR_OLDRED, !"[������]{FFFFFF} ���������� �������� ������ �� �������!");

	format(global_str, 1250, "\
	\t\t\t\t\t{D5736E}%s{FFFFFF}\n\n\
	{FFFF00}������: {FFFFFF}%s\n\n\
	{FFFF00}�� ���������� ������� ��� �����:\n\
	{D5736E}- {FFFFFF}%d ���(��) � /arz\n\n\
	{FFFF00}�������� ���������� ������: {FFFFFF}%d �� %d.\n\n\
	{FFFF00}��� ������?: {FFFFFF}%s",
	
	QuestBonus[data][bQuestName],
	QuestBonus[data][bQuestStory],
	QuestBonus[data][bQuestPayHour],
	P_QuestBonus[playerId][P_QUEST_PROGRESS],
	QuestBonus[data][bQuestMaxProgress],
	QuestBonusStory[data][P_QuestBonus[playerId][P_QUEST_PROGRESS]]);


	return SPD(playerId, 9923, DIALOG_STYLE_MSGBOX, !"�������� ��������� �����", global_str, !"�����", !"������");
}

stock GetBonusQuest(playerid, data) {

	if !(data == P_QuestBonus[playerid][P_QUEST_ID]) *then
		return -1;
		
	return P_QuestBonus[playerid][P_QUEST_PROGRESS];

}

public: QuestBonusLoad(playerid) {

	if cache_get_row_count() *then {

		global_str = "[����������]{FFFFFF} ��� �������� ������� ������������: /arzquest";

		P_QuestBonus[playerid][P_QUEST_ID] = cache_get_row_int(0, 1, mysql);
		P_QuestBonus[playerid][P_QUEST_PROGRESS] = cache_get_row_int(0, 2, mysql);

	}
	else {

		global_str = "[����������]{FFFFFF} ����� �������� ������ ��� ���� ���, /arzquest ( ��� �������� �� ������. )";

		P_QuestBonus[playerid][P_QUEST_ID] = 
		P_QuestBonus[playerid][P_QUEST_PROGRESS] = 0;

		SQL("INSERT INTO arzquest (`player_id`) VALUES ('%d')", PI[playerid][pID]);
	}
	
	return SCM(playerid, COLOR_OLDRED, global_str);
}