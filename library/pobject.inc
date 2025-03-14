stock GetCountUsedObj(id, type = 0, interior_find = 0)
{
	f(mysql_string, 150, "SELECT * FROM `bh_objects` WHERE `%s` = '%d' AND Interior %s= 0;", !type ? "HouseID":"BizID", id, !interior_find ? "":"!" );

   	new use_obj,
   	    Cache:result = mysql_query(mysql, mysql_string);
	
   	use_obj = cache_num_rows();
   	cache_delete(result);
    return use_obj;
}

stock ShowListUsedObj(playerid, id, type, type_list)
{
	f(mysql_string, 150, "SELECT * FROM `bh_objects` WHERE `%s` = '%d' AND Interior %s= 0;", !type ? "HouseID":"BizID", id, type_list ? "!":"");

    new Cache:result = mysql_query(mysql, mysql_string);
	
	global_str = "";
	
	new count = type ? BizData[id][bObjectCount][type_list]:HouseInfo[id][hObjectCount][type_list];
	
	for new i,item; i < count; i++ do
	{
		if cache_num_rows() > i *then
			cache_get_value_index_int(i, 12, item), format(mysql_string, 128, "{FFFFFF}[%d] %s\n", i + 1, ItemsInfo[item][itemName]);
		else
			format(mysql_string, 128, "{AFAFAF}[%d] ���� ��������\n", i + 1);
	
		strcat(global_str, mysql_string);
	}
	
	strcat(global_str, "{FFFF00}������ �������������� ����");
	
	spdList(playerid, 0, id);
	spdList(playerid, 1, type);
	spdList(playerid, 2, type_list);
	spdList(playerid, 3, count);
	
	cache_delete(result);
	 
	return SPD(playerid, 2435, DIALOG_STYLE_LIST, !type_list ? !"�������� �� �����":!"�������� � ���������", global_str, !"�������", !"�����");
}

stock GetEditBH_object_distance(playerid, Float:x, Float:y, Float:z, &biz = -1, &house = -1)
{
	new Float:distance = 21.0;
	
	if !(BizEntered[playerid] == -1) && GetString(BizData[BizEntered[playerid]][bOwner], PN(playerid)) && GetPlayerVirtualWorld(playerid) == BizEntered[playerid] + 100 *then
		distance = PointToPoint(x,y,z, BizData[BizEntered[playerid]][bExit][0], BizData[BizEntered[playerid]][bExit][1], BizData[BizEntered[playerid]][bExit][2]), biz = BizEntered[playerid];
	
	else if !(HouseEntered[playerid] == -1) && GetString(HouseInfo[HouseEntered[playerid]][hOwner], PN(playerid)) && GetPlayerVirtualWorld(playerid) == HouseEntered[playerid] + 50 *then
		distance = PointToPoint(x,y,z, HouseInfo[HouseEntered[playerid]][hExit_X], HouseInfo[HouseEntered[playerid]][hExit_Y], HouseInfo[HouseEntered[playerid]][hExit_Z]), house = HouseEntered[playerid];
		
	else
	{
		for new i; i < OWNABLEHOUSES; i++ do
		{
			if GetString(HouseInfo[i][hOwner], PN(playerid)) *then
			{
				if distance > PointToPoint(x,y,z, HouseInfo[i][hEnter_X],HouseInfo[i][hEnter_Y],HouseInfo[i][hEnter_Z]) *then
					distance = PointToPoint(x,y,z, HouseInfo[i][hEnter_X],HouseInfo[i][hEnter_Y],HouseInfo[i][hEnter_Z]), house = i;
			}
			
			if i < OWNABLEBIZES && GetString(BizData[i][bOwner],PN(playerid)) *then
			{
				if distance > PointToPoint(x,y,z, BizData[i][bEnter][0],BizData[i][bEnter][1],BizData[i][bEnter][2]) *then
					distance = PointToPoint(x,y,z, BizData[i][bEnter][0],BizData[i][bEnter][1],BizData[i][bEnter][2]), biz = i;
			}
		
		}
	}
	
	return _:distance;
}

