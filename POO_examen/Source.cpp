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
	struct date_contact {
		char numar_telefon[30], site[30], facebook[30];
	};
	date_contact date;
	bool loc_parcare;
	int nr_camere, nr_locuri, numar_cam_ocupat, pret_cazare;
	cazare *urm;
public:
	cazare(int t,int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30],bool loc_p)
	{
		tip = t;
		loc_parcare = loc_p;
		id_cazare = id;
		nr_camere = nr_cam;
		nr_locuri = nr_loc;
		numar_cam_ocupat = nr_cam_oc;
		pret_cazare = pret;
		strcpy(nume_cazare, nume_c);
		strcpy(date.numar_telefon, nr_tel);
		strcpy(date.site, site);
		strcpy(date.facebook, fb);
	}
	virtual void afisare()
	{
		cout << "\n----------------\n";
		cout << nume_cazare;
		cout << "\nCamera: " << id_cazare;
		cout << "\nNr cam: " << nr_camere;
		cout << "\nNr loc: " << nr_locuri;
		cout << "\nNr camere ocupate: " << numar_cam_ocupat;
		cout << "\nPret: " << pret_cazare;

	}
	void operator+(const int nr)
	{
		this->numar_cam_ocupat = this->numar_cam_ocupat + nr;
	}
	void operator-(const int nr)
	{
		this->numar_cam_ocupat = this->numar_cam_ocupat - nr;
	}
	friend class lista;
};

class hotel :public cazare
{
	enum dotari { piscina, restaurant, sala_conferinte, sala_sport };
	dotari dot1, dot2, dot3;
	int nr_stele;
public:
	hotel(int d1, int d2, int d3, int nr_st,int t, int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30],bool loc_p) :cazare(t,id, nr_cam, nr_loc, nr_cam_oc, pret, nume_c, nr_tel, site, fb,loc_p)
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
	pensiune(int nr_marg, bool b,int t, int id, int nr_cam, int nr_loc, int nr_cam_oc, int pret, char nume_c[30], char nr_tel[30], char site[30], char fb[30],bool loc_p) :cazare(t,id, nr_cam, nr_loc, nr_cam_oc, pret, nume_c, nr_tel, site, fb,loc_p)
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
	void cauta(char nrtel[30], char site[30]);
	void modifica_camere(int t,int camere_oc, int nr);
	
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
	bool loc_p;
	cout << "Loc parcare (1.da, 0.nu ): "; cin >> loc_p;
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
		hotel *h = new hotel(d1, d2, d3, nr_stele, t, id, nr_cam, nr_loc, nr_cam_oc, pret, nume_cazare, nr_tel, site, fb,loc_p);
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
		pensiune *h = new pensiune(nr_marg, bb, t, id, nr_cam, nr_cam, nr_cam_oc, pret, nume_cazare, nr_tel, site, fb,loc_p);
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
void lista::cauta(char nrtel[30], char site[30])
{
	cazare *p;
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->date.numar_telefon, nrtel) == 0 && strcmp(p->date.site, site) == 0 && p->loc_parcare == true)
			p->afisare();
		p = p->urm;
	}
}
void lista::modifica_camere(int t,int camere_oc, int nr)
{
	cazare *p;
	p = head;
	while (p != NULL)
	{
		if (p->numar_cam_ocupat==camere_oc&&t==1)
		{
			 *p+nr;
		}
		if (p->numar_cam_ocupat == camere_oc && t == 2)
		{
			*p - nr;
		}
		p = p->urm;
	}
}
int main()
{
	int opt,id=-1,t;
	lista l;
	l.head = NULL;
	do {
		cout << "\n====================================\n1.adauga\n2.afisare\n3.stergere dupa nume cazare\n4.afisare dupa nr telefon/site/loc parcare\n5+6.adaugare camere ocupate dupa camera ocupate(supraincarcare +) same dar cu -\n7.exit\n===============================\n";
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
		case 4: {
			char nrtel[30], site[30]; cout << "\nnr tel de cautat: "; cin >> nrtel;
			cout << "site cautare: "; cin >> site;
			l.cauta(nrtel, site);
			break;

				}
		case 5: {
			int nr;int camere_oc;
			cout << "Nr camere oc: "; cin >> camere_oc;
			cout << "Nr camere ocupate de modificat: "; cin >> nr;
			int t;
			cout << "\n1.+\n2.-"; cin >> t;
			l.modifica_camere(t,camere_oc, nr);
			break;
			}
		case 7: {
			exit(0); break; 
		}
		default: break;
		}
	
	} while (opt != 7);
	return 0;
}