#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

static string one_to_one[10] = {u8"爸爸",u8"媽媽",u8"哥哥",u8"弟弟",u8"姊姊",u8"妹妹",u8"兒子",u8"女兒",u8"妻子",u8"丈夫" };
static string out_family[67] = { /*0.*/"自己",/*1.*/"阿祖", /*2.*/"祖父",/* 3.*/"祖母",/* 4.*/"外祖父", /*5.*/"外祖母",/*6.*/"父親", /*7.*/"伯父"/*(較年長)*/, /*8.*/"伯母",/* 9.*/"叔父"/*(較年輕)*/, /*10.*/"嬸嬸", /*11.*/"姑媽"/* * */,/*12.*/"姑丈",/*13.*/"母親",/* 14.*/"舅舅" /***/,/* 15.*/"舅媽 ",/*16.*/"姨媽"/* * */,/*17.*/"姨丈",/*18.*/"堂兄",/* 19.*/"堂弟" ,/*20.*/"堂姊 ",/*21.*/"堂妹 ",/*22.*/"表兄",/* 23.*/"表弟",/* 24.*/"表姊",/* 25.*/"表妹",/*26.*/"哥哥",/* 27.*/"嫂嫂",/* 28.*/"弟弟", /*29.*/"弟媳", /*30.*/"姊姊",/* 31.*/"姊夫", /*32.*/"妹妹", /*33.*/"妹夫", /*34.*/"姪子", /*35.*/"姪女",/* 36.*/"外甥",/* 37.*/"外甥女",/*38.*/"兒子",/* 39.*/"媳婦",/*40.*/"孫子",/* 41.*/"孫女",/* 42.*/"女兒",/* 43.*/"女婿",/* 44.*/"外孫",/*45.*/"夫",/* 46.*/"夫父",/* 47.*/"夫母",/* 48.*/"夫兄", /*49.*/"夫兄嫂",/* 50.*/"夫弟",/* 51.*/"夫弟媳",/* 52.*/"夫姊",/* 53.*/"夫姊夫",/* 54.*/"夫妹",/* 55.*/"夫妹夫",/*56.*/"妻",/* 57.*/"妻父",/* 58.*/"妻母",/* 59.*/"妻兄",/* 60.*/"妻兄嫂",/* 61.*/"妻弟",/* 62.*/"妻弟媳",/* 63.*/"妻姊",/* 64.*/"妻姊夫",/* 65.*/"妻妹",/* 66.*/"妻妹夫" };
static int list[67][10] = {
	/*0自己*/{6,13,26,28,30,32,38,42,56,45},
	/*1阿祖*/{-1,-1,-1,-1,-1,-1,-2/*父親：2/母親：4*/,-2/*父親：3/母親：5*/,1,1},
	/*2祖父*/{1,1,-1,-1,-1,-1,-2/*年輕：9/年長：7*/,11,3,-1},
	/*3祖母*/{1,1,-1,-1,-1,-1,-2/*年輕：9/年長：7*/,11,-1,2},
	/*4外祖父*/{1,1,-1,-1,-1,-1,14,16,5,-1},
	/*5外祖母*/{1,1,-1,-1,-1,-1,14,16,-1,4},
	/*6父親*/{2,3,7,9,11,11,-2/*年輕：28/年長：26*/,-2/*年輕：32/年長：30*/,13,-1},
	/*7伯父*/{2,3,7,9,11,11,-2/*年輕：19/年長：18*/,-2/*年輕：21/年長：20*/,8,-1},
	/*8伯母*/{-1,-1,-1,-1,-1,-1,-2/*年輕：19/年長：18*/,-2/*年輕：21/年長：20*/,-1,7},
	/*9叔父*/{2,3,7,9,11,11,-2/*年輕：19/年長：18*/,-2/*年輕：21/年長：20*/,10,-1},
	/*10嬸嬸*/{-1,-1,-1,-1,-1,-1,-2/*年輕：19/年長：18*/,-2/*年輕：21/年長：20*/,-1,9},
	/*11姑媽*/{2,3,7,9,11,11,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,-1,12},
	/*12姑丈*/{-1,-1,-1,-1,-1,-1,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,11,-1},
	/*13母親*/{4,5,14,14,16,16,-2/*年輕：28/年長：26*/,-2/*年輕：32/年長：30*/,-1,6},
	/*14舅舅*/{4,5,14,14,16,16,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,15,-1},
	/*15舅媽*/{-1,-1,-1,-1,-1,-1,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,-1,14},
	/*16姨媽*/{4,5,14,14,16,16,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,-1,17},
	/*17姨丈*/{-1,-1,-1,-1,-1,-1,-2/*年輕：23/年長：22*/,-2/*年輕：25/年長：24*/,16,-1},
	/*18堂兄*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*19堂弟*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*20堂姊*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*21堂妹*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*22表兄*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*23表弟*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*24表姊*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*25表妹*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*26哥哥*/{6,13,26,28,30,32,34,35,27,-1},
	/*27嫂嫂*/{-1,-1,-1,-1,-1,-1,34,35,-1,26},
	/*28弟弟*/{6,13,26,28,30,32,34,35,29,-1},
	/*29弟媳*/{-1,-1,-1,-1,-1,-1,34,35,-1,28},
	/*30姊姊*/{6,13,26,28,30,32,36,37,-1,31},
	/*31姊夫*/{-1,-1,-1,-1,-1,-1,36,37,30,-1},
	/*32妹妹*/{6,13,26,28,30,32,36,37,-1,33},
	/*33妹夫*/{-1,-1,-1,-1,-1,-1,36,37,32,-1},
	/*34姪子*/{-2/* 26/28/48/50 */,-2/* 27/29/49/51 */,34,34,35,35,-1,-1,-1,-1},
	/*35姪女*/{-2/* 26/28/48/50 */,-2/* 27/29/49/51 */,34,34,35,35,-1,-1,-1,-1},
	/*36外甥*/{-2/* 31/33/53/55/59/61/64/66 */,-2/* 30/32/52/54/60/62/63/65 */,36,36,37,37,-1,-1,-1,-1},
	/*37外甥女*/{-2/* 31/33/53/55/59/61/64/66 */,-2/* 30/32/52/54/60/62/63/65 */,36,36,37,37,-1,-1,-1,-1},
	/*38兒子*/{-2/* 0/45 */,-2/* 0/56 */,38,38,42,42,40,41,39,-1},
	/*39媳婦*/{-1,-1,-1,-1,-1,-1,40,41,-1,38},
	/*40孫子*/{38,39,40,40,41,41,-1,-1,-1,-1},
	/*41孫女*/{38,39,40,40,41,41,-1,-1,-1,-1},
	/*42女兒*/{-2/* 0/45 */,-2/* 0/56 */,38,38,42,42,44,44,-1,43},
	/*43女婿*/{-1,-1,-1,-1,-1,-1,44,44,42,-1},
	/*44外孫*/{43,42,44,44,44,44,-1,-1,-1,-1},
	/*45丈夫*/{46,47,48,50,52,54,38,42,0,-1},
	/*46夫父*/{-1,-1,-1,-1,-1,-1,-2/*年輕：50/年長：48*/,-2/*年輕：54/年長：52*/,47,-1},
	/*47夫母*/{-1,-1,-1,-1,-1,-1,-2/*年輕：50/年長：48*/,-2/*年輕：54/年長：52*/,-1,46},
	/*48夫兄*/{46,47,48,50,52,54,34,35,49,-1},
	/*49夫兄嫂*/{-1,-1,-1,-1,-1,-1,34,35,-1,48},
	/*50夫弟*/{46,47,48,50,52,54,34,35,51,-1},
	/*51夫弟媳*/{-1,-1,-1,-1,-1,-1,34,35,-1,50},
	/*52夫姊*/{46,47,48,50,52,54,36,37,-1,53},
	/*53夫姊夫*/{-1,-1,-1,-1,-1,-1,36,37,52,-1},
	/*54夫妹*/{46,47,48,50,52,54,36,37,-1,55},
	/*55夫妹夫*/{-1,-1,-1,-1,-1,-1,36,37,54,-1},
	/*56妻子*/{57,58,59,61,63,65,38,42,-1,0},
	/*57妻父*/{-1,-1,-1,-1,-1,-1,-2/*年輕：61/年長：59*/,-2/*年輕：65/年長：63*/,58,-1},
	/*58妻母*/{-1,-1,-1,-1,-1,-1,-2/*年輕：61/年長：59*/,-2/*年輕：65/年長：63*/,-1,57},
	/*59妻兄*/{57,58,59,61,63,65,36,37,60,-1},
	/*60妻兄嫂*/{-1,-1,-1,-1,-1,-1,36,37,-1,59},
	/*61妻弟*/{57,58,59,61,63,65,36,37,62,-1},
	/*62妻弟媳*/{-1,-1,-1,-1,-1,-1,36,37,-1,61},
	/*63妻姊*/{57,58,59,61,63,65,36,37,-1,64},
	/*64妻姊夫*/{-1,-1,-1,-1,-1,-1,36,37,63,-1},
	/*65妻妹*/{57,58,59,61,63,65,36,37,-1,66},
	/*66妻妹夫*/{-1,-1,-1,-1,-1,-1,36,37,65,-1},
};

