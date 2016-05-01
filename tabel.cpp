#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <cstring.h>

void tabel_transaksi(int v=0,string masuk=' ')
{
   //header
   gotoxy(3,1); cout<<"Status Login : "<<masuk;
   gotoxy(2,3); cout<<setfill('=')<<setw(77)<<endl;
	gotoxy(2,4); cout<<char(179); gotoxy(18,4); cout<<char(179); gotoxy(35,4); cout<<char(179); gotoxy(51,4); cout<<char(179); gotoxy(61,4); cout<<char(179); gotoxy(77,4); cout<<char(179);
   gotoxy(5,4); cout<<"Kode Barang"; gotoxy(21,4); cout<<"Nama Barang"; gotoxy(37,4); cout<<"Harga Satuan"; gotoxy(53,4); cout<<"volume"<<endl; gotoxy(63,4); cout<<"Jumlah Harga"<<endl;
   gotoxy(2,5); cout<<char(179); gotoxy(3,5); cout<<setfill('=')<<setw(75)<<endl; gotoxy(77,5); cout<<char(179);

   //pembuatan garis batas antar kolom
   gotoxy(2,6+v); cout<<char(179);
   gotoxy(18,6+v); cout<<char(179);
   gotoxy(35,6+v); cout<<char(179);
   gotoxy(51,6+v); cout<<char(179);
   gotoxy(61,6+v); cout<<char(179);
   gotoxy(77,6+v); cout<<char(179);

   //footer
   gotoxy(2,7+v); cout<<setfill('=')<<setw(77)<<endl;
}
//==================================================================================================================================================================
extern "C++" void tabel_laporan(int v,int l)
{
   //header
   gotoxy(2,3); cout<<setfill('=')<<setw(61)<<endl;
	gotoxy(2,4); cout<<char(179); gotoxy(18,4); cout<<char(179); gotoxy(35,4); cout<<char(179); gotoxy(45,4); cout<<char(179); gotoxy(61,4); cout<<char(179);
   gotoxy(5,4); cout<<"Kode Barang"; gotoxy(21,4); cout<<"Nama Barang"; gotoxy(37,4); cout<<"Volume"; gotoxy(47,4); cout<<"Jumlah harga"<<endl;
   gotoxy(2,5); cout<<char(179); gotoxy(3,5); cout<<setfill('=')<<setw(59)<<endl; gotoxy(61,5); cout<<char(179);

   for(int i=0; i<l; i++)
   {
   	//pembuatan garis batas antar kolom
   		gotoxy(2,6+i); cout<<char(179);
   		gotoxy(18,6+i); cout<<char(179);
   		gotoxy(35,6+i); cout<<char(179);
   		gotoxy(45,6+i); cout<<char(179);
   		gotoxy(61,6+i); cout<<char(179);
   }

   //footer
   gotoxy(2,6+v); cout<<setfill('=')<<setw(61)<<endl;
}
//==================================================================================================================================================================
extern "C++" void tabel_entry_barang(int h,int n)
{
	//header
	gotoxy(24,1);cout<<"ENTRY BARANG"<<endl<<endl;
   gotoxy(2,2);cout<<setfill('=')<<setw(64)<<endl;
   gotoxy(2,3);cout<<char(179); gotoxy(16,3);cout<<char(179); gotoxy(41,3);cout<<char(179); gotoxy(57,3);cout<<char(179); gotoxy(64,3); cout<<char(179);
   gotoxy(3,3);cout<<"Kode Barang"; gotoxy(24,3);cout<<"Nama Barang"; gotoxy(47,3);cout<<"Harga"; gotoxy(59,3); cout<<"Stok";
   gotoxy(2,4);cout<<char(179); gotoxy(16,4);cout<<char(179); gotoxy(41,4);cout<<char(179); gotoxy(57,4);cout<<char(179); gotoxy(64,3); cout<<char(179);
   gotoxy(3,4);cout<<setfill('=')<<setw(63)<<endl;


   gotoxy(2,5+h); cout<<char(179);
  	gotoxy(16,5+h); cout<<char(179);
  	gotoxy(41,5+h); cout<<char(179);
  	gotoxy(57,5+h); cout<<char(179);
  	gotoxy(64,5+h); cout<<char(179);

   for(int i=0; i<n; i++)
   {

       //pembuatan garis pembatas vertikal
   	gotoxy(2,5+i); cout<<char(179);
   	gotoxy(16,5+i); cout<<char(179);
   	gotoxy(41,5+i); cout<<char(179);
   	gotoxy(57,5+i); cout<<char(179);
   	gotoxy(64,5+i); cout<<char(179);
   }


   //footer
   gotoxy(2,6+h); cout<<setfill('=')<<setw(64)<<endl;
}
//==================================================================================================================================================================
extern "C++" void tabel_entry_karyawan(int h,int m)
{
	//header
   gotoxy(2,2); cout<<setfill('=')<<setw(42)<<endl;
   gotoxy(2,3); cout<<char(179); gotoxy(18,3); cout<<char(179); gotoxy(42,3); cout<<char(179);
   gotoxy(4,3); cout<<"Kode Karyawan"; gotoxy(24,3); cout<<"Nama Karyawan";
   gotoxy(2,4); cout<<char(179); gotoxy(3,4); cout<<setfill('=')<<setw(40)<<endl; gotoxy(42,4); cout<<char(179);

   //pembuatan garis pembatas vertikal
   gotoxy(2,5+h); cout<<char(179);
   gotoxy(18,5+h); cout<<char(179);
   gotoxy(42,5+h); cout<<char(179);

   for(int i=0; i<m; i++)
   {
   	//pembuatan garis vertikal pembatas
      gotoxy(2,5+i); cout<<char(179);
      gotoxy(18,5+i); cout<<char(179);
      gotoxy(42,5+i); cout<<char(179);
   }
   //footer
   gotoxy(2,6+h); cout<<setfill('=')<<setw(42)<<endl;
}