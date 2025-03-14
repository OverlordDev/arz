
/*
// ILYA SYSTEM 
new SQL_STRING[1250];
#define str_f(%0,%1) format(SQL_STRING, sizeof SQL_STRING, %0, %1), SQL_STRING
*/

new
	RETURN_STRING[10][2048],
	RETURN_INTEGER[10],
	RETURN_STRING_FIXTEXT[128];

stock GetArray_Massive_return(num = 0, Data[], search_id, len = sizeof Data)
{
	RETURN_INTEGER[num] = -1;
	
	for new i; i < len; i++ do
		if(Data[i] == search_id)
			RETURN_INTEGER[num] = i;
}

#define GetArrayMassive(%0,%1,%2) (GetArray_Massive_return(%0, %1, %2), RETURN_INTEGER[%0])

stock String_UnPackMassive(Pack_Data[], UnPack_Data[][], unpack_format[] = "s[128]", unpack_separation[] = ",", len = sizeof UnPack_Data) 
{
	sscanf(Pack_Data, (str_f("p<%s>a<%s>[%d]", unpack_separation, unpack_format, len)), SQL_GET_ROW_STR);
	
	for new i; i < len; i++ do
		SetString(UnPack_Data[i], SQL_GET_ROW_STR[i]);

	return true;
}

stock Int_UnPackMassive(Pack_Data[], UnPack_Data[], unpack_format[] = "i", unpack_separation[] = ",", len = sizeof UnPack_Data)
	return (sscanf(Pack_Data, (str_f("p<%s>a<%s>[%d]", unpack_separation, unpack_format, len)), UnPack_Data));


stock Int_PackMassive_return(num = 0, Data[], len = sizeof Data)
{
	RETURN_STRING[num][0] = EOS;
	
	for new i; i < len; i++ do
	{
		strcat(RETURN_STRING[num], ( str_f("%d,", Data[i]) ) );
	}
}

#define Int_PackMassive(%0,%1) (Int_PackMassive_return(%0, %1), RETURN_STRING[%0])

stock Float_UnPackMassive(Pack_Data[], Float:UnPack_Data[], unpack_format[] = "f", unpack_separation[] = ",", len = sizeof UnPack_Data)
	return (sscanf(Pack_Data, (str_f("p<%s>a<%s>[%d]", unpack_separation, unpack_format, len)), UnPack_Data));
	
stock Float_PackMassive_return(num = 0, Float:Data[], len = sizeof Data)
{
	RETURN_STRING[num][0] = EOS;
	
	for new i; i < len; i++ do
	{
		strcat(RETURN_STRING[num], ( str_f("%f,", Data[i]) ) );
	}
}

#define Float_PackMassive(%0,%1) (Float_PackMassive_return(%0, %1), RETURN_STRING[%0])

stock String_PackMassive_return(num = 0, Data[][], len = sizeof Data)
{
	RETURN_STRING[num][0] = EOS;
	
	for new i; i < len; i++ do
	{
		strcat(RETURN_STRING[num], ( str_f("%s%s", Data[i], (len-1) == i ? "":",") ) );
	}
}

#define String_PackMassive(%0,%1) (String_PackMassive_return(%0, %1), RETURN_STRING[%0])


#define FixText(%0) (FixText_function(%0), RETURN_STRING_FIXTEXT)

stock FixText_function(const string[])
{
	for new i; i < strlen(string); i++ do
	{
		switch string[i] do
		{ 
			case '�': RETURN_STRING_FIXTEXT[i] = 'a';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'A';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'e';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'E';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'e';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'E';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'k';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'K';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'M';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'H'; 
			case '�': RETURN_STRING_FIXTEXT[i] = 'o';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'O';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'p';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'P';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'c';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'C';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'y';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'Y';   
			case '�','�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'x';  
			case '�': RETURN_STRING_FIXTEXT[i] = 'X'; 
			case '�','�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			case '�': RETURN_STRING_FIXTEXT[i] = '�';  
			default: RETURN_STRING_FIXTEXT[i] = string[i];
        }  
    }

	RETURN_STRING_FIXTEXT[strlen(string)] = '\0';
} 