int main(int argc, char* argv[]) {
	int i, j, k;
	string input;
	ifstream fin;
	//system("chcp 65001 && cls");//G++沒有支援
	fin.open(argv[1]/*"text0.txt"*/);
	if (!fin) {
		cout << "file couldn't open." << endl;
		exit(1);
	}
	while (getline(fin, input)) {
		//cout << input << endl;
		string s;
		int pos = 0;
		int f=0, l=0;
		s = input;
		vector<int> pre_previous;//前一個人的爸媽
		int previous = 0;//前一個人的代碼
		int person = 0;//現在的
		int sex = 0;//女生1 男生2
		if (s.find(u8"我(女)") != -1 || s.find(u8"我的丈夫") != -1|| s.substr(0, 6) == u8"丈夫") sex = 1;
		else if (s.find(u8"我(男)") != -1 || s.find(u8"我的妻子") != -1|| s.substr(0, 6) == u8"妻子") sex = 2;
		//sex 女生1 男生2
		 do{
			pos = input.find(u8"的", pos);			
			if (pos - f < 0)l = s.size() - f;
			else l = pos - f;
			s = s.substr(f, /*pos - f*/l);			
			if (s.find(u8"我") == -1) {
				for (i = 0; i < 10; i++) {
					if (s.find(one_to_one[i]) != -1) {
						break;
					}
				}//i為那10個的對應位置
				person = list[previous][i];
				if (person == -2) {
					if (previous == 2 || previous == 3) {
						if (s.find(u8"年輕") != -1) person = 9;
						else person = 7;
					}//祖父母
					else if (previous == 6 || previous == 13) {
						if (i == 6) {
							if (s.find(u8"年輕") != -1) person = 28;
							else person = 26;
						}//兒子
						else {
							if (s.find(u8"年輕") != -1) person = 32;
							else person = 30;
						}//女兒
					}//父母
					else if (previous == 7 || previous == 8 || previous == 9 || previous == 10) {
						if (i == 6) {
							if (s.find(u8"年輕") != -1) person = 19;
							else person = 18;
						}//兒子
						else {
							if (s.find(u8"年輕") != -1) person = 21;
							else person = 20;
						}//女兒
					}//伯父伯母叔父嬸嬸
					else if (previous == 11 || previous == 12 || previous == 14 || previous == 15 || previous == 16 || previous == 17) {
						if (i == 6) {
							if (s.find(u8"年輕") != -1) person = 23;
							else person = 22;
						}//兒子
						else {
							if (s.find(u8"年輕") != -1) person = 25;
							else person = 24;
						}//女兒
					}//姑媽姑丈舅舅舅媽姨媽姨丈
					else if (previous == 18 || previous == 19 || previous == 20 || previous == 21) {
						while (pre_previous[pre_previous.size() - 1] == 18 || pre_previous[pre_previous.size() - 1] == 19 || pre_previous[pre_previous.size() - 1] == 20 || pre_previous[pre_previous.size() - 1] == 21)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 7 || pre_previous[pre_previous.size() - 1] == 8) person = 7;
							else person = 9;
						}//爸爸
						else {
							if (pre_previous[pre_previous.size() - 1] == 7 || pre_previous[pre_previous.size() - 1] == 8) person = 8;
							else person = 10;
						}//媽媽
					}//堂兄弟姊妹
					else if (previous == 22 || previous == 23 || previous == 24 || previous == 25) {
						while (pre_previous[pre_previous.size() - 1] == 22 || pre_previous[pre_previous.size() - 1] == 23 || pre_previous[pre_previous.size() - 1] == 24 || pre_previous[pre_previous.size() - 1] == 25)pre_previous.pop_back();						
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 11 || pre_previous[pre_previous.size() - 1] == 12) person = 12;
							else if (pre_previous[pre_previous.size() - 1] == 14 || pre_previous[pre_previous.size() - 1] == 15)person = 14;
							else person = 17;
						}//爸爸
						else {
							if (pre_previous[pre_previous.size() - 1] == 11 || pre_previous[pre_previous.size() - 1] == 12) person = 11;
							else if (pre_previous[pre_previous.size() - 1] == 14 || pre_previous[pre_previous.size() - 1] == 15)person = 15;
							else person = 16;
						}//媽媽
					}//表兄弟姊妹
					else if (previous == 34 || previous == 35) {
						while (pre_previous[pre_previous.size() - 1] == 34|| pre_previous[pre_previous.size() - 1] == 35)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 26 || pre_previous[pre_previous.size() - 1] == 27) person = 26;
							else if (pre_previous[pre_previous.size() - 1] == 28 || pre_previous[pre_previous.size() - 1] == 29)person = 28;
							else if (pre_previous[pre_previous.size() - 1] == 48 || pre_previous[pre_previous.size() - 1] == 49)person = 48;
							else person = 50;
						}//爸爸
						else {
							if (pre_previous[pre_previous.size() - 1] == 26 || pre_previous[pre_previous.size() - 1] == 27) person = 27;
							else if (pre_previous[pre_previous.size() - 1] == 28 || pre_previous[pre_previous.size() - 1] == 29)person = 29;
							else if (pre_previous[pre_previous.size() - 1] == 48 || pre_previous[pre_previous.size() - 1] == 49)person = 49;
							else person = 51;
						}//媽媽
					}//姪子女
					else if (previous == 36 || previous == 37) {
						while (pre_previous[pre_previous.size() - 1] == 36 || pre_previous[pre_previous.size() - 1] == 37)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 31 || pre_previous[pre_previous.size() - 1] == 30) person = 31;
							else if (pre_previous[pre_previous.size() - 1] == 33 || pre_previous[pre_previous.size() - 1] == 32)person = 33;
							else if (pre_previous[pre_previous.size() - 1] == 53 || pre_previous[pre_previous.size() - 1] == 52)person = 53;
							else if (pre_previous[pre_previous.size() - 1] == 55 || pre_previous[pre_previous.size() - 1] == 54)person = 55;
							else if (pre_previous[pre_previous.size() - 1] == 59 || pre_previous[pre_previous.size() - 1] == 60)person = 59;
							else if (pre_previous[pre_previous.size() - 1] == 61 || pre_previous[pre_previous.size() - 1] == 62)person = 61;
							else if (pre_previous[pre_previous.size() - 1] == 64 || pre_previous[pre_previous.size() - 1] == 63)person = 64;
							else person = 66;
						}//爸爸
						else {
							if (pre_previous[pre_previous.size() - 1] == 31 || pre_previous[pre_previous.size() - 1] == 30) person = 30;
							else if (pre_previous[pre_previous.size() - 1] == 33 || pre_previous[pre_previous.size() - 1] == 32)person = 32;
							else if (pre_previous[pre_previous.size() - 1] == 53 || pre_previous[pre_previous.size() - 1] == 52)person = 52;
							else if (pre_previous[pre_previous.size() - 1] == 55 || pre_previous[pre_previous.size() - 1] == 54)person = 54;
							else if (pre_previous[pre_previous.size() - 1] == 59 || pre_previous[pre_previous.size() - 1] == 60)person = 60;
							else if (pre_previous[pre_previous.size() - 1] == 61 || pre_previous[pre_previous.size() - 1] == 62)person = 62;
							else if (pre_previous[pre_previous.size() - 1] == 64 || pre_previous[pre_previous.size() - 1] == 63)person = 63;
							else person = 65;
						}//媽媽
					}//外甥 女
					else if (previous == 38 || previous == 42) {
						if (i == 0) {
							if (sex==2) person = 0;						
							else person = 45;
						}//爸爸
						else {
							if (sex == 1) person = 0;
							else person = 56;
						}//媽媽
					}//兒子女兒
					else if (previous == 46 || previous == 47) {
						if (i == 6) {
							if (s.find(u8"年輕") != -1) person = 50;
							else person = 48;
						}//兒子
						else {
							if (s.find(u8"年輕") != -1) person = 54;
							else person = 52;
						}//女兒
					}//夫父夫母
					else if (previous == 57 || previous == 58) {
						if (i == 6) {
							if (s.find(u8"年輕") != -1) person = 61;
							else person = 59;
						}//兒子
						else {
							if (s.find(u8"年輕") != -1) person = 65;
							else person = 63;
						}//女兒
					}//妻父妻母
				}
				pre_previous.push_back(previous);				
				previous = person;
			}			
			/*move to the next word*/
			f = pos + 3;
			if (pos != -1)pos++;
			s = input;
		 } while (pos != -1);
		 cout << out_family[person] << endl;
		
	}
	
	return 0;
}