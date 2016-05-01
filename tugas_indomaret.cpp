#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <windows.h>
#include "tabel.h"
#include "urut.h"

using namespace std;

struct indomaret
{
	string kode_barang,nama_barang,kode_karyawan,nama_karyawan,kadaluarsa;
   long harga,volume,stok_barang,jumlah,total_penjualan,total_semua;
}toko[99],transaksi[99],laporan[99];

//==================================================================================================================================================================
//deklarasi variabel global

string masuk;  //untuk menampung login
string tampung_total_penjualan;
short int n=0; //untuk indeks barang
short int t=0; //untuk indeks transaksi
short int m=0; //untuk indeks karyawan
short int l=0; //untuk indeks laporan
int ketemu; //untuk indeks nama barang dan harga yang sudah ditemukan
long jumlah_semua;  //mentotal semua penjualan untuk laporan
bool kondisi_login;
long stok_info;

//==================================================================================================================================================================
//prototype fungsi
bool validasi_kode_barang(string kode);

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x, int y); 

void WaitKey();

//==================================================================================================================================================================
string login()
{
   register string kode;
   register int i;
   bool ketemu=0;
	static bool login=0; kembali1:  i=0;

   if(login==0)
	{
   	cout<<"Masukkan kode karyawan : "; cin>>kode;
      while(i<m)
   	{
   		if(kode == toko[i].kode_karyawan)
      	{
      		ketemu=1; laporan[l].nama_karyawan=toko[i].nama_karyawan; break;
      	}
      	i++;
   	}
   	if(ketemu == 0)
   	{
   		cout<<"Kode yang anda masukkan salah, silahkan coba lagi"; system("pause");
      	system("cls"); goto kembali1;
   	}
   	else
   	{
   		cout<<"Kode benar, selamat datang "<<toko[i].nama_karyawan<<endl; system("pause");
      }
   }

   return toko[i].nama_karyawan;
}
//==================================================================================================================================================================
string nama_barang(string kode)
{

   if(n>0)
		for(int i=0; i<n; i++)
   	{
   		if(kode == toko[i].kode_barang)
      	{
      		kode=toko[i].nama_barang; ketemu=i; break;
      	}
   	}
   
   return kode;
}
//==================================================================================================================================================================
bool cek_stok(string kode,int volume)
{
   bool cek=1;
	if(n>0)
   {
		for(int i=0; i<n; i++)
   	{
   		if(kode == toko[i].kode_barang)
      	{
            stok_info=toko[i].stok_barang;
         	if(volume <= toko[i].stok_barang)
            {

            	toko[i].stok_barang = toko[i].stok_barang - volume;
               cek=1;

               break;
            }
            else
            {
            		cek=0; break;
            }
            
      	}
   	}
   }
   return cek;
}
//==================================================================================================================================================================
void transaksi_pembayaran()
{
	char tanya; bool cek; int f=0; long int total_penjualan; static long int total_semua;
   string nama_barang1;
   char volume[3];
   bool hasil;

   //pembuatan tabel
   tabel_transaksi(f,masuk);

   kembali2:

   total_penjualan=0;

   gotoxy(41,8+f); cout<<"Total Penjualan : ";gotoxy(63,8+f); cout<<"Rp "<<transaksi[1].total_penjualan;

   //membuat garis bawah
   tabel_transaksi(f,masuk);

   //melakukan pembersihan apabila kode yang diinputkan tidak ada dalam daftar entry barang
   gotoxy(3,6+f); cout<<setfill(' ')<<setw(11)<<endl; gotoxy(3,6+f); cin>>transaksi[t].kode_barang;


   //melakukan pengecekan kode barang dengan yang ada pada daftar entry barang
   cek=validasi_kode_barang(transaksi[t].kode_barang);
   if(cek==1)
   {
   	gotoxy(3,9+f); cout<<"Kode yang anda masukkan tidak ada dalam daftar";
      system("pause"); gotoxy(3,9+f); cout<<setfill(' ')<<setw(70)<<endl;
      goto kembali2;
   }
   nama_barang1=nama_barang(transaksi[t].kode_barang);
   transaksi[t].nama_barang=nama_barang1;

   gotoxy(21,6+f); cout<<toko[ketemu].nama_barang;
   gotoxy(37,6+f); cout<<toko[ketemu].harga;

   cek_kembali:
   gotoxy(53,6+f);gets(volume);transaksi[t].volume=atoi(volume);

   hasil=cek_stok(transaksi[t].kode_barang,transaksi[t].volume);
   if(hasil==0)
   {
      gotoxy(3,9+f); cout<<"Stok barang hanya "<<stok_info; system("pause");
      gotoxy(3,9+f); cout<<setfill(' ')<<setw(77)<<endl;
   	gotoxy(53,6+f);cout<<setfill(' ')<<setw(7)<<endl;
   	goto cek_kembali;
   }
   //rumus jumlah harga
   transaksi[t].jumlah=toko[ketemu].harga * transaksi[t].volume;
   gotoxy(63,6+f); cout<<"Rp "<<transaksi[t].jumlah;

   //melakukan perhitungan total dari jumlah harga
	total_penjualan=total_penjualan + transaksi[t].jumlah;
   total_semua=total_semua + transaksi[t].jumlah;
   gotoxy(63,8+f); cout<<"Rp "<<total_semua<<endl;

   //baris pengisian laporan
   laporan[l].kode_barang=transaksi[t].kode_barang;
   laporan[l].nama_barang=transaksi[t].nama_barang;
   laporan[l].volume=transaksi[t].volume;
   laporan[l].jumlah=transaksi[t].jumlah;
   laporan[l].nama_karyawan=masuk;


   //total semua penjualan untuk laporan
   jumlah_semua=jumlah_semua+total_penjualan;
   laporan[l].total_semua=jumlah_semua;
   t++; f++; l++;

   gotoxy(3,9+f); cout<<"Tekan y untuk memasukkan data lagi : "; cin>>tanya;
   if(tanya == 'y' || tanya == 'Y')
   {
      //penghapusan karakter pada baris horisontal
      gotoxy(2,6+f); cout<<setfill(' ')<<setw(77)<<endl;
   	gotoxy(3,9+f); cout<<setfill(' ')<<setw(77)<<endl;
      gotoxy(1,10+f); cout<<setfill(' ')<<setw(77)<<endl;
      goto kembali2;
   }
   total_semua=0;
}
//==================================================================================================================================================================
void update_data()
{
   bool cek_dulu;
   string kode_barang_update;

   kembali:
   cout<<"Masukkan kode barang yang ingin anda update : "; cin>>kode_barang_update;
	cek_dulu=validasi_kode_barang(kode_barang_update);
   if(cek_dulu == 0)
   {
   	cout<<"Kode yang anda masukkan tidak ada dalam entry"; system("pause");
      system("cls");
      goto kembali;
   }

}
//==================================================================================================================================================================
void laporan_penjualan()
{
   //pembuatan tabel
   int v;
   v=l;
   tabel_laporan(v);

   for(int i=0; i<l; i++)
   {
     	//pencetakan laporan
    	gotoxy(3,6+i); cout<<laporan[i].nama_karyawan;
     	gotoxy(21,6+i); cout<<laporan[i].nama_barang;
     	gotoxy(37,6+i); cout<<laporan[i].volume;
     	gotoxy(47,6+i); cout<<"Rp "<<laporan[i].jumlah;
   }
   gotoxy(24,7+l); cout<<"Total Penjualan : "; gotoxy(47,7+l); cout<<"Rp "<<jumlah_semua;
   system("pause");
}
//==================================================================================================================================================================

