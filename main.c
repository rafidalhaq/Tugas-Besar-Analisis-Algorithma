#include <stdio.h>
#include <string.h>

typedef struct _user
{char nama[20];
int nilai;
}user;

int menu()//menampilkan menu dan menghasilkan nilai yang dimaksukkan user
    {
    int x;
    printf("\n |------ |Game Minesweeper|---------|\n\n");
    printf("|-------------|Main Menu|------------|\n\n");
    printf("1.New Game\n");
    printf("2.Highscore\n");
    printf("3.Start\n");
    printf("4.Exit\n\n");
    printf("Masukkan pilihan : ");
    scanf("%i",&x);
    while((x<1)||(x>4))
    {
        printf("Pilihan Invalid !\n");
        printf("Masukkan pilihan : \n");
        scanf("%i",&x);
    }
    printf("\n");
    return x;
    }

void cek(int board[15][15],int revealed[15][15],int x, int y)//mengecek saat board[x][y] berisi 0
{
//Kamus lokal
int i,j;
revealed[x][y]=1;

//Algoritma
   for(i=x-1;i<x+2;i++)
         {for(j=y-1;j<y+2;j++)
                              {if(i>=0&&j>=0&&i<15&&j<15)
                                 {if(revealed[i][j]==0&&board[i][j]!=0)
                                     {revealed[i][j]=1;}
                                 }
                              }
          }
   for(i=x-1;i<x+2;i++)
         {for(j=y-1;j<y+2;j++)
                              {if(i>=0&&j>=0&&i<15&&j<15)
                                 {if(revealed[i][j]==0&&board[i][j]==0)
                                     {cek(board,revealed,i,j);}
                                 }
                              }
         }


}

int klik(int board[15][15],int revealed[15][15],char kondisi[15][15])
     {
//Kamus lokal
     int a,b,x,y,q,z;

//Algoritma
      do {
         printf("X: ");
         scanf("%i",&y);
         printf("y: ");
         scanf("%i",&x);
         }while(x<1||y<1||x>15||y>15);

         x--;y--;//konfersi ke matriks yg dari 0 sampai 14
						 if(kondisi[x][y]=='F')
							 {
							 }
                         else if(board[x][y] == 9)
							{
                                    for(a=0;a<15;a++)for(b=0;b<15;b++)
                                                      {if(board[a][b]==9)revealed[a][b]=1;}
                                    z=1;

							}
                         else if(board[x][y]==0)
							 {     revealed[x][y]=1; //revealed 1 terbuka
								   cek(board,revealed,x,y);
							 }
                         else{revealed[x][y] = 1;}

                         for(a=0;a<15;a++)
                                    {for(b=0;b<15;b++)
                                         if(revealed[a][b]==1)
                                                         {switch(board[a][b])
                                                                 {
                                                                 case 0: kondisi[a][b]='0';break;
                                                                 case 1: kondisi[a][b]='1';break;
                                                                 case 2: kondisi[a][b]='2';break;
                                                                 case 3: kondisi[a][b]='3';break;
                                                                 case 4: kondisi[a][b]='4';break;
                                                                 case 5: kondisi[a][b]='5';break;
                                                                 case 6: kondisi[a][b]='6';break;
                                                                 case 7: kondisi[a][b]='7';break;
                                                                 case 8: kondisi[a][b]='8';break;
                                                                 case 9: kondisi[a][b]='#';break;
                                                                 }

                                                         }

                                    }

       q=jumlhbuka(revealed);
                      
                         if (z==1){return 1;}else if(q>=200){z=2;}else{z=0;}
                         return z;

     }
     
int jumlhbuka(int revealed[15][15],char kondisi[15][15])
   {int a,b,q=0;
   for(a=0;a<15;a++)
   {for(b=0;b<15;b++)
       {if(revealed[a][b]==1&&kondisi[a][b]!='#'){q=q+1;}}
       }
   return q;
   }

void flag(char kondisi[15][15], int revealed[15][15])
{
//Kamus lokal
int x,y;
//Algoritma
      do {
         printf("X: ");
         scanf("%i",&y);
         printf("y: ");
         scanf("%i",&x);
         }
         while(x<1||y<1||x>15||y>15);
         if(revealed[x-1][y-1]==0)//board = 0 tertutup
         {
             kondisi[x-1][y-1]='F';
			 
         }
}



void rflag(char kondisi[15][15],int revealed[15][15])
{
//Kamus lokal
  int x,y;

//Algoritma
      do {
         printf("X: ");
		 scanf("%i",&y);
         printf("y: ");
		 scanf("%i",&x);
         }
		 while(x<1||y<1||x>15||y>15);

         if(kondisi[x-1][y-1]=='F')		//jika kondisinya sedang flag
		 {
			kondisi[x-1][y-1]='_';
         }
}