stock CreateEditBH_object(playerid, itemid, type)
{
	new
		Float:x, Float:y, Float:z;
			
	GetPlayerPos(playerid, x, y, z);
	
	new biz = -1, house = -1, Float:distance = Float:GetEditBH_object_distance(playerid, x,y,z, biz, house);
	
	type = type > 0 ? 1:0;
	
	if !(biz == -1) && GetCountUsedObj(biz, 1, type) >= BizData[biz][bObjectCount][type] *then
		return SCM(playerid, COLOR_RED, "[������]{FFFFFF} � ������ ������� �� ������� ������ ��� ���������, ���������� ��������.");
	
	else if !(house == -1) && GetCountUsedObj(house, 0, type) >= HouseInfo[house][hObjectCount][type] *then
		return SCM(playerid, COLOR_RED, "[������]{FFFFFF} � ������ ���� �� ������� ������ ��� ���������, ���������� ��������."); 
		

	else if MAX_CREATE_OBJECTS <= TOTALOBJECTS *then 
		return SCM(playerid, -1, "LIMIT OBJECTS IN SERVER CREATED");
	
	if distance > 20.0 *then 
		return SCM(playerid, COLOR_RED, "[������]{FFFFFF} �� �� ������ ���������� ������ ������, ����� �� ���������� �� 20 ������ �� ������ ����������� ���������!");
	
	/*EditObjectPlayer[playerid] = CreateDynamicObject(ItemsInfo2[itemid][itemModel], x+2, y+2, z, 0, 0, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	EditDynamicObject(playerid, EditObjectPlayer[playerid]);
	

	Int_SetPlayerData(playerid, "install_house_obj", PickInvent[playerid] + 1);*/
	
	new id = PickInvent[playerid] + 1;
			
	BH_Object[TOTALOBJECTS][objModel] = ItemsInfo[itemid][itemModel];//GetDynamicObjectModel(objectid);
			
	DestroyDynamicObject(EditObjectPlayer[playerid]);
			
	if Float:GetEditBH_object_distance(playerid, x,y,z, BH_Object[TOTALOBJECTS][objBizID], BH_Object[TOTALOBJECTS][objHouseID]) > 20.0 *then 
		return SCM(playerid, COLOR_RED, "[������]{FFFFFF} �� �� ������ ���������� ������ ������, ����� �� ���������� �� 20 ������ �� ������ ����������� ���������!");
			
			
	new item = Inventory[playerid][0][id-1];
			
	if ItemsInfo[item][itemModel] == BH_Object[TOTALOBJECTS][objModel] *then
		ClearItem(playerid, id-1, 1);
	else 
	{
		return SCMF(playerid, -1, "������ �������� ������������ | ���: %d %d %d", item, ItemsInfo[item][itemModel], BH_Object[TOTALOBJECTS][objModel]);
	}
			
	BH_Object[TOTALOBJECTS][objPosX] = x+2;
	BH_Object[TOTALOBJECTS][objPosY] = y+2;
	BH_Object[TOTALOBJECTS][objPosZ] = z;

	/*BH_Object[TOTALOBJECTS][objRotX] = rx;
	BH_Object[TOTALOBJECTS][objRotY] = ry;
	BH_Object[TOTALOBJECTS][objRotZ] = rz;*/
		
	BH_Object[TOTALOBJECTS][objItemID] = item;
	BH_Object[TOTALOBJECTS][objWorld] = GetPlayerVirtualWorld(playerid);
	BH_Object[TOTALOBJECTS][objInterior] = GetPlayerInterior(playerid);
			
	f(global_str, 400, "INSERT INTO `bh_objects` (`Model`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `HouseID`, `BizID`, `Owner`, `Date`, `ItemID`, `World`, `Interior`) VALUES (%d, '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%s', CURRENT_TIMESTAMP(), '%d', '%d', '%d')",
		BH_Object[TOTALOBJECTS][objModel],
		BH_Object[TOTALOBJECTS][objPosX],
		BH_Object[TOTALOBJECTS][objPosY],
		BH_Object[TOTALOBJECTS][objPosZ],
		BH_Object[TOTALOBJECTS][objRotX],
		BH_Object[TOTALOBJECTS][objRotY],
		BH_Object[TOTALOBJECTS][objRotZ],
		BH_Object[TOTALOBJECTS][objHouseID], BH_Object[TOTALOBJECTS][objBizID], PN(playerid), item,
		BH_Object[TOTALOBJECTS][objWorld],
		BH_Object[TOTALOBJECTS][objInterior] );
			
	mysql_tquery(mysql, global_str, "Create_BH_Object", "d", TOTALOBJECTS);
			
	return SCM(playerid, 0x6495EDFF, !"[����������]{FFFFFF} �� ������� ����������� �������. ���� ������ ������ ��� �����������, ������� /pobject ����� ����.");
   
	//return SCM(playerid, COLOR_VALIK, !"[���������]{FFFFFF} ����� ��������� ��������� ������� - ������� �� �������, ����� �������� - ������� ESC.");
}

public: Create_BH_Object(id)
{
	BH_Object[id][objBaseID] = cache_insert_id();
	
	BH_Object[id][objID] = CreateDynamicObject(BH_Object[id][objModel], BH_Object[id][objPosX], BH_Object[id][objPosY], BH_Object[id][objPosZ], BH_Object[id][objRotX], BH_Object[id][objRotY], BH_Object[id][objRotZ], BH_Object[id][objWorld], BH_Object[id][objInterior]);
	
	return TOTALOBJECTS ++;	
}