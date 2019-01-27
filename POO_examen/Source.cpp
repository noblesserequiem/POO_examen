#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class lista;

class cazare
{
	int tip;
	int id_cazare;
	char nume_cazare[30];
	struct adresa {
		char numar_telefon[30], site[30], facebook[30];
	};
	adresa adr;
	bool loc_parcare;
	int nr_camere, nr_locuri, numar_cam_ocupat, pret_cazare;
	cazare *urm;
public:
	cazare(int t,int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30])
	{
		tip = t;
		id_cazare = id;
		nr_camere = nr_cam;
		nr_locuri = nr_loc;
		numar_cam_ocupat = nr_cam_oc;
		pret_cazare = pret;
		strcpy(nume_cazare, nume_c);
		strcpy(adr.numar_telefon, nr_tel);
		strcpy(adr.site, site);
		strcpy(adr.facebook, fb);
	}
	virtual void afisare()
	{
		cout << "\n----------------\n";
		cout << nume_cazare;
		cout << "\nCamera: " << id_cazare;
		cout << "\nNr cam: " << nr_camere;
		cout << "\nNr loc: " << nr_locuri;
		cout << "\nPret: " << pret_cazare;

	}
	friend class lista;
};

class hotel :public cazare
{
	enum dotari { piscina, restaurant, sala_conferinte, sala_sport };
	dotari dot1, dot2, dot3;
	int nr_stele;
public:
	hotel(int d1, int d2, int d3, int nr_st,int t, int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30]) :cazare(t,id, nr_cam, nr_loc, nr_cam_oc, pret, nume_c, nr_tel, site, fb)
	{
		dot1 = static_cast<dotari>(d1);
		dot2 = static_cast<dotari>(d2);
		dot3 = static_cast<dotari>(d3);
		nr_stele = nr_st;

	}
	void afisare()
	{
		cazare::afisare();
		cout << "\nDotari: " << dot1 << " " << dot2 << " " << dot3;
		cout << "\nStele: " << nr_stele;
	}
	friend class lista;
};

class pensiune :public cazare
{
	int nr_margarete;
	bool bb;
public:
	pensiune(int nr_marg, bool b,int t, int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30]) :cazare(t,id, nr_cam, nr_loc, nr_cam_oc, pret, nume_c, nr_tel, site, fb)
	{
	nr_margarete = nr_marg;
	bb = b;
	}
	void afisare()
	{
		cazare::afisare();
		cout << "\n Nr margarete: " << nr_margarete;
		cout << "\n BB: " << bb;
	}
	friend class lista;
};
class MyException
{
public:
	int var;
	char errorcode[30];
	MyException()
	{
		*errorcode = 0;
		var = 0;
	}
	MyException(char *er, int v)
	{
		strcpy(errorcode, er);
		var = v;
	}
};
class lista
{
public:
	cazare *head;
	void adaugare(cazare *a);
	void afisare();
	void stergere(char nume[30]);
};
void lista::adaugare(cazare *a)
{
	cazare *p;
	p = head;
	if (p == NULL)
	{
		head = a;
	}
	else
	{
		if (strcmp(a->nume_cazare, head->nume_cazare) < 0)
		{
			a->urm = head;
			head = a;
		}
		else
		{
			while (p->urm != NULL && strcmp(p->urm->nume_cazare, a->nume_cazare) < 0)
				p = p->urm;
			a->urm = p->urm;
			p->urm = a;
		}
	}
}
void lista::afisare()
{
	int subd;
	cout << "\n1.Hotel\n2.Pensiune";
	cin >> subd;
	cazare *p;
	p = head;
	while (p != NULL)
	{
		if (p->tip == subd)
			p->afisare();
		p = p->urm;
	}

}
void introducere(lista &l, int t,int id)
{
	cazare *p;
	char nume_cazare[30], nr_tel[30], site[30], fb[30];
	cout << "\nNume cazare: "; cin >> nume_cazare;
	cout << "Nr_Tel: "; cin >> nr_tel;
	cout << "Site: "; cin >> site;
	cout << "Fb: "; cin >> fb;
	int nr_cam, nr_loc, nr_cam_oc, pret;
	cout << "Nr camere: "; cin >> nr_cam;
	cout << "Nr locuri: "; cin >> nr_loc;
	cout << "Nr camere oc: "; cin>>nr_cam_oc;
	cout << "Pret: "; cin >> pret;
	if (t == 1)
	{
		int d1, d2, d3, nr_stele;
		cout << "\n3 dotari max\n0.piscina\n1.restaurant\n2.sala conf\n3.sala sport\n"; cin >> d1 >> d2 >> d3;
		try {
			cout << "Nr stele: "; cin >> nr_stele;
			if (nr_stele > 7)
				throw MyException((char*)"Nr stele<7", nr_stele);
		}
		catch (MyException e)
		{
			do {
				cout << "Nr_stele: ";
				cin >> nr_stele;
			} while (nr_stele > 7);
		}
		hotel *h = new hotel(d1, d2, d3, nr_stele, t, id, nr_cam, nr_loc, nr_cam_oc, pret, nume_cazare, nr_tel, site, fb);
		p = h;
		l.adaugare(p);
	}
	if (t == 2)
	{
		int nr_marg;
		bool bb;
		try
		{
			cout << "Nr margarete: "; cin >> nr_marg;
			if (nr_marg > 5)
				throw MyException((char*)"Marg>5", nr_marg);
		}
		catch (MyException e)
		{
			do {
				cout << "Nr marga: ";
				cin >> nr_marg;
			} while (nr_marg > 5);
		}
		cout << "BB ?ceva?: "; cin >> bb;
		pensiune *h = new pensiune(nr_marg, bb, t, id, nr_cam, nr_cam, nr_cam_oc, pret, nume_cazare, nr_tel, site, fb);
		p = h;
		l.adaugare(p);
	}
}
void lista::stergere(char nume[30])
{
	cazare *p,*aux;
	p = head;
	if (strcmp(head->nume_cazare, nume) == 0)
	{
		aux = head;
		head = head->urm;
		free(aux);
	}
	else
	{
		while (p->urm != NULL)
		{

			if (strcmp(p->urm->nume_cazare, nume) == 0)
			{
				aux = p->urm;
				p->urm = p->urm->urm;
				free(aux);
			}
			if(p->urm)
			p = p->urm;
		}
	}
}
int main()
{
	int opt,id=-1,t;
	lista l;
	l.head = NULL;
	do {
		cout << "\n1.adauga\n2.afisare\n";
		cout << "\nopt= "; cin >> opt;
		switch (opt)
		{
		case 1: {
			id++;
			cout << "\n1.hotel\n2.pensiune\n";
			cin >> t;
			introducere(l, t, id);
			break;
		}
		case 2: {
			l.afisare(); break;
				}
		case 3: {
			char nume[30];
			cout << "nume de sters: ";
			cin >> nume;
			l.stergere(nume);
			break;
		}
		case 5: {
			exit(0); break; 
		}
		default: break;
		}
	
	} while (opt != 5);
	return 0;
}