#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
#define scale 1000


map<char, int> appear;
string haff_code;
//根节点永远是下标为255的节点
struct node
{
	char info;
	int father;
	int left;
	int right;
	int weight;
	node() {
		father = left = right = -1;
		info = 0;
		weight = 0;
	}

} haff[scale];
int NYT;//NYT 的编号
void creat() {
	NYT = scale-1;
}
int find(int weight) {
	for (size_t i =scale-1 ; i >= 0; i--)
	{
		if (haff[i].weight == weight)
			return i;
	}
	return -1;
}
void adjust_shot(int loc) {
	//cout << "in shot" << endl;
	//cout << "loc is:" << loc << endl;
	//node temp;
	int te;
	char ex;
	te=find(haff[loc].weight);
	//int t2 = te;
	if (te != loc && haff[loc].father!=te) {
		//cout << "in take place";
		//cout << endl << "loc: " << te << endl;
		//cout << "dsa";
		/*
		if (t2 == haff[haff[t2].father].left) {
			haff[haff[t2].father].left = loc;
		}
		else {
			cout << "ringht 1\n";
			haff[haff[t2].father].right = loc;
		}
		if (loc == haff[haff[loc].father].left) {
			haff[haff[loc].father].left = t2;
		}
		else {
			haff[haff[loc].father].right = t2;

		}*/
		/*
		ex = haff[t2].info;
		haff[t2].info = haff[loc].info;
		haff[loc].info = ex;
		*/
		/*
		te = haff[t2].father;
		haff[t2].father = haff[loc].father;
		haff[loc].father = te;
		*/
		int left = haff[loc].left;
		int right = haff[loc].right;
		char info = haff[loc].info;
		if (appear.count(haff[loc].info))
		{
			appear[haff[loc].info] = te;
		}
		if (appear.count(haff[te].info))
		{
			appear[haff[te].info] = loc;
		}
		
		if (haff[loc].left != -1)
		{
			haff[haff[loc].left].father = te;
		}
		if (haff[loc].right != -1)
		{
			haff[haff[loc].right].father = te;

		}
		if (haff[te].left != -1)
		{
			haff[haff[te].left].father = loc;

		}
		if (haff[te].right != -1)
		{
			haff[haff[te].right].father = loc;
		}

		haff[loc].left = haff[te].left;
		haff[loc].right = haff[te].right;
		haff[loc].info = haff[te].info;
		haff[te].right = right;
		haff[te].left = left;
		haff[te].info = info;
		//te=appear[]
		loc = te;
	}
	//loc = t2;
		 
	haff[loc].weight++;

	if(haff[loc].father!=-1)
		adjust_shot(haff[loc].father);
}
void adjust_not_shot(int NYT) {
	if (haff[haff[NYT].father].father != -1)
		adjust_shot(haff[haff[NYT].father].father);
}
void show_fist(int cur) {
	string code;
	int temp = cur;
	cout << haff[cur].info << " : " << cur << " : " << haff[cur].weight << " : ";
	for (; cur != scale-1; cur = haff[cur].father)
	{
		if (haff[haff[cur].father].right == cur)
		{
			code += '1';
		}
		else code += '0';
	}
	for (int i = 0; i < code.size()-1; i++)
	{
		cout << code[code.size() - i - 1];
		haff_code += code[code.size() - i - 1];
	}
	haff_code += haff[temp].info;
	cout << haff[temp].info;
	cout << endl;
	//code = code;
}
void show(int cur) {
	string code;

	cout << haff[cur].info << " : " << cur << " : " << haff[cur].weight+1 << " : ";
	for (; cur != scale-1; cur = haff[cur].father)
	{
		if (haff[haff[cur].father].right == cur)
		{
			code += '1';
		}
		else code += '0';
	}
	for (int i = 0; i < code.size(); i++)
	{
		haff_code += code[code.size() - i - 1];
		cout << code[code.size() - i - 1];
	}
	cout << endl;
}
void insert(char x) {
	appear[x] = NYT - 1;
	haff[NYT].weight = 1;
	haff[NYT].left = NYT - 2;
	haff[NYT].right = NYT - 1;

	haff[NYT - 1].info = x;
	haff[NYT - 1].father = NYT;
	haff[NYT - 1].weight = 1;
	//appear[x] = NYT - 1;

	NYT -= 2;
	haff[NYT].father = NYT + 2;

	show_fist(NYT + 1);

	adjust_not_shot(NYT);
}




void dy_haff() {
	char c;
	creat();
	
	

	while ((c = cin.get()) && c != EOF)
	{
		if (c=='$')
		{
			break;
		}
		if (!appear.count(c))//尚未出现
		{
			//haff[0] = haff[0]; appear[0] = appear[0];

			haff[0] = haff[0]; !appear.count(c);
			insert(c);
			haff[0] = haff[0]; !appear.count(c);

		}
		else {
			
			//haff[0] = haff[0];
			show(appear[c]);
			//haff[0] = haff[0]; !appear.count(c);
			adjust_shot(appear[c]);
			//haff[0] = haff[0]; !appear.count(c);

		}
		//cout <<haff_code<<endl;
	}
}