void resetscore()
{
//Kamus lokal
     int a,b;
     FILE *pf;

//Algoritma
     pf=fopen("HighScore.TXT","w");
     for(a=1;a<=10;a++)
         {
         fputs("username\n",pf);
         }
     fclose(pf);
     pf=fopen("HighScore.dat","wb");
     for(a=1;a<=10;a++)
     {putw(0,pf);}
     fclose(pf);

     }



void baca(user pemain[11])
{
//Kamus lokal
     int a,b;
     char c[20];
     FILE *pf;

//Algoritma
     pf=fopen("HighScore.txt","r");
     if(pf==NULL){resetscore();}
     a=1;
     fgets(pemain[a].nama,20,pf);
     while(a<=10)
                 {
                 if(pemain[a].nama[0]!='\n')
                     {a++;fgets(pemain[a].nama,20,pf);}
                 else{fgets(pemain[a].nama,20,pf);}
                 }
     fclose(pf);
     pf=fopen("HighScore.dat","rb");
     for(a=1;a<=10;a++)
     {pemain[a].nilai=getw(pf);}
     fclose(pf);
     }

void highscore()
{
//Kamus lokal
int a,b;
user juara[11];

//Algoritma
     baca(juara);baca(juara);
     printf(" Rank  |   Player     |  Score\n\n");
     for(a=1;a<=10;a++)
        {
        printf("%2i.       %s",a,juara[a].nama);
        printf("_________________________%i\n",juara[a].nilai);
        }
    printf("\ntekan x untuk mereset highscore ");
    if(getch()=='x'){resetscore();}
    system("cls");
     }

void tulis(user pemain[11])
{
//Kamus lokal
int a,b;
FILE *pf;

//Algoritma
     pf=fopen("HighScore.TXT","w");
     if(pf==NULL){resetscore();}
     for(a=1;a<=10;a++)
         {
         fputs(pemain[a].nama,pf);fputs("\n",pf);
         }
     fclose(pf);
     pf=fopen("HighScore.dat","wb");
     for(a=1;a<=10;a++)
     {putw(pemain[a].nilai,pf);}
     fclose(pf);
     }


void updatescore(user pemain)
{
//Kamus lokal
     int a,b;
     user juara[12];

//Algoritma
     baca(juara);
     for(a=10;a>=1;a--)
                       {
                       if(juara[a].nilai<pemain.nilai)
                         {juara[a+1]=juara[a];juara[a]=pemain;}
                         else{break;}
                       }
     tulis(juara);
     }

void random(int A[15][15])
{
//Kamus lokal
    srand((unsigned)time(NULL));
    int a,b,c=0;

//Algoritma
    for(a=0;a<15;a++){for(b=0;b<15;b++){A[a][b]=0;}}
    while(c<25)
            {
            for(a=0;a<15&&c<25;a++)
                {
                for(b=0;b<15&&c<25;b++)
                                      {
                                       if(A[a][b]!=9)
                                             {
                                             A[a][b]= rand()%10;
                                             if(A[a][b]==9){c++;}
                                             else{A[a][b]=0;}
                                             }
                                       }
                }
            }
    }


void PasangBom(int board[15][15])//mengisi board dengan 0-9. 9 maka berisi bom dan 0 maka kosong
{
//Kamus lokal
int x,y,a,i,j;a=25;

//Algoritma
      random(board);//isi board dengan 9 sebagai bom dan yang lain 0;
      for(x=0;x<15;x++)
          for(y=0;y<15;y++)
                         if(board[y][x] == 9)
                         {          if((y-1) >= 0)
                                    if(board[y-1][x] != 9)
                                                  board[y-1][x]++;
                                    if((y-1) >= 0 && (x-1) >= 0)
                                    if(board[y-1][x-1] != 9)
                                                  board[y-1][x-1]++;
                                    if((x-1) >= 0)
                                    if(board[y][x-1] != 9)
                                                  board[y][x-1]++;
                                    if((y+1) < 15)
                                    if(board[y+1][x] != 9)
                                                  board[y+1][x]++;
                                    if((y+1) < 15 && (x+1) < 15)
                                    if(board[y+1][x+1] != 9)
                                                  board[y+1][x+1]++;
                                    if((x+1) < 15)
                                    if(board[y][x+1] != 9)
                                                  board[y][x+1]++;
                                    if((y-1) >= 0 && (x+1) < 15)
                                    if(board[y-1][x+1] != 9)
                                                  board[y-1][x+1]++;
                                    if((y+1) < 15 && (x-1) >= 0)
                                    if(board[y+1][x-1] != 9)
                                                  board[y+1][x-1]++;
                         }

        }



