enum phone_shop_data
{
    shop_phoneId,
    shop_phoneCost,
    shop_phoneIdColor[11]
};

new PhoneShop[3][phone_shop_data] =
{
    {329, 200, {1476, 329, 1477, 1478, 1479, 1480, 1481, 1482, 1483, 1484, 1485}},
    {1487, 400, {1486, 1487, 1488, 1489, 1490, 1491, 1492, 1493, 1494, 1495, 1496}},
    {382, 600, {382, 383, 1474, 384, 389, 1475, 385, 386, 387, 388, 1473}}
};

new PhoneBuyData[MAX_PLAYERS];

new
    PhoneColor[MAX_PLAYERS],
    PhoneOpen[MAX_PLAYERS];

stock GetPhoneID(itemId) {
    
    switch itemId do {

        case 719..729: 
            return 0; // iphone x
        
        case 708..718:
            return 1; // Samsung Galaxy_S10

        case 675..685:
            return 2; // Xiaomi
        
        case 697..707:
            return 3; // Google Pixel 3
        
        case 686..696:
            return 4; // Huawei P20 PRO

    }

    return INVALID_DATA_ID;
}

stock ShowPhoneMenu(playerid)
{
    f(global_str, 550, "\
    {B03131}[1]{FFFFFF} ���������\n\
    {B03131}[2]{FFFFFF} ������ (���������)\n\
    {B03131}[3]{FFFFFF} ������/���������� ���. ����������\n\
    {B03131}[4]{FFFFFF} �����{B03131}\n\
    {B03131}[5]{FFFFFF} �����[%s{FFFFFF}]\n\
    {B03131}[6]{FFFFFF} ��������� ������\n\
    {B03131}[7]{FFFFFF} ��������� ������� � ����� \"%s\"\n\
    {B03131}[8]{FFFFFF} ������ �������\n\
    %s", PlayerPlayed{playerid} ? ("{7def58}���") : ("{ef5858}����"), PI[playerid][pPhoneInfo][1] ? ("�������") : ("�������"),
    !(FP_Data[playerid][F_FAMILY_ID] == -1) ?  (GetFamilyDataInt(FP_Data[playerid][F_FAMILY_ID], "brend") ? "\n{B03131}[9]{FFFFFF} ����� ���������\n{B03131}[10]{FFFFFF} ����� ������������":""): "");
    
    return SPD(playerid, 966, DIALOG_STYLE_LIST, !"����", global_str, !"�������", !"������");
}

stock IsPhoneModel(modelId)
{
    if modelId >= 18865 && modelId <= 18874 or modelId == 19513 *then
        return true;

    return false;
}

stock GetPhoneColorIdByModel(modelId)
{
    switch modelId do
    {
        case 18866: return 0;
        case 18872: return 2;
        case 18871: return 3;
        case 18867: return 4;
        case 19513: return 5;
        case 18865: return 6;
        case 18873: return 7;
        case 18868: return 9;
        case 18869: return 8;
        case 18870: return 10;
    }

    return 1;
}

stock GetPhoneColorNameByModel(modelId)
{
    new Color[14];

    switch modelId do
    {
        case 18865: Color = "���������";
        case 18866: Color = "�������";
        case 18867: Color = "�������";
        case 18868: Color = "������";
        case 18869: Color = "�������";
        case 18870: Color = "����� �������";
        case 18871: Color = "�������";
        case 18872: Color = "�����";
        case 18873: Color = "�������";
        case 18874: Color = "�����";
        case 19513: Color = "����������";

        default: Color = "none";
    }

    return Color;
}

stock ShowPlayerBuyPhone(playerid, bool:update = true)
{
    if update *then 
        PhoneBuyData[playerid] = -1;

    format(global_str, 300, "\
    {FFFFFF}������������\t{FFFFFF}����������\n\
    ������:\t%s\n\
    {FFFFFF}����:\t%s\n\
    {FFFFFF}������:\t{73B461}${FFFFFF}%d", 
    !(PhoneBuyData[playerid] == -1) ? (str_f("%s", ItemsInfo[PhoneBuyData[playerid]][itemEng_name])):"�������", 
    !(PhoneBuyData[playerid] == -1) && !GetString(GetPhoneColorNameByModel(ItemsInfo[PhoneBuyData[playerid]][itemModel]), "�����") ? 
    GetPhoneColorNameByModel(ItemsInfo[PhoneBuyData[playerid]][itemModel]):"�����������", 
    !(PhoneBuyData[playerid] == -1) ? (PhoneShop[gpdList(playerid, 0)][shop_phoneCost] + (!GetString(GetPhoneColorNameByModel(ItemsInfo[PhoneBuyData[playerid]][itemModel]), "�����") ? 200000:0)):0);

    return SPD(playerid, 2000, DIALOG_STYLE_TABLIST_HEADERS, !"{FFFFFF}����������� | {ae433d}��������� ����������", global_str, !"�", !"�");
}