string result;
int nyt;
node r_haff[scale];
map<char, int> appear_for_release;

int find_realese(int weight) {
	for (size_t i = scale - 1; i >= 0; i--)
	{
		if (r_haff[i].weight == weight)
			return i;
	}
	return -1;
}
void adjust_shot_release(int loc) {
	//cout << "in shot" << endl;
	//cout << "loc is:" << loc << endl;
	//node temp;
	int te;
	char ex;
	te = find_realese(r_haff[loc].weight);
	//int t2 = te;
	if (te != loc && r_haff[loc].father != te) {
		//cout << "in take place";
		//cout << endl << "loc: " << te << endl;
		//cout << "dsa";
		/*
		if (t2 == r_haff[r_haff[t2].father].left) {
		r_haff[r_haff[t2].father].left = loc;
		}
		else {
		cout << "ringht 1\n";
		r_haff[r_haff[t2].father].right = loc;
		}
		if (loc == r_haff[r_haff[loc].father].left) {
		r_haff[r_haff[loc].father].left = t2;
		}
		else {
		r_haff[r_haff[loc].father].right = t2;

		}*/
		/*
		ex = r_haff[t2].info;
		r_haff[t2].info = r_haff[loc].info;
		r_haff[loc].info = ex;
		*/
		/*
		te = r_haff[t2].father;
		r_haff[t2].father = r_haff[loc].father;
		r_haff[loc].father = te;
		*/
		int left = r_haff[loc].left;
		int right = r_haff[loc].right;
		char info = r_haff[loc].info;
		if (appear.count(r_haff[loc].info))
		{
			appear[r_haff[loc].info] = te;
		}
		if (appear.count(r_haff[te].info))
		{
			appear[r_haff[te].info] = loc;
		}

		if (r_haff[loc].left != -1)
		{
			r_haff[r_haff[loc].left].father = te;
		}
		if (r_haff[loc].right != -1)
		{
			r_haff[r_haff[loc].right].father = te;

		}
		if (r_haff[te].left != -1)
		{
			r_haff[r_haff[te].left].father = loc;

		}
		if (r_haff[te].right != -1)
		{
			r_haff[r_haff[te].right].father = loc;
		}

		r_haff[loc].left = r_haff[te].left;
		r_haff[loc].right = r_haff[te].right;
		r_haff[loc].info = r_haff[te].info;
		r_haff[te].right = right;
		r_haff[te].left = left;
		r_haff[te].info = info;
		//te=appear[]
		loc = te;
	}
	//loc = t2;

	r_haff[loc].weight++;

	if (r_haff[loc].father != -1)
		adjust_shot_release(r_haff[loc].father);
}
void adjust_not_shot_release(int nty) {
	if (r_haff[r_haff[nty].father].father != -1)
		adjust_shot_release(r_haff[r_haff[nty].father].father);
}
void insert_for_release(char x) {
	result += x;

	appear_for_release[x] = nyt - 1;
	r_haff[nyt].weight = 1;
	r_haff[nyt].left = nyt - 2;
	r_haff[nyt].right = nyt - 1;

	r_haff[nyt - 1].info = x;
	r_haff[nyt - 1].father = nyt;
	r_haff[nyt - 1].weight = 1;

	nyt -= 2;
	r_haff[nyt].father = nyt + 2;
	adjust_not_shot_release(nyt);
}
bool is_num(char x) {
	if (x>='0'&&x<='9')
	{
		return 1;
	}
	return 0;
}
void release() {
	
	//haff_code = "b0s00d100f000g10";
	nyt = scale - 1;
	int cur;
	cur = scale - 1;//令cur等于root
	for (size_t i = 0; i < haff_code.size(); i++)
	{
		if (is_num(haff_code[i]))
		{
			if (haff_code[i] == '1')
			{

				cur = r_haff[cur].right;
				//cout << haff_code[i];
				//cout << "right\n";
				//cout << "cur:" << cur << endl;
			}
			else {
				//cout << haff_code[i];

				cur = r_haff[cur].left;
				//cout << "left\n";
				//cout << "cur:" << cur << endl;
			}
			if (appear_for_release.count(r_haff[cur].info))
			{
				//cout << haff_code[i];
				//cout << "cur:" << cur << endl;
				result += r_haff[cur].info;
				adjust_shot_release(cur);
				cur = scale - 1;//令cur等于root
				
			}
		}
		else {//发现新节点
			cur = scale - 1;//令cur等于root
			insert_for_release(haff_code[i]);
		}
	}

	cout << result;
	r_haff[0] = r_haff[0];
}