bool validasi_kode_barang(string kode)
{
   bool valid=1;

   if(n>0)
   {
		for(int i=0; i<n; i++)
   	{
   		if(kode == toko[i].kode_barang)
      	{
      		valid = 0; break;
      	}
   	}
   }
   else
   	valid=1;

   return valid;
}
//==================================================================================================================================================================
void entry_barang()
{
   static int i=0;
   bool validation;
   char harga[10];
   char stok[10];
   char tanya;

   kembali2:
   tabel_entry_barang(i,n);

   for(int j=0; j<n; j++)
   {
      //pencetakan inputan sebelumnya
      gotoxy(3,5+j); cout<<toko[j].kode_barang;
      gotoxy(17, 5+j); cout<<toko[j].nama_barang;
      gotoxy(42, 5+j); cout<<"Rp "<<toko[j].harga;
      gotoxy(59,5+j); cout<<toko[j].stok_barang<<endl;
   }

   back:

   gotoxy(3,5+i); cout<<setfill(' ')<<setw(13)<<endl; gotoxy(3,5+i); cin>>toko[n].kode_barang;
   validation=validasi_kode_barang(toko[n].kode_barang);
   if(validation == 0)
   {
      gotoxy(3,9+i); cout<<"kode barang tidak boleh sama"; system("pause");
      gotoxy(3,9+i); cout<<setfill(' ')<<setw(77)<<endl;
   	goto back;
   }
   gotoxy(17,5+i); getline(cin,toko[n].nama_barang); gotoxy(17,5+i); gotoxy(42,5+i); cout<<"Rp "; gets(harga); toko[n].harga=atol(harga);
   gotoxy(59,5+i); gets(stok); toko[n].stok_barang=atoi(stok); gotoxy(65,5+i); getline(cin,toko[n].kadaluarsa);

   i++; n++;

   gotoxy(3,9+i); cout<<"Tekan y untuk memasukkan data lagi : "; cin>>tanya;
   if(tanya == 'y' || tanya == 'Y')
   {
      //penghapusan karakter pada baris horisontal
      gotoxy(2,5+i); cout<<setfill(' ')<<setw(88)<<endl;
   	gotoxy(3,9+i); cout<<setfill(' ')<<setw(88)<<endl;
      gotoxy(1,10+i); cout<<setfill(' ')<<setw(88)<<endl;
      goto kembali2;
   }
}
//==================================================================================================================================================================
void laporan_stok()
{
	for(int i=0; i<n; i++)
   {
   	cout<<toko[i].stok_barang;
   }
   system("pause");
}
//==================================================================================================================================================================
bool validasi_kode_karyawan(string kode)
{
   bool valid=1;

   if(m>0)
		for(int i=0; i<m; i++)
   	{
   		if(kode == toko[i].kode_karyawan)
      	{
      		valid = 0; break;
      	}
   	}
   else
   	valid=1;

   return valid;
} 
//==================================================================================================================================================================
void entry_karyawan()
{
   static int i=0;
   bool validation;
   char tanya;

   kembali2:
   tabel_entry_karyawan(i,m);

   for(int j=0; j<m; j++)
   {


      //pencetakan inputan sebelumnya
   	gotoxy(3,5+j); cout<<toko[j].kode_karyawan;
      gotoxy(19, 5+j); cout<<toko[j].nama_karyawan;
   }

   back:

   //input kode karyawan
   gotoxy(3,5+i); cout<<setfill(' ')<<setw(16)<<endl;
   gotoxy(3,5+i); cin>>toko[m].kode_karyawan;

   //pengecekan kode karyawan apabila ada yang sama
   validation=validasi_kode_karyawan(toko[m].kode_karyawan);
   if(validation == 0)
   {
      gotoxy(3,9+i); cout<<"kode barang tidak boleh sama"; system("pause");
      gotoxy(3,9+i); cout<<setfill(' ')<<setw(77)<<endl;
   	goto back;
   }
   gotoxy(19,5+i); getline(cin,toko[m].nama_karyawan);
   i++; m++;

   gotoxy(3,9+i); cout<<"Tekan y untuk memasukkan data lagi : "; cin>>tanya;
   if(tanya == 'y' || tanya == 'Y')
   {
      //penghapusan karakter pada baris horisontal
      gotoxy(2,5+i); cout<<setfill(' ')<<setw(88)<<endl;
   	gotoxy(3,9+i); cout<<setfill(' ')<<setw(88)<<endl;
      gotoxy(1,10+i); cout<<setfill(' ')<<setw(88)<<endl;
      goto kembali2;
   }
}
//==================================================================================================================================================================
void view_entry_barang()
{
	tabel_entry_barang(n-1,n);

   for(int j=0; j<n; j++)
   {
      //pencetakan inputan sebelumnya
      gotoxy(3,5+j); cout<<toko[j].kode_barang;
      gotoxy(17, 5+j); cout<<toko[j].nama_barang;
      gotoxy(42, 5+j); cout<<"Rp "<<toko[j].harga;
      gotoxy(59,5+j); cout<<toko[j].stok_barang;
      gotoxy(65,5+j); cout<<toko[j].kadaluarsa<<endl;
   }
   system("pause");
}
//==================================================================================================================================================================
void view_entry_karyawan()
{
	tabel_entry_karyawan(m-1,m);

   for(int j=0; j<m; j++)
   {
      //pencetakan inputan sebelumnya
   	gotoxy(3,5+j); cout<<toko[j].kode_karyawan;
      gotoxy(19, 5+j); cout<<toko[j].nama_karyawan;
   }
   system("pause");
}
//==================================================================================================================================================================
void menu_barang()
{
   char *pilih1=new char;
   int pilih;

   kembali:
	cout<<"1. Update data"<<endl;
   cout<<"2. kembali ke menu utama"<<endl;

   cin>>pilih1;
   pilih=atoi(pilih1);

   switch(pilih)
   {
   	case 1 : system("cls"); update_data(); system("cls");
      case 2 : system("cls"); break;
   	default: cout<<"Pilihan salah"; system("pause"); system("cls"); goto kembali;
   }
}
//==================================================================================================================================================================
void entry()
{
   int pilih;
   char *pilih2=new char;

   entry:

	cout<<"1. Entry Barang"<<endl;
   cout<<"2. Entry Karyawan"<<endl;
   cout<<"3. Lihat data barang"<<endl;
   cout<<"4. Lihat data karyawan"<<endl;
   cout<<"5. Kembali ke menu"<<endl;
   cout<<endl<<endl<<"Pilihan : "; gets(pilih2);

   pilih=atoi(pilih2);
   switch(pilih)
   {
   		case 1 : system("cls"); entry_barang(); system("cls"); goto entry;
      	case 2 : system("cls"); entry_karyawan(); system("cls"); goto entry;
      	case 3 : system("cls"); view_entry_barang(); system("cls"); goto entry;
      	case 4 : system("cls"); view_entry_karyawan(); system("cls"); goto entry;
      	case 5 : system("cls"); break;
      	default: cout<<"Pilihan salah"; system("pause"); system("cls"); goto entry;
   }
}
//==================================================================================================================================================================
int main()
{
   int pilihan;
   char *pilihan2=new char;

   kembali:

	cout<<"||MENU PILIHAN||"<<endl;
   cout<<"1. Entry barang dan karyawan"<<endl;
   cout<<"2. Transaksi penjualan"<<endl;
   cout<<"3. Laporan penjualan"<<endl;
   cout<<"4. Laporan stok barang"<<endl;
   cout<<"5. Exit"<<endl;
   cout<<endl<<"Pilihan : "; gets(pilihan2);

   pilihan=atoi(pilihan2);
   switch(pilihan)
   {
   		case 1 : system("cls"); entry(); system("cls"); goto kembali;
      	case 2 : system("cls");
      				if(m<1 || n<1)
               		{
                     	cout<<"Anda belum menginputkan data barang atau data karyawan"; system("pause");
                     	system("cls");
                     	goto kembali;
                  	}
              		system("cls"); masuk=login();
      
              		system("cls"); transaksi_pembayaran(); system("cls"); goto kembali;
      	case 3 : system("cls");
        	       if(t<1)
            	   	{
               			cout<<"Anda belum membuat transaksi"; system("pause");
                    	 system("cls");
                     	goto kembali;
                 	}
       				laporan_penjualan(); system("cls"); goto kembali;
      	case 4 : system("cls"); laporan_stok(); goto kembali;
      	case 5 : exit(0);
      	default : cout<<"Pilihan salah bro"; system("pause"); system("cls"); goto kembali;
   }
}


//==================================================================================================================================================================
//fungsi gotoxy
//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//COORD CursorPosition;

void gotoxy(int x, int y) 
{ 
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

void WaitKey()
{
   while (_kbhit()) _getch(); // Empty the input buffer
   _getch(); // Wait for a key
   while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
}