void Tampilkar(char x[15][15])
{
//Kamus lokal
     int a=0;
     int b=0;

//Algoritma
     printf(" y\\x");
     while(b<15)
                {
                if(b<9){printf("_%i__",b+1);}
                else{printf("%i__",b+1);}
                b=b+1;
                }
      printf("\n");
      while(a<15)
                 {
                 b=0;
                 if(a<9){printf(" %i",a+1);}
                 else{printf("%i",a+1);}
                 while(b<15){printf("_|_%c",x[a][b]);b=b+1;}
                 printf("_|\n");
                 a=a+1;
                 }
     printf("\n");
      }

void Tampilang(int x[15][15])
{
//Kamus lokal
     int a=0;
     int b=0;

//Algoritma
     printf(" y\\x");
     while(b<15)
                {
                if(b<9){printf("_%i__",b+1);}
                else{printf("%i__",b+1);}
                b=b+1;
                }
      printf("\n");
      while(a<15)
                 {
                 b=0;
                 if(a<9){printf(" %i",a+1);}
                 else{printf("%i",a+1);}
                 while(b<15){printf(" | %i",x[a][b]);b=b+1;}
                 printf(" |\n");
                 a=a+1;
                 }
     printf("\n");
      }

void start(user pemain)
{
//Kamus lokal
int a,b,x,y,z,jbuka;
int jk=0;//jumlah klik,
int dead=0;//0 masih main, 1 kalah, 2 menang , 4 keluar(stop)
int board[15][15];
int revealed[15][15];
char kondisi[15][15];

//Algoritma
PasangBom(board);
for(a=0;a<15;a++)for(b=0;b<15;b++)revealed[a][b]=0;//mengkosongkan parameter buka
for(a=0;a<15;a++)for(b=0;b<15;b++)kondisi[a][b]='_';//mengkosongkan tampilan awal
Tampilkar(kondisi);
while(dead==0)
     {
           do{
           printf("1.Klik\n");
           printf("2.Flag\n");
           printf("3.Remove Flag\n");
           printf("4.Stop\n");
           printf("Masukkan pilihan : ");
           scanf("%i",&z);
           }while(z<1||(z>4&&z!=2357));
           switch(z)
           {
            case 1 :
            dead=klik(board,revealed,kondisi);
            jk++;
            break;

            case 2 :
            flag(kondisi,revealed);
            jk++;
            break;

            case 3 :
            rflag(kondisi,revealed);
            jk++;
            break;

            case 4 :
            system("cls");
            dead=4;
            break;

            case 2357 : //Cheat untuk melihat seluruh isi bom di minesweeper bila user memasukkan angka 2357
            Tampilang(board);
            break;
           }
           if(z!=4)
           Tampilkar(kondisi);
     }
     
     
     jbuka=jumlhbuka(revealed,kondisi);
     if (dead == 1)
        {   pemain.nilai=10*(2*jbuka- jk)+10;
            printf("\nANDA MENGENAI BOMB!!! \n\n");
            printf("User Name = %s\n",pemain.nama);
            printf("Score anda = %i\n",pemain.nilai);
            updatescore(pemain);getch();
        }
     else if(dead == 2)
        {   pemain.nilai=10*(2*jbuka-jk)+100;
            printf("\nANDA MENANG!!! :)\n\n");
            printf("User Name = %s\n",pemain.nama);
            printf("Score anda = %i\n",pemain.nilai);
            updatescore(pemain);getch();
        }
     
     system("cls");

}


int main()
{
int a,x;
user juara[11];
user pemain;
baca(juara);//memastikan bahwa file higscore.txt dan highscore.dat ada jika tidak ada maka akan direset.
strcpy(pemain.nama,"username");
pemain.nilai=0;
a=1;

while(a==1)
{
x=menu();
          switch(x){
            case 1:
            printf("Masukkan Nama : ");
            gets(pemain.nama);
            gets(pemain.nama);
            system("cls");
            printf("User Name : %s\n\n",pemain.nama);
            pemain.nilai=0;
            start(pemain);
            break;

            case 2:
            system("cls");
            highscore();
            break;

            case 3:
            system("cls");
            printf("User Name : %s\n\n",pemain.nama);
            start(pemain);
            break;

            case 4:
            system("cls");
            a=0;
            printf("\nTerima kasih sudah mencoba game ini\n\n");
          }

}

